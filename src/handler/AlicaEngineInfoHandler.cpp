#include <handler/AlicaEngineInfoHandler.h>
#include <iostream>
#include <conversion.h>

AlicaEngineInfoHandler::AlicaEngineInfoHandler(CapnprotoMessageHandler *successor)
    : CapnprotoMessageHandler(successor) {}

bool AlicaEngineInfoHandler::doHandle(capnp::FlatArrayMessageReader &reader) {
    try {
        std::cout << AlicaEngineInfo::from(reader).toJson() << std::endl;
        return true;
    } catch (std::runtime_error&) {
        return false;
    } catch (kj::Exception&) {
        return false;
    }
}
