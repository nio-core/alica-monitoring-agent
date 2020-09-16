#include <handler/CapnprotoMessageHandler.h>
#include <conversion.h>
#include <iostream>

CapnprotoMessageHandler::CapnprotoMessageHandler(CapnprotoMessageHandler *successor) : successor_(successor) {}

void CapnprotoMessageHandler::handle(capnp::FlatArrayMessageReader &reader) {
    auto messageHandled = doHandle(reader);

    if(!messageHandled && successor_ != nullptr) {
        successor_->handle(reader);
    } else if(!messageHandled && successor_ == nullptr) {
        std::cout << "No matching handler available" << std::endl;
    }
}
