#include <handler/AllocationAuthorityInfoHandler.h>
#include <conversion.h>
#include <iostream>

AllocationAuthorityInfoHandler::AllocationAuthorityInfoHandler(CapnprotoMessageHandler *successor)
        : CapnprotoMessageHandler(successor) {}

void AllocationAuthorityInfoHandler::handle(capnp::FlatArrayMessageReader &reader) {
    try {
        std::cout << AllocationAuthorityInfo::from(reader).toJson() << std::endl;
        return;
    } catch (std::runtime_error& e) {}
    catch (kj::Exception&) {}

    if(successor_ != nullptr) {
        successor_->handle(reader);
    } else {
        std::cout << "No matching handler available" << std::endl;
    }
}
