#pragma once

#include <handler/CapnprotoMessageHandler.h>

class SyncReadyHandler : public CapnprotoMessageHandler {
public:
    explicit SyncReadyHandler(SerializationStrategy* serializationStrategy);

private:
    void doHandle(capnp::FlatArrayMessageReader &reader) override;
};
