#include <handler/AllocationAuthorityInfoHandler.h>
#include <conversion/AllocationAuthorityInfo.h>
#include <serialization/SerializationStrategy.h>
#include <iostream>

AllocationAuthorityInfoHandler::AllocationAuthorityInfoHandler(SerializationStrategy* serializationStrategy)
    : CapnprotoMessageHandler(serializationStrategy) {}

bool AllocationAuthorityInfoHandler::doHandle(capnp::FlatArrayMessageReader &reader) {
    try {
        auto allocationAuthorityInfo = conversion::AllocationAuthorityInfo::from(reader);
        const std::string json = serializationStrategy->serializeAllocationAuthorityInfo(allocationAuthorityInfo);
        std::cout << json << std::endl;
        return true;
    } catch (std::runtime_error&) {
        return false;
    } catch (kj::Exception&) {
        return false;
    }
}
