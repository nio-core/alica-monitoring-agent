#pragma once

#include "CapnprotoMessageHandler.h"

class AllocationAuthorityInfoHandler : public CapnprotoMessageHandler {
private:
    bool doHandle(capnp::FlatArrayMessageReader &reader) override;
};
