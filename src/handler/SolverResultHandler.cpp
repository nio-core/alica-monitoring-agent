#include <handler/SolverResultHandler.h>
#include <conversion/SolverResult.h>
#include <iostream>

SolverResultHandler::SolverResultHandler(CapnprotoMessageHandler *successor) : CapnprotoMessageHandler(successor) {}

void SolverResultHandler::handle(capnp::FlatArrayMessageReader &reader) {
    try {
        std::cout << SolverResult::from(reader).toJson() << std::endl;
        return;
    } catch (std::runtime_error& e) {}
    catch (kj::Exception&) {}

    if(successor_ != nullptr) {
        successor_->handle(reader);
    } else {
        std::cout << "No matching handler available" << std::endl;
    }
}
