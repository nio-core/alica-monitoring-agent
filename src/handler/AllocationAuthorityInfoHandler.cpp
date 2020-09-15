#include <handler/AllocationAuthorityInfoHandler.h>
#include <conversion.h>
#include <iostream>

void AllocationAuthorityInfoHandler::handle(capnp::FlatArrayMessageReader &reader) {
    try {
        std::cout << std::endl << AllocationAuthorityInfo::from(reader).toJson() << std::endl << std::endl;
        return;
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    } catch (kj::Exception&) {
        std::cout << "Error reading Allocation Authority Info" << std::endl;
    }
}

AllocationAuthorityInfoHandler::AllocationAuthorityInfoHandler(CapnprotoMessageHandler *successor)
        : CapnprotoMessageHandler(successor) {}
