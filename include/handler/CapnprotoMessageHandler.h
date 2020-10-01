#pragma once

#include <capnp/serialize.h>

class CapnprotoMessageHandler {
public:
    explicit CapnprotoMessageHandler();

    virtual ~CapnprotoMessageHandler() = default;

    void handle(capnp::FlatArrayMessageReader& reader);

    CapnprotoMessageHandler* chain(CapnprotoMessageHandler* successor);

protected:
    CapnprotoMessageHandler* successor_;

    virtual bool doHandle(capnp::FlatArrayMessageReader &reader) = 0;
};
