#include <handler/SyncTalkHandler.h>
#include <model/SyncTalk.h>
#include <serialization/SerializationStrategy.h>
#include <iostream>
#include <exception/MessageHandlingException.h>
#include <storage/StorageStrategy.h>


SyncTalkHandler::SyncTalkHandler(SerializationStrategy *serializationStrategy, StorageStrategy* storageStrategy)
        : CapnprotoMessageHandler(serializationStrategy, storageStrategy) {}

void SyncTalkHandler::doHandle(capnp::FlatArrayMessageReader &reader) {
    try {
        auto syncTalk = model::SyncTalk::from(reader);
        const std::string json = serializationStrategy->serializeSyncTalk(syncTalk);
        storageStrategy->store(syncTalk.getSenderId(), "SYNC_TALK", json);
    } catch (std::runtime_error& e) {
        throw MessageHandlingException();
    } catch (kj::Exception&) {
        throw MessageHandlingException();
    }
}
