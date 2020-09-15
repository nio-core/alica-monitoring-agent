#include <handler/SyncTalkHandler.h>
#include <iostream>
#include <conversion.h>

void SyncTalkHandler::handle(capnp::FlatArrayMessageReader &reader) {
    try {
        std::cout << std::endl << SyncTalk::from(reader).toJson() << std::endl << std::endl;
        return;
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    } catch (kj::Exception&) {
        std::cout << "Error reading Sync Talk" << std::endl;
    }
}

SyncTalkHandler::SyncTalkHandler(CapnprotoMessageHandler *successor) : CapnprotoMessageHandler(successor) {}
