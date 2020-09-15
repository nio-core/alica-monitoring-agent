#include <handler/SolverResultHandler.h>
#include <conversion/SolverResult.h>
#include <iostream>

void SolverResultHandler::handle(capnp::FlatArrayMessageReader &reader) {
    try {
        std::cout << std::endl << SolverResult::from(reader).toJson() << std::endl << std::endl;
        return;
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    } catch (kj::Exception&) {
        std::cout << "Error reading Solver Result" << std::endl;
    }
}

SolverResultHandler::SolverResultHandler(CapnprotoMessageHandler *successor) : CapnprotoMessageHandler(successor) {}
