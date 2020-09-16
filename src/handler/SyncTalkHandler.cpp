#include <handler/SyncTalkHandler.h>
#include <iostream>
#include <conversion.h>

SyncTalkHandler::SyncTalkHandler(CapnprotoMessageHandler *successor) : CapnprotoMessageHandler(successor) {}

void SyncTalkHandler::handle(capnp::FlatArrayMessageReader &reader) {
    try {
        std::cout << SyncTalk::from(reader).toJson() << std::endl;
        return;
    } catch (std::runtime_error& e) {}
    catch (kj::Exception&) {}

    if(successor_ != nullptr) {
        successor_->handle(reader);
    } else {
        std::cout << "No matching handler available" << std::endl;
    }
}
