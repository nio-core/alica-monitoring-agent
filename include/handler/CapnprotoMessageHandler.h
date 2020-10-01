#pragma once

#include <capnp/serialize.h>

class SerializationStrategy;
class StorageStrategy;

class CapnprotoMessageHandler {
public:
    explicit CapnprotoMessageHandler(SerializationStrategy *serializationStrategy,
                                     StorageStrategy *storageStrategy);

    virtual ~CapnprotoMessageHandler();

    void handle(capnp::FlatArrayMessageReader& reader);

    CapnprotoMessageHandler* chain(CapnprotoMessageHandler* successor);

protected:
    CapnprotoMessageHandler* successor;
    SerializationStrategy* serializationStrategy;
    StorageStrategy* storageStrategy;

    virtual void doHandle(capnp::FlatArrayMessageReader &reader) = 0;
};
