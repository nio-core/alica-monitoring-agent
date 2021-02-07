#include <handler/PerformanceMeasurementHandler.h>
#include <iostream>
#include <chrono>

PerformanceMeasurementHandler::PerformanceMeasurementHandler()
        : CapnprotoMessageHandler(nullptr, nullptr) {}

void PerformanceMeasurementHandler::doHandle(capnp::FlatArrayMessageReader &reader) {
    auto smmt_start = std::chrono::high_resolution_clock::now();
    successor->handle(reader);
    auto smmt_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> smmt = smmt_end - smmt_start;
    std::cout << "SMMT: " << smmt.count() << " Milliseconds" << std::endl;
}
