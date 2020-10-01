#include <handler/PlanTreeInfoHandler.h>
#include <iostream>
#include <conversion.h>

bool PlanTreeInfoHandler::doHandle(capnp::FlatArrayMessageReader &reader) {
    try {
        std::cout << conversion::PlanTreeInfo::from(reader).toJson() << std::endl;
        return true;
    } catch (std::runtime_error&) {
        return false;
    } catch (kj::Exception&) {
        return false;
    }
}
