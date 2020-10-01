#include <handler/CapnprotoMessageHandler.h>
#include <conversion.h>
#include <iostream>

CapnprotoMessageHandler::CapnprotoMessageHandler() : successor_(nullptr) {}

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

CapnprotoMessageHandler *CapnprotoMessageHandler::chain(CapnprotoMessageHandler *successor) {
    successor_ = successor;
    return successor_;
}
