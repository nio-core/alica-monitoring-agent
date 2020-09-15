#include <handler/RoleSwitchHandler.h>
#include <conversion.h>
#include <iostream>

void RoleSwitchHandler::handle(capnp::FlatArrayMessageReader &reader) {
    try {
        std::cout << std::endl << RoleSwitch::from(reader).toJson() << std::endl << std::endl;
        return;
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    } catch (kj::Exception&) {
        std::cout << "Error reading Role Switch" << std::endl;
    }

}

RoleSwitchHandler::RoleSwitchHandler(CapnprotoMessageHandler *successor) : CapnprotoMessageHandler(successor) {}
