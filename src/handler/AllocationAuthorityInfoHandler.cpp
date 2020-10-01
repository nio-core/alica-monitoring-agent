#include <handler/AllocationAuthorityInfoHandler.h>
#include <conversion.h>
#include <iostream>

bool AllocationAuthorityInfoHandler::doHandle(capnp::FlatArrayMessageReader &reader) {
    try {
        std::cout << conversion::AllocationAuthorityInfo::from(reader).toJson() << std::endl;
        return true;
    } catch (std::runtime_error&) {
        return false;
    } catch (kj::Exception&) {
        return false;
    }
}
