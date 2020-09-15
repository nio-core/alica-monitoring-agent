#pragma once

#include "CapnprotoMessageHandler.h"

class SyncTalkHandler : public CapnprotoMessageHandler {
public:
    explicit SyncTalkHandler(CapnprotoMessageHandler *successor);

    void handle(capnp::FlatArrayMessageReader &reader) override;
};
