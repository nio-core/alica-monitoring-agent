#pragma once

#include <handler/CapnprotoMessageHandler.h>

class RoleSwitchHandler : public CapnprotoMessageHandler {
public:
    explicit RoleSwitchHandler(SerializationStrategy* serializationStrategy);

private:
    bool doHandle(capnp::FlatArrayMessageReader &reader) override;
};
