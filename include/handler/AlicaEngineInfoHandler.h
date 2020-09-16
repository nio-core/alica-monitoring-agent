#pragma once

#include "CapnprotoMessageHandler.h"

class AlicaEngineInfoHandler : public CapnprotoMessageHandler{
public:
    explicit AlicaEngineInfoHandler(CapnprotoMessageHandler *successor);

private:
    bool doHandle(capnp::FlatArrayMessageReader& reader) override;
};
