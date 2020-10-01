#include <handler/RoleSwitchHandler.h>
#include <conversion.h>
#include <iostream>

bool RoleSwitchHandler::doHandle(capnp::FlatArrayMessageReader &reader) {
    try {
        std::cout << conversion::RoleSwitch::from(reader).toJson() << std::endl;
        return true;
    } catch (std::runtime_error&) {
        return false;
    } catch (kj::Exception&) {
        return false;
    }
}
