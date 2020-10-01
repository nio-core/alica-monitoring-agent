#pragma once

#include <handler/CapnprotoMessageHandler.h>

class SyncReadyHandler : public CapnprotoMessageHandler {
public:
    explicit SyncReadyHandler(SerializationStrategy* serializationStrategy, StorageStrategy* storageStrategy);

private:
    void doHandle(capnp::FlatArrayMessageReader &reader) override;
};
