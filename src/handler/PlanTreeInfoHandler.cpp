#include <handler/PlanTreeInfoHandler.h>
#include <model/PlanTreeInfo.h>
#include <serialization/SerializationStrategy.h>
#include <iostream>


PlanTreeInfoHandler::PlanTreeInfoHandler(SerializationStrategy *serializationStrategy)
    : CapnprotoMessageHandler(serializationStrategy) {}

bool PlanTreeInfoHandler::doHandle(capnp::FlatArrayMessageReader &reader) {
    try {
        auto planTreeInfo = model::PlanTreeInfo::from(reader);
        const std::string json = serializationStrategy->serializePlanTreeInfo(planTreeInfo);
        std::cout << json << std::endl;
        return true;
    } catch (std::runtime_error&) {
        return false;
    } catch (kj::Exception&) {
        return false;
    }
}
