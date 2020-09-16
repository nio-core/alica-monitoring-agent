#pragma once

#include "CapnprotoMessageHandler.h"

class RoleSwitchHandler : public CapnprotoMessageHandler {
public:
    explicit RoleSwitchHandler(CapnprotoMessageHandler *successor);

private:
    bool doHandle(capnp::FlatArrayMessageReader &reader) override;
};
