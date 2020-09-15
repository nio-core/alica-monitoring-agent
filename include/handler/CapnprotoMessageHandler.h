#pragma once

#include <capnp/serialize.h>

class CapnprotoMessageHandler {
public:
    explicit CapnprotoMessageHandler(CapnprotoMessageHandler *successor);

    virtual ~CapnprotoMessageHandler() = default;

    virtual void handle(capnp::FlatArrayMessageReader& reader) = 0;

protected:
    CapnprotoMessageHandler* successor_;
};
