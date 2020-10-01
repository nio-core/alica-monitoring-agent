#include <handler/SyncTalkHandler.h>
#include <model/SyncTalk.h>
#include <serialization/SerializationStrategy.h>
#include <iostream>
#include <exception/MessageHandlingException.h>


SyncTalkHandler::SyncTalkHandler(SerializationStrategy *serializationStrategy)
        : CapnprotoMessageHandler(serializationStrategy) {}

void SyncTalkHandler::doHandle(capnp::FlatArrayMessageReader &reader) {
    try {
        auto syncTalk = model::SyncTalk::from(reader);
        const std::string json = serializationStrategy->serializeSyncTalk(syncTalk);
        std::cout << json << std::endl;
    } catch (std::runtime_error& e) {
        throw MessageHandlingException();
    } catch (kj::Exception&) {
        throw MessageHandlingException();
    }
}
