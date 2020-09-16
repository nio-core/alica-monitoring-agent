#include <handler/RoleSwitchHandler.h>
#include <conversion.h>
#include <iostream>

RoleSwitchHandler::RoleSwitchHandler(CapnprotoMessageHandler *successor) : CapnprotoMessageHandler(successor) {}

void RoleSwitchHandler::handle(capnp::FlatArrayMessageReader &reader) {
    try {
        std::cout << RoleSwitch::from(reader).toJson() << std::endl;
        return;
    } catch (std::runtime_error& e) {}
    catch (kj::Exception&) {}

    if(successor_ != nullptr) {
        successor_->handle(reader);
    } else {
        std::cout << "No matching handler available" << std::endl;
    }
}
