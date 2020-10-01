#include <handler/SyncTalkHandler.h>
#include <iostream>
#include <conversion.h>

bool SyncTalkHandler::doHandle(capnp::FlatArrayMessageReader &reader) {
    try {
        std::cout << conversion::SyncTalk::from(reader).toJson() << std::endl;
        return true;
    } catch (std::runtime_error& e) {
        return false;
    } catch (kj::Exception&) {
        return false;
    }
}
