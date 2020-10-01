#include <handler/SyncReadyHandler.h>
#include <model/SyncReady.h>
#include <serialization/SerializationStrategy.h>
#include <iostream>
#include <exception/MessageHandlingException.h>
#include <storage/StorageStrategy.h>

SyncReadyHandler::SyncReadyHandler(SerializationStrategy *serializationStrategy, StorageStrategy* storageStrategy)
        : CapnprotoMessageHandler(serializationStrategy, storageStrategy) {}


void SyncReadyHandler::doHandle(capnp::FlatArrayMessageReader &reader) {
    try {
        auto syncReady = model::SyncReady::from(reader);
        const std::string json = serializationStrategy->serializeSyncReady(syncReady);
        storageStrategy->store(syncReady.getSenderId(), "SYNC_READY", json);
    } catch (std::runtime_error& e) {
        throw MessageHandlingException();
    } catch (kj::Exception&) {
        throw MessageHandlingException();
    }
}