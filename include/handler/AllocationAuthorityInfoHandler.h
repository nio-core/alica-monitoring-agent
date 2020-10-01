#pragma once

#include <handler/CapnprotoMessageHandler.h>

class AllocationAuthorityInfoHandler : public CapnprotoMessageHandler {
public:
    explicit AllocationAuthorityInfoHandler(SerializationStrategy *serializationStrategy);

private:
    void doHandle(capnp::FlatArrayMessageReader &reader) override;
};
