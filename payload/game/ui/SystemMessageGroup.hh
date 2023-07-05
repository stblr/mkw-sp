#pragma once

#include "game/ui/MessageGroup.hh"

namespace UI {

class SystemMessageGroup : public MessageGroup {
public:
    REPLACE void load();
};
static_assert(sizeof(SystemMessageGroup) == 0x14);

} // namespace UI
