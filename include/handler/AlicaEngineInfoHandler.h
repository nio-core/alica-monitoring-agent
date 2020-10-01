#pragma once

#include "CapnprotoMessageHandler.h"

class AlicaEngineInfoHandler : public CapnprotoMessageHandler{
private:
    bool doHandle(capnp::FlatArrayMessageReader& reader) override;
};
