#include <handler/PlanTreeInfoHandler.h>
#include <iostream>
#include <conversion.h>

void PlanTreeInfoHandler::handle(capnp::FlatArrayMessageReader &reader) {
    try {
        std::cout << std::endl << PlanTreeInfo::from(reader).toJson() << std::endl << std::endl;
        return;
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    } catch (kj::Exception&) {
        std::cout << "Error reading Plan Tree Info" << std::endl;
    }
}

PlanTreeInfoHandler::PlanTreeInfoHandler(CapnprotoMessageHandler *successor) : CapnprotoMessageHandler(successor) {}
