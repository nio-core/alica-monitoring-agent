#include <handler/RoleSwitchHandler.h>
#include <model/RoleSwitch.h>
#include <serialization/SerializationStrategy.h>
#include <iostream>


RoleSwitchHandler::RoleSwitchHandler(SerializationStrategy *serializationStrategy)
        : CapnprotoMessageHandler(serializationStrategy) {}

bool RoleSwitchHandler::doHandle(capnp::FlatArrayMessageReader &reader) {
    try {
        auto roleSwitch = model::RoleSwitch::from(reader);
        const std::string json = serializationStrategy->serializeRoleSwitch(roleSwitch);
        std::cout << json << std::endl;
        return true;
    } catch (std::runtime_error&) {
        return false;
    } catch (kj::Exception&) {
        return false;
    }
}

