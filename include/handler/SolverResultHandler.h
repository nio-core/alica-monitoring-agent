#pragma once

#include <handler/CapnprotoMessageHandler.h>

class SolverResultHandler : public CapnprotoMessageHandler {
public:
    explicit SolverResultHandler(SerializationStrategy* serializationStrategy, StorageStrategy* storageStrategy);

private:
    void doHandle(capnp::FlatArrayMessageReader &reader) override;
};
