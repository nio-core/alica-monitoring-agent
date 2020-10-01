#pragma once

#include <capnp/serialize.h>

class SerializationStrategy;

class CapnprotoMessageHandler {
public:
    explicit CapnprotoMessageHandler(SerializationStrategy *serializationStrategy);

    virtual ~CapnprotoMessageHandler();

    void handle(capnp::FlatArrayMessageReader& reader);

    CapnprotoMessageHandler* chain(CapnprotoMessageHandler* successor);

protected:
    CapnprotoMessageHandler* successor;
    SerializationStrategy* serializationStrategy;

    virtual bool doHandle(capnp::FlatArrayMessageReader &reader) = 0;
};
