#include <handler/RoleSwitchHandler.h>
#include <model/RoleSwitch.h>
#include <serialization/SerializationStrategy.h>
#include <iostream>
#include <exception/MessageHandlingException.h>
#include <storage/StorageStrategy.h>

RoleSwitchHandler::RoleSwitchHandler(SerializationStrategy *serializationStrategy, StorageStrategy* storageStrategy)
        : CapnprotoMessageHandler(serializationStrategy, storageStrategy) {}

void RoleSwitchHandler::doHandle(capnp::FlatArrayMessageReader &reader) {
    try {
        auto roleSwitch = model::RoleSwitch::from(reader);
        const std::string json = serializationStrategy->serializeRoleSwitch(roleSwitch);
        storageStrategy->store(roleSwitch.getSenderId(), "ROLE_SWITCH", json);
    } catch (std::runtime_error&) {
        throw MessageHandlingException();
    } catch (kj::Exception&) {
        throw MessageHandlingException();
    }
}

