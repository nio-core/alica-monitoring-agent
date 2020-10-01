#include <handler/SolverResultHandler.h>
#include <conversion/SolverResult.h>
#include <serialization/SerializationStrategy.h>
#include <iostream>

SolverResultHandler::SolverResultHandler(SerializationStrategy *serializationStrategy)
        : CapnprotoMessageHandler(serializationStrategy) {}
        
bool SolverResultHandler::doHandle(capnp::FlatArrayMessageReader &reader) {
    try {
        auto solverResult = conversion::SolverResult::from(reader);
        const std::string json = serializationStrategy->serializeSolverResult(solverResult);
        std::cout << json << std::endl;
        return true;
    } catch (std::runtime_error&) {
        return false;
    } catch (kj::Exception&) {
        return false;
    }
}
