#include <handler/CapnprotoMessageHandler.h>
#include <serialization/SerializationStrategy.h>
#include <iostream>
#include "exception/MessageHandlingException.h"
#include "exception/NoFittingHandlerException.h"

CapnprotoMessageHandler::CapnprotoMessageHandler(SerializationStrategy *serializationStrategy,
                                                 StorageStrategy *storageStrategy)
        : successor(nullptr), serializationStrategy(serializationStrategy), storageStrategy(storageStrategy) {}

CapnprotoMessageHandler::~CapnprotoMessageHandler() {
    delete successor;
}

void CapnprotoMessageHandler::handle(capnp::FlatArrayMessageReader &reader) {
    try {
        doHandle(reader);
    } catch (MessageHandlingException& e) {
        if (successor) {
            successor->handle(reader);
        } else {
            throw NoFittingHandlerException();
        }
    }
}

CapnprotoMessageHandler *CapnprotoMessageHandler::chain(CapnprotoMessageHandler *successor) {
    this->successor = successor;
    return successor;
}
