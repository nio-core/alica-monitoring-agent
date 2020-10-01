#pragma once

#include <handler/CapnprotoMessageHandler.h>

class AlicaEngineInfoHandler : public CapnprotoMessageHandler{
public:
    explicit AlicaEngineInfoHandler(SerializationStrategy* serializationStrategy, StorageStrategy* storageStrategy);

private:
    void doHandle(capnp::FlatArrayMessageReader& reader) override;
};
