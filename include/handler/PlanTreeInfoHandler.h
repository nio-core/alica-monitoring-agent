#pragma once

#include <handler/CapnprotoMessageHandler.h>

class PlanTreeInfoHandler : public CapnprotoMessageHandler {
public:
    explicit PlanTreeInfoHandler(SerializationStrategy* serializationStrategy);

private:
    bool doHandle(capnp::FlatArrayMessageReader &reader) override;
};
