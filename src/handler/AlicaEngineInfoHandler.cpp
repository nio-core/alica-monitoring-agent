#include <handler/AlicaEngineInfoHandler.h>
#include <iostream>
#include <conversion.h>

AlicaEngineInfoHandler::AlicaEngineInfoHandler(CapnprotoMessageHandler *successor)
    : CapnprotoMessageHandler(successor) {}

void AlicaEngineInfoHandler::handle(capnp::FlatArrayMessageReader &reader) {
    try {
        std::cout << AlicaEngineInfo::from(reader).toJson() << std::endl;
        return;
    } catch (std::runtime_error&) {}
    catch (kj::Exception&) {}

    if(successor_ != nullptr) {
        successor_->handle(reader);
    } else {
        std::cout << "No matching handler available" << std::endl;
    }
}
