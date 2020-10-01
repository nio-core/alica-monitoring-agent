#include <handler/AlicaEngineInfoHandler.h>
#include <conversion/AlicaEngineInfo.h>
#include <serialization/SerializationStrategy.h>
#include <iostream>

AlicaEngineInfoHandler::AlicaEngineInfoHandler(SerializationStrategy *serializationStrategy) :
    CapnprotoMessageHandler(serializationStrategy) {}

bool AlicaEngineInfoHandler::doHandle(capnp::FlatArrayMessageReader &reader) {
    try {
        auto engineInfo = conversion::AlicaEngineInfo::from(reader);
        const std::string json = serializationStrategy->serializeAlicaEngineInfo(engineInfo);
        std::cout << json << std::endl;
        return true;
    } catch (std::runtime_error&) {
        return false;
    } catch (kj::Exception&) {
        return false;
    }
}
