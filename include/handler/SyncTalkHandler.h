#pragma once

#include "CapnprotoMessageHandler.h"

class SyncTalkHandler : public CapnprotoMessageHandler {
private:
    bool doHandle(capnp::FlatArrayMessageReader &reader) override;
};
