#include <handler/RoleSwitchHandler.h>
#include <model/RoleSwitch.h>
#include <serialization/SerializationStrategy.h>
#include <iostream>
#include <exception/MessageHandlingException.h>


RoleSwitchHandler::RoleSwitchHandler(SerializationStrategy *serializationStrategy)
        : CapnprotoMessageHandler(serializationStrategy) {}

void RoleSwitchHandler::doHandle(capnp::FlatArrayMessageReader &reader) {
    try {
        auto roleSwitch = model::RoleSwitch::from(reader);
        const std::string json = serializationStrategy->serializeRoleSwitch(roleSwitch);
        std::cout << json << std::endl;
    } catch (std::runtime_error&) {
        throw MessageHandlingException();
    } catch (kj::Exception&) {
        throw MessageHandlingException();
    }
}

