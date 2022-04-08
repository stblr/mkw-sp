#include "UsbHid.h"

#include "sp/Bytes.h"
#include "sp/Usb.h"

#include <revolution.h>

enum {
    DESCRIPTOR_TYPE_HID = 0x21,
    DESCRIPTOR_TYPE_REPORT = 0x22,
    DESCRIPTOR_TYPE_PHYSICAL = 0x23,
};

enum {
    ITEM_TYPE_MAIN = 0x0,
    ITEM_TYPE_GLOBAL = 0x1,
    ITEM_TYPE_LOCAL = 0x2,
};

enum {
    ITEM_TAG_GLOBAL_USAGE_PAGE = 0x0,
    ITEM_TAG_GLOBAL_LOGICAL_MINIMUM = 0x1,
    ITEM_TAG_GLOBAL_LOGICAL_MAXIMUM = 0x2,
    ITEM_TAG_GLOBAL_PHYSICAL_MINIMUM = 0x3,
    ITEM_TAG_GLOBAL_PHYSICAL_MAXIMUM = 0x4,
    ITEM_TAG_GLOBAL_UNIT_EXPONENT = 0x5,
    ITEM_TAG_GLOBAL_UNIT = 0x6,
    ITEM_TAG_GLOBAL_REPORT_SIZE = 0x7,
    ITEM_TAG_GLOBAL_REPORT_ID = 0x8,
    ITEM_TAG_GLOBAL_REPORT_COUNT = 0x9,
    ITEM_TAG_GLOBAL_PUSH = 0xa,
    ITEM_TAG_GLOBAL_POP = 0xb,

    ITEM_TAG_MAIN_INPUT = 0x8,
    ITEM_TAG_MAIN_OUTPUT = 0x9,
    ITEM_TAG_MAIN_FEATURE = 0xa,
    ITEM_TAG_MAIN_COLLECTION = 0xb,
    ITEM_TAG_MAIN_END_COLLECTION = 0xc,

    ITEM_TAG_LONG = 0xf,
};

typedef struct {
    bool isUsed;
    u32 id;
    u8 *buffer;
} Device;

static u8 *descriptorBuffer;
static Device devices[4];

static Device *UsbHid_findFreeDevice(void) {
    for (u32 i = 0; i < ARRAY_SIZE(devices); i++) {
        if (!devices[i].isUsed) {
            return &devices[i];
        }
    }

    return NULL;
}

static bool UsbHid_processReportDescriptor(u16 descriptorSize, const u8 *descriptor) {
    for (u32 offset = 0; offset < descriptorSize;) {
        u8 size = descriptor[offset] & 0x3;
        u8 type = descriptor[offset] >> 2 & 0x3;
        u8 tag = descriptor[offset] >> 4;
        //SP_LOG("%x %x %x", size, type, tag);
        offset++;

        if (tag == ITEM_TAG_LONG) {
            if (offset + 2 > descriptorSize) {
                return false;
            }
            size = descriptor[offset++];
            tag = descriptor[offset++];
            offset += size;
            if (offset > descriptorSize) {
                return false;
            }
            continue;
        }

        if (size == 3) {
            size = 4;
        }

        u32 val;
        switch (size) {
        case 0:
            val = 0;
            break;
        case 1:
            val = descriptor[offset];
            break;
        case 2:
            val = read_u16_le(descriptor, offset);
            break;
        case 4:
            val = read_u32_le(descriptor, offset);
        }

        switch (type) {
        case ITEM_TYPE_MAIN:
            OSReport("main ");
            switch (tag) {
            case ITEM_TAG_MAIN_INPUT:
                OSReport("input %x", val);
                break;
            case ITEM_TAG_MAIN_OUTPUT:
                OSReport("output %x", val);
                break;
            case ITEM_TAG_MAIN_FEATURE:
                OSReport("feature %x", val);
                break;
            case ITEM_TAG_MAIN_COLLECTION:
                OSReport("collection %x", val);
                break;
            case ITEM_TAG_MAIN_END_COLLECTION:
                OSReport("end collection %x", val);
                break;
            }
            OSReport("\n");
            break;
        case ITEM_TYPE_GLOBAL:
            OSReport("global ");
            switch (tag) {
            case ITEM_TAG_GLOBAL_USAGE_PAGE:
                OSReport("usage page %x", val);
                break;
            case ITEM_TAG_GLOBAL_LOGICAL_MINIMUM:
                OSReport("logical minimum %x", val);
                break;
            case ITEM_TAG_GLOBAL_LOGICAL_MAXIMUM:
                OSReport("logical maximum %x", val);
                break;
            case ITEM_TAG_GLOBAL_PHYSICAL_MINIMUM:
                OSReport("physical minimum %x", val);
                break;
            case ITEM_TAG_GLOBAL_PHYSICAL_MAXIMUM:
                OSReport("physical maximum %x", val);
                break;
            case ITEM_TAG_GLOBAL_UNIT_EXPONENT:
                OSReport("unit exponent %x", val);
                break;
            case ITEM_TAG_GLOBAL_UNIT:
                OSReport("unit %x", val);
                break;
            case ITEM_TAG_GLOBAL_REPORT_SIZE:
                OSReport("report size %x", val);
                break;
            case ITEM_TAG_GLOBAL_REPORT_ID:
                OSReport("report id %x", val);
                break;
            case ITEM_TAG_GLOBAL_REPORT_COUNT:
                OSReport("report count %x", val);
                break;
            case ITEM_TAG_GLOBAL_PUSH:
                OSReport("push %x", val);
                break;
            case ITEM_TAG_GLOBAL_POP:
                OSReport("pop %x", val);
                break;
            }
            OSReport("\n");
            break;
        case ITEM_TYPE_LOCAL:
            OSReport("local %x %x\n", tag, val);
            break;
        default:
            return false;
        }

        offset += size;
    }

    return true;
}

static bool UsbHid_onDeviceAdd(const UsbDeviceInfo *info) {
    Device *device = UsbHid_findFreeDevice();
    if (!device) {
        return false;
    }

    u8 interfaceClass = info->interfaceDescriptor.interfaceClass;
    if (interfaceClass != USB_INTERFACE_CLASS_HID) {
        return false;
    }

    u16 vendorId = info->deviceDescriptor.vendorId;
    u16 productId = info->deviceDescriptor.productId;
    SP_LOG("Found device %04x:%04x", vendorId, productId);

    u8 requestType = 0;
    requestType |= USB_RECIPIENT_INTERFACE << USB_RECIPIENT_SHIFT;
    requestType |= USB_REQUEST_TYPE_STANDARD << USB_REQUEST_TYPE_SHIFT;
    requestType |= USB_ENDPOINT_DIRECTION_DEVICE_TO_HOST << USB_ENDPOINT_DIRECTION_SHIFT;
    if (!Usb_ctrlTransfer(info->id, requestType, USB_GET_DESCRIPTOR, DESCRIPTOR_TYPE_HID << 8,
            info->interfaceDescriptor.interfaceNumber, 0x9, descriptorBuffer)) {
        return false;
    }

    u16 reportDescriptorSize = read_u16_le(descriptorBuffer, 0x7);
    if (reportDescriptorSize == 0 || reportDescriptorSize > 0x1000) {
        return false;
    }
    if (!Usb_ctrlTransfer(info->id, requestType, USB_GET_DESCRIPTOR, DESCRIPTOR_TYPE_REPORT << 8,
            info->interfaceDescriptor.interfaceNumber, reportDescriptorSize, descriptorBuffer)) {
        return false;
    }

    for (u32 i = 0; i < reportDescriptorSize; i++) {
        if (i % 8 == 7) {
            OSReport("%02x\n", descriptorBuffer[i]);
        } else {
            OSReport("%02x ", descriptorBuffer[i]);
        }
    }
    OSReport("\n");

    UsbHid_processReportDescriptor(reportDescriptorSize, descriptorBuffer);

    return false;
}

static void UsbHid_onDeviceRemove(u32 id) {

}

static UsbHandler handler = {
    .onDeviceAdd = UsbHid_onDeviceAdd,
    .onDeviceRemove = UsbHid_onDeviceRemove,
};

void UsbHid_init(void) {
    descriptorBuffer = OSAllocFromMEM2ArenaLo(0x1000, 0x20);
    for (u32 i = 0; i < ARRAY_SIZE(devices); i++) {
        //devices[i].buffer = OSAllocFromMEM2ArenaLo(/* ? */, 0x20);
    }

    Usb_addHandler(&handler);
}
