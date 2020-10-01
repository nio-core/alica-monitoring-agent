#pragma once

#include "CapnprotoMessageHandler.h"

class PlanTreeInfoHandler : public CapnprotoMessageHandler {
private:
    bool doHandle(capnp::FlatArrayMessageReader &reader) override;
};
