#include <handler/SyncReadyHandler.h>
#include <model/SyncReady.h>
#include <serialization/SerializationStrategy.h>
#include <iostream>
#include <exception/MessageHandlingException.h>

SyncReadyHandler::SyncReadyHandler(SerializationStrategy *serializationStrategy)
        : CapnprotoMessageHandler(serializationStrategy) {}


void SyncReadyHandler::doHandle(capnp::FlatArrayMessageReader &reader) {
    try {
        auto syncReady = model::SyncReady::from(reader);
        const std::string json = serializationStrategy->serializeSyncReady(syncReady);
        std::cout << json << std::endl;
    } catch (std::runtime_error& e) {
        throw MessageHandlingException();
    } catch (kj::Exception&) {
        throw MessageHandlingException();
    }
}