#pragma once

#include "CapnprotoMessageHandler.h"

class SyncTalkHandler : public CapnprotoMessageHandler {
public:
    explicit SyncTalkHandler(CapnprotoMessageHandler *successor);

    bool doHandle(capnp::FlatArrayMessageReader &reader) override;
};
