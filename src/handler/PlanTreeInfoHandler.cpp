#include <handler/PlanTreeInfoHandler.h>
#include <iostream>
#include <conversion.h>

PlanTreeInfoHandler::PlanTreeInfoHandler(CapnprotoMessageHandler *successor) : CapnprotoMessageHandler(successor) {}

void PlanTreeInfoHandler::handle(capnp::FlatArrayMessageReader &reader) {
    try {
        std::cout << PlanTreeInfo::from(reader).toJson() << std::endl;
        return;
    } catch (std::runtime_error& e) {}
    catch (kj::Exception&) {}

    if(successor_ != nullptr) {
        successor_->handle(reader);
    } else {
        std::cout << "No matching handler available" << std::endl;
    }
}
