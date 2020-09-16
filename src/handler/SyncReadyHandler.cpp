#include <handler/SyncReadyHandler.h>
#include <iostream>
#include <conversion.h>

SyncReadyHandler::SyncReadyHandler(CapnprotoMessageHandler *successor) : CapnprotoMessageHandler(successor) {}

void SyncReadyHandler::handle(capnp::FlatArrayMessageReader &reader) {
    try {
        std::cout << SyncReady::from(reader).toJson() << std::endl;
        return;
    } catch (std::runtime_error& e) {}
    catch (kj::Exception&) {}

    if(successor_ != nullptr) {
        successor_->handle(reader);
    } else {
        std::cout << "No matching handler available" << std::endl;
    }
}
