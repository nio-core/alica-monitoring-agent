#include <handler/AlicaEngineInfoHandler.h>
#include <iostream>
#include <conversion.h>

void AlicaEngineInfoHandler::handle(capnp::FlatArrayMessageReader &reader) {
    try {
        std::cout << std::endl << AlicaEngineInfo::from(reader).toJson() << std::endl << std::endl;
        return;
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    } catch (kj::Exception&) {
        std::cout << "Error reading Engine Info" << std::endl;
    }
}

AlicaEngineInfoHandler::AlicaEngineInfoHandler(CapnprotoMessageHandler *successor) : CapnprotoMessageHandler(
        successor) {}
