#pragma once

#include "Page.h"
#include "RadioButtonControl.h"

#include "ctrl/CtrlMenuBackButton.h"
#include "ctrl/CtrlMenuInstructionText.h"
#include "ctrl/CtrlMenuPageTitleText.h"

typedef struct {
    Page;
    MultiControlInputManager inputManager;
    CtrlMenuPageTitleText pageTitleText;
    RadioButtonControl settingControls[2];
    CtrlMenuInstructionText instructionText;
    CtrlMenuBackButton backButton;
    InputHandler onBack;
    RadioButtonControlHandler onSettingFront;
    RadioButtonControlHandler onSettingSelect;
    bool resetSelection;
} LicenseSettingsPage;