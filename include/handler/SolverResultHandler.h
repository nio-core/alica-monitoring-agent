#pragma once

#include "CapnprotoMessageHandler.h"

class SolverResultHandler : public CapnprotoMessageHandler {
public:
    explicit SolverResultHandler(CapnprotoMessageHandler *successor);

private:
    bool doHandle(capnp::FlatArrayMessageReader &reader) override;
};
