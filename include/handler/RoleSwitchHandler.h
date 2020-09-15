#pragma once

#include "CapnprotoMessageHandler.h"

class RoleSwitchHandler : public CapnprotoMessageHandler {
public:
    explicit RoleSwitchHandler(CapnprotoMessageHandler *successor);

    void handle(capnp::FlatArrayMessageReader &reader) override;
};
