#pragma once

#include <capnp/serialize.h>

class CapnprotoMessageHandler {
public:
    void handle(capnp::FlatArrayMessageReader& reader);
};
