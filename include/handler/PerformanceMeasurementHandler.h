#pragma once

#include <handler/CapnprotoMessageHandler.h>

class PerformanceMeasurementHandler : public CapnprotoMessageHandler {
public:
    explicit PerformanceMeasurementHandler();
private:
    void doHandle(capnp::FlatArrayMessageReader &reader) override;
};
