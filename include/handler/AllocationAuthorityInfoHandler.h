#pragma once

#include <handler/CapnprotoMessageHandler.h>

class AllocationAuthorityInfoHandler : public CapnprotoMessageHandler {
public:
    explicit AllocationAuthorityInfoHandler(SerializationStrategy *serializationStrategy);

private:
    bool doHandle(capnp::FlatArrayMessageReader &reader) override;
};
