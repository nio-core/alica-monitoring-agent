#pragma once

#include "CapnprotoMessageHandler.h"

class AllocationAuthorityInfoHandler : public CapnprotoMessageHandler {
public:
    explicit AllocationAuthorityInfoHandler(CapnprotoMessageHandler *successor);

private:
    bool doHandle(capnp::FlatArrayMessageReader &reader) override;
};
