#pragma once

#include "CapnprotoMessageHandler.h"

class SyncReadyHandler : public CapnprotoMessageHandler {
public:
    explicit SyncReadyHandler(CapnprotoMessageHandler *successor);

    bool doHandle(capnp::FlatArrayMessageReader &reader) override;
};
