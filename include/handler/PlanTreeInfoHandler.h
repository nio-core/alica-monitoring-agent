#pragma once

#include "CapnprotoMessageHandler.h"

class PlanTreeInfoHandler : public CapnprotoMessageHandler {
public:
    explicit PlanTreeInfoHandler(CapnprotoMessageHandler *successor);

private:
    bool doHandle(capnp::FlatArrayMessageReader &reader) override;
};
