#pragma once

#include <handler/CapnprotoMessageHandler.h>

class AlicaEngineInfoHandler : public CapnprotoMessageHandler{
public:
    explicit AlicaEngineInfoHandler(SerializationStrategy* serializationStrategy);

private:
    bool doHandle(capnp::FlatArrayMessageReader& reader) override;
};
