#include <handler/AllocationAuthorityInfoHandler.h>
#include <model/AllocationAuthorityInfo.h>
#include <serialization/SerializationStrategy.h>
#include <iostream>
#include <exception/MessageHandlingException.h>
#include <storage/StorageStrategy.h>

AllocationAuthorityInfoHandler::AllocationAuthorityInfoHandler(SerializationStrategy* serializationStrategy,
                                                               StorageStrategy* storageStrategy)
    : CapnprotoMessageHandler(serializationStrategy, storageStrategy) {}

void AllocationAuthorityInfoHandler::doHandle(capnp::FlatArrayMessageReader &reader) {
    try {
        auto allocationAuthorityInfo = model::AllocationAuthorityInfo::from(reader);
        const std::string json = serializationStrategy->serializeAllocationAuthorityInfo(allocationAuthorityInfo);
        storageStrategy->store(allocationAuthorityInfo.getSenderId(), "ALLOCATION_AUTHORITY_INFO", json);
    } catch (std::runtime_error&) {
        throw MessageHandlingException();
    } catch (kj::Exception&) {
        throw MessageHandlingException();
    }
}
