#pragma once

#include "CapnprotoMessageHandler.h"

class SyncReadyHandler : public CapnprotoMessageHandler {
private:
    bool doHandle(capnp::FlatArrayMessageReader &reader) override;
};
