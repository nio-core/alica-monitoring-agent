#pragma once

#include <handler/CapnprotoMessageHandler.h>

class AlicaEngineInfoHandler : public CapnprotoMessageHandler{
public:
    explicit AlicaEngineInfoHandler(SerializationStrategy* serializationStrategy);

private:
    void doHandle(capnp::FlatArrayMessageReader& reader) override;
};
