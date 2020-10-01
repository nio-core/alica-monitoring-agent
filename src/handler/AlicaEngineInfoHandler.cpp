#include <handler/AlicaEngineInfoHandler.h>
#include <model/AlicaEngineInfo.h>
#include <serialization/SerializationStrategy.h>
#include <iostream>
#include <exception/MessageHandlingException.h>
#include <storage/StorageStrategy.h>

AlicaEngineInfoHandler::AlicaEngineInfoHandler(SerializationStrategy *serializationStrategy, StorageStrategy* storageStrategy) :
        CapnprotoMessageHandler(serializationStrategy, storageStrategy) {}

void AlicaEngineInfoHandler::doHandle(capnp::FlatArrayMessageReader &reader) {
    try {
        auto engineInfo = model::AlicaEngineInfo::from(reader);
        const std::string json = serializationStrategy->serializeAlicaEngineInfo(engineInfo);
        storageStrategy->store(engineInfo.getSenderId(), "ALICA_ENGINE_INFO", json);
    } catch (std::runtime_error&) {
        throw MessageHandlingException();
    } catch (kj::Exception&) {
        throw MessageHandlingException();
    }
}
