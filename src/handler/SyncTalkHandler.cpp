#include <handler/SyncTalkHandler.h>
#include <model/SyncTalk.h>
#include <serialization/SerializationStrategy.h>
#include <iostream>


SyncTalkHandler::SyncTalkHandler(SerializationStrategy *serializationStrategy)
        : CapnprotoMessageHandler(serializationStrategy) {}

bool SyncTalkHandler::doHandle(capnp::FlatArrayMessageReader &reader) {
    try {
        auto syncTalk = model::SyncTalk::from(reader);
        const std::string json = serializationStrategy->serializeSyncTalk(syncTalk);
        std::cout << json << std::endl;
        return true;
    } catch (std::runtime_error& e) {
        return false;
    } catch (kj::Exception&) {
        return false;
    }
}
