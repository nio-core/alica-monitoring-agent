#pragma once

#include <handler/CapnprotoMessageHandler.h>

class SyncTalkHandler : public CapnprotoMessageHandler {
public:
    explicit SyncTalkHandler(SerializationStrategy* serializationStrategy, StorageStrategy* storageStrategy);

private:
    void doHandle(capnp::FlatArrayMessageReader &reader) override;
};
