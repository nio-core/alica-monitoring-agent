#include <handler/AllocationAuthorityInfoHandler.h>
#include <model/AllocationAuthorityInfo.h>
#include <serialization/SerializationStrategy.h>
#include <iostream>
#include <exception/MessageHandlingException.h>

AllocationAuthorityInfoHandler::AllocationAuthorityInfoHandler(SerializationStrategy* serializationStrategy)
    : CapnprotoMessageHandler(serializationStrategy) {}

void AllocationAuthorityInfoHandler::doHandle(capnp::FlatArrayMessageReader &reader) {
    try {
        auto allocationAuthorityInfo = model::AllocationAuthorityInfo::from(reader);
        const std::string json = serializationStrategy->serializeAllocationAuthorityInfo(allocationAuthorityInfo);
        std::cout << json << std::endl;
    } catch (std::runtime_error&) {
        throw MessageHandlingException();
    } catch (kj::Exception&) {
        throw MessageHandlingException();
    }
}
