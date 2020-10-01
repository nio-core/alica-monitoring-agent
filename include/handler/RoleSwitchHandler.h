#pragma once

#include "CapnprotoMessageHandler.h"

class RoleSwitchHandler : public CapnprotoMessageHandler {
private:
    bool doHandle(capnp::FlatArrayMessageReader &reader) override;
};
