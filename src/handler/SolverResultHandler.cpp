#include <handler/SolverResultHandler.h>
#include <model/SolverResult.h>
#include <serialization/SerializationStrategy.h>
#include <iostream>
#include <exception/MessageHandlingException.h>
#include <storage/StorageStrategy.h>

SolverResultHandler::SolverResultHandler(SerializationStrategy *serializationStrategy, StorageStrategy* storageStrategy)
        : CapnprotoMessageHandler(serializationStrategy, storageStrategy) {}
        
void SolverResultHandler::doHandle(capnp::FlatArrayMessageReader &reader) {
    try {
        auto solverResult = model::SolverResult::from(reader);
        const std::string json = serializationStrategy->serializeSolverResult(solverResult);
        storageStrategy->store(solverResult.getSenderId(), "SOLVER_RESULT", json);
    } catch (std::runtime_error&) {
        throw MessageHandlingException();
    } catch (kj::Exception&) {
        throw MessageHandlingException();
    }
}
