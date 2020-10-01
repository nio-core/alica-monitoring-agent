#pragma once

#include "CapnprotoMessageHandler.h"

class SolverResultHandler : public CapnprotoMessageHandler {
private:
    bool doHandle(capnp::FlatArrayMessageReader &reader) override;
};
