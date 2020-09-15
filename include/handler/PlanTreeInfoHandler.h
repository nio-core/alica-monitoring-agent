#pragma once

#include "CapnprotoMessageHandler.h"

class PlanTreeInfoHandler : public CapnprotoMessageHandler {
public:
    explicit PlanTreeInfoHandler(CapnprotoMessageHandler *successor);

    void handle(capnp::FlatArrayMessageReader &reader) override;
};
