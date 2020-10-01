#pragma once

#include <handler/CapnprotoMessageHandler.h>

class SyncTalkHandler : public CapnprotoMessageHandler {
public:
    explicit SyncTalkHandler(SerializationStrategy* serializationStrategy);


private:
    bool doHandle(capnp::FlatArrayMessageReader &reader) override;
};
