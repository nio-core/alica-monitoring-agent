#pragma once

#include "CapnprotoMessageHandler.h"

class SyncReadyHandler : public CapnprotoMessageHandler {
public:
    explicit SyncReadyHandler(CapnprotoMessageHandler *successor);

    void handle(capnp::FlatArrayMessageReader &reader) override;
};
