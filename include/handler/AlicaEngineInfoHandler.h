#pragma once

#include "CapnprotoMessageHandler.h"

class AlicaEngineInfoHandler : public CapnprotoMessageHandler{
public:
    explicit AlicaEngineInfoHandler(CapnprotoMessageHandler *successor);

    void handle(capnp::FlatArrayMessageReader& reader) override;
};
