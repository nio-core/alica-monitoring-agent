#include <handler/SolverResultHandler.h>
#include <conversion/SolverResult.h>
#include <iostream>

SolverResultHandler::SolverResultHandler(CapnprotoMessageHandler *successor) : CapnprotoMessageHandler(successor) {}

bool SolverResultHandler::doHandle(capnp::FlatArrayMessageReader &reader) {
    try {
        std::cout << SolverResult::from(reader).toJson() << std::endl;
        return true;
    } catch (std::runtime_error&) {
        return false;
    } catch (kj::Exception&) {
        return false;
    }
}
