#pragma once

#include <handler/CapnprotoMessageHandler.h>

class SolverResultHandler : public CapnprotoMessageHandler {
public:
    explicit SolverResultHandler(SerializationStrategy* serializationStrategy);

private:
    bool doHandle(capnp::FlatArrayMessageReader &reader) override;
};
