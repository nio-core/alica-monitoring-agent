#pragma once

#include "CapnprotoMessageHandler.h"

class AllocationAuthorityInfoHandler : public CapnprotoMessageHandler {
public:
    explicit AllocationAuthorityInfoHandler(CapnprotoMessageHandler *successor);

    void handle(capnp::FlatArrayMessageReader &reader) override;
};
