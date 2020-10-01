#include <handler/SolverResultHandler.h>
#include <model/SolverResult.h>
#include <serialization/SerializationStrategy.h>
#include <iostream>
#include <exception/MessageHandlingException.h>

SolverResultHandler::SolverResultHandler(SerializationStrategy *serializationStrategy)
        : CapnprotoMessageHandler(serializationStrategy) {}
        
void SolverResultHandler::doHandle(capnp::FlatArrayMessageReader &reader) {
    try {
        auto solverResult = model::SolverResult::from(reader);
        const std::string json = serializationStrategy->serializeSolverResult(solverResult);
        std::cout << json << std::endl;
    } catch (std::runtime_error&) {
        throw MessageHandlingException();
    } catch (kj::Exception&) {
        throw MessageHandlingException();
    }
}
