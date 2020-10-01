#include <handler/SyncReadyHandler.h>
#include <model/SyncReady.h>
#include <serialization/SerializationStrategy.h>
#include <iostream>

SyncReadyHandler::SyncReadyHandler(SerializationStrategy *serializationStrategy)
        : CapnprotoMessageHandler(serializationStrategy) {}


bool SyncReadyHandler::doHandle(capnp::FlatArrayMessageReader &reader) {
    try {
        auto syncReady = model::SyncReady::from(reader);
        const std::string json = serializationStrategy->serializeSyncReady(syncReady);
        std::cout << json << std::endl;
        return true;
    } catch (std::runtime_error& e) {
        return false;
    }
    catch (kj::Exception&) {
        return false;
    }
}