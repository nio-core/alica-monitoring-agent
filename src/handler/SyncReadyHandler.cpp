#include <handler/SyncReadyHandler.h>
#include <iostream>
#include <conversion.h>

bool SyncReadyHandler::doHandle(capnp::FlatArrayMessageReader &reader) {
    try {
        std::cout << conversion::SyncReady::from(reader).toJson() << std::endl;
        return true;
    } catch (std::runtime_error& e) {
        return false;
    }
    catch (kj::Exception&) {
        return false;
    }
}
