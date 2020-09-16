#pragma once

#include <capnp/serialize.h>

class CapnprotoMessageHandler {
public:
    explicit CapnprotoMessageHandler(CapnprotoMessageHandler *successor);

    virtual ~CapnprotoMessageHandler() = default;

    void handle(capnp::FlatArrayMessageReader& reader);

protected:
    CapnprotoMessageHandler* successor_;

    virtual bool doHandle(capnp::FlatArrayMessageReader &reader) = 0;
};
