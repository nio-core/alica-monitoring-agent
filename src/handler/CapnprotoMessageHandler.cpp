#include <handler/CapnprotoMessageHandler.h>
#include <conversion.h>
#include <iostream>

CapnprotoMessageHandler::CapnprotoMessageHandler(CapnprotoMessageHandler *successor) : successor_(successor) {}

void CapnprotoMessageHandler::handle(capnp::FlatArrayMessageReader &reader) {
    auto messageHandlingSuccessful = doHandle(reader);

    if (!messageHandlingSuccessful) {
        if(successor_) {
            successor_->handle(reader);
        } else {
            std::cout << "No matching handler available" << std::endl;
        }
    }
}
