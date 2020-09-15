#pragma once

#include "CapnprotoMessageHandler.h"

class SolverResultHandler : public CapnprotoMessageHandler {
public:
    explicit SolverResultHandler(CapnprotoMessageHandler *successor);

    void handle(capnp::FlatArrayMessageReader &reader) override;
};
