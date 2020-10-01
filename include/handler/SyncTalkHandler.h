#pragma once

#include <handler/CapnprotoMessageHandler.h>

class SyncTalkHandler : public CapnprotoMessageHandler {
public:
    explicit SyncTalkHandler(SerializationStrategy* serializationStrategy);

private:
    void doHandle(capnp::FlatArrayMessageReader &reader) override;
};
