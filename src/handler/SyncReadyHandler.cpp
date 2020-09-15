#include <handler/SyncReadyHandler.h>
#include <iostream>
#include <conversion.h>

void SyncReadyHandler::handle(capnp::FlatArrayMessageReader &reader) {
    try {
        std::cout << std::endl << SyncReady::from(reader).toJson() << std::endl << std::endl;
        return;
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    } catch (kj::Exception&) {
        std::cout << "Error reading Sync Talk" << std::endl;
    }
}

SyncReadyHandler::SyncReadyHandler(CapnprotoMessageHandler *successor) : CapnprotoMessageHandler(successor) {}
