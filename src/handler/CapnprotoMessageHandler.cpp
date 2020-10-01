#include <handler/CapnprotoMessageHandler.h>
#include <serialization/SerializationStrategy.h>
#include <iostream>

CapnprotoMessageHandler::CapnprotoMessageHandler(SerializationStrategy *serializationStrategy)
        : successor(nullptr), serializationStrategy(serializationStrategy) {}

CapnprotoMessageHandler::~CapnprotoMessageHandler() {
    delete successor;
}

void CapnprotoMessageHandler::handle(capnp::FlatArrayMessageReader &reader) {
    auto messageHandlingSuccessful = doHandle(reader);

    if (!messageHandlingSuccessful) {
        if(successor) {
            successor->handle(reader);
        } else {
            std::cout << "No matching handler available" << std::endl;
        }
    }
}

CapnprotoMessageHandler *CapnprotoMessageHandler::chain(CapnprotoMessageHandler *successor) {
    this->successor = successor;
    return successor;
}
