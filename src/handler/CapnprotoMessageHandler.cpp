#include <handler/CapnprotoMessageHandler.h>
#include <conversion.h>
#include <iostream>

void CapnprotoMessageHandler::handle(capnp::FlatArrayMessageReader& reader) {
    try {
        std::cout << std::endl << AlicaEngineInfo::from(reader).toJson() << std::endl << std::endl;
        return;
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    } catch (kj::Exception&) {
        std::cout << "Error reading Engine Info" << std::endl;
    }

    try {
        std::cout << std::endl << AllocationAuthorityInfo::from(reader).toJson() << std::endl << std::endl;
        return;
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    } catch (kj::Exception&) {
        std::cout << "Error reading Allocation Authority Info" << std::endl;
    }

    try {
        std::cout << std::endl << PlanTreeInfo::from(reader).toJson() << std::endl << std::endl;
        return;
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    } catch (kj::Exception&) {
        std::cout << "Error reading Plan Tree Info" << std::endl;
    }

    try {
        std::cout << std::endl << SolverResult::from(reader).toJson() << std::endl << std::endl;
        return;
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    } catch (kj::Exception&) {
        std::cout << "Error reading Solver Result" << std::endl;
    }

    try {
        std::cout << std::endl << SyncTalk::from(reader).toJson() << std::endl << std::endl;
        return;
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    } catch (kj::Exception&) {
        std::cout << "Error reading Sync Talk" << std::endl;
    }

    try {
        std::cout << std::endl << RoleSwitch::from(reader).toJson() << std::endl << std::endl;
        return;
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    } catch (kj::Exception&) {
        std::cout << "Error reading Role Switch" << std::endl;
    }

    try {
        std::cout << std::endl << SyncReady::from(reader).toJson() << std::endl << std::endl;
        return;
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    } catch (kj::Exception&) {
        std::cout << "Error reading Sync Talk" << std::endl;
    }

    std::cout << "Could not parse message into available message types, skipping" << std::endl;
}
