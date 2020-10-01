#pragma once

#include <handler/CapnprotoMessageHandler.h>

class RoleSwitchHandler : public CapnprotoMessageHandler {
public:
    explicit RoleSwitchHandler(SerializationStrategy* serializationStrategy, StorageStrategy* storageStrategy);

private:
    void doHandle(capnp::FlatArrayMessageReader &reader) override;
};
