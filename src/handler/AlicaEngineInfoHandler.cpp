#include <handler/AlicaEngineInfoHandler.h>
#include <model/AlicaEngineInfo.h>
#include <serialization/SerializationStrategy.h>
#include <iostream>
#include <exception/MessageHandlingException.h>

AlicaEngineInfoHandler::AlicaEngineInfoHandler(SerializationStrategy *serializationStrategy) :
    CapnprotoMessageHandler(serializationStrategy) {}

void AlicaEngineInfoHandler::doHandle(capnp::FlatArrayMessageReader &reader) {
    try {
        auto engineInfo = model::AlicaEngineInfo::from(reader);
        const std::string json = serializationStrategy->serializeAlicaEngineInfo(engineInfo);
        std::cout << json << std::endl;
    } catch (std::runtime_error&) {
        throw MessageHandlingException();
    } catch (kj::Exception&) {
        throw MessageHandlingException();
    }
}
