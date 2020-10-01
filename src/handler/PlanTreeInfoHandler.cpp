#include <handler/PlanTreeInfoHandler.h>
#include <model/PlanTreeInfo.h>
#include <serialization/SerializationStrategy.h>
#include <iostream>
#include <exception/MessageHandlingException.h>
#include <storage/StorageStrategy.h>

PlanTreeInfoHandler::PlanTreeInfoHandler(SerializationStrategy *serializationStrategy, StorageStrategy* storageStrategy)
    : CapnprotoMessageHandler(serializationStrategy, storageStrategy) {}

void PlanTreeInfoHandler::doHandle(capnp::FlatArrayMessageReader &reader) {
    try {
        auto planTreeInfo = model::PlanTreeInfo::from(reader);
        const std::string json = serializationStrategy->serializePlanTreeInfo(planTreeInfo);
        storageStrategy->store(planTreeInfo.getSenderId(), "PLAN_TREE_INFO", json);
    } catch (std::runtime_error&) {
        throw MessageHandlingException();
    } catch (kj::Exception&) {
        throw MessageHandlingException();
    }
}
