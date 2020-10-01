#include <handler/PlanTreeInfoHandler.h>
#include <model/PlanTreeInfo.h>
#include <serialization/SerializationStrategy.h>
#include <iostream>
#include <exception/MessageHandlingException.h>


PlanTreeInfoHandler::PlanTreeInfoHandler(SerializationStrategy *serializationStrategy)
    : CapnprotoMessageHandler(serializationStrategy) {}

void PlanTreeInfoHandler::doHandle(capnp::FlatArrayMessageReader &reader) {
    try {
        auto planTreeInfo = model::PlanTreeInfo::from(reader);
        const std::string json = serializationStrategy->serializePlanTreeInfo(planTreeInfo);
        std::cout << json << std::endl;
    } catch (std::runtime_error&) {
        throw MessageHandlingException();
    } catch (kj::Exception&) {
        throw MessageHandlingException();
    }
}
