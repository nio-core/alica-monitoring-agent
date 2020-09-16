#include <handler/PlanTreeInfoHandler.h>
#include <iostream>
#include <conversion.h>

PlanTreeInfoHandler::PlanTreeInfoHandler(CapnprotoMessageHandler *successor) : CapnprotoMessageHandler(successor) {}

bool PlanTreeInfoHandler::doHandle(capnp::FlatArrayMessageReader &reader) {
    try {
        std::cout << PlanTreeInfo::from(reader).toJson() << std::endl;
        return true;
    } catch (std::runtime_error&) {
        return false;
    } catch (kj::Exception&) {
        return false;
    }
}
