#include <processing.h>
#include <iostream>
#include <AlicaEngineInfo.capnp.h>
#include <AllocationAuthorityInfo.capnp.h>
#include <PlanTreeInfo.capnp.h>
#include <RoleSwitch.capnp.h>
#include <SolverResult.capnp.h>
#include <SyncReady.capnp.h>
#include <SyncTalk.capnp.h>

void processing::try_read_alica_engine_info(::capnp::FlatArrayMessageReader& reader) {
    try {
        reader.getRoot<alica_msgs::AlicaEngineInfo>();
        std::cout << "+++ Received alica engine information" << std::endl;
    } catch (std::exception& e) {
        std::cout << "--- Could not read alica engine information from received message" << std::endl;
    }
}

void processing::try_read_allocation_authority_information(::capnp::FlatArrayMessageReader &reader) {
    try {
        auto allocation_authority_information = reader.getRoot<alica_msgs::AllocationAuthorityInfo>();
        std::cout << "+++ Received allocation authority information" << std::endl;
    } catch (std::exception& e) {
        std::cout << "--- Could not read allocation authority info from received message" << std::endl;
    }
}

void processing::try_read_plan_tree_information(::capnp::FlatArrayMessageReader &reader) {
    try {
        reader.getRoot<alica_msgs::PlanTreeInfo>();
        std::cout << "+++ Received plan tree information" << std::endl;
    } catch (std::exception& e) {
        std::cout << "--- Could not read plan tree information from received message" << std::endl;
    }
}

void processing::try_read_role_switch(::capnp::FlatArrayMessageReader &reader) {
    try {
        reader.getRoot<alica_msgs::RoleSwitch>();
        std::cout << "+++ Received role switch" << std::endl;
    } catch (std::exception& e) {
        std::cout << "--- Could not read role switch from received message" << std::endl;
    }
}

void processing::try_read_solver_result(::capnp::FlatArrayMessageReader &reader) {
    try {
        reader.getRoot<alica_msgs::SolverResult>();
        std::cout << "+++ Received solver result" << std::endl;
    } catch (std::exception& e) {
        std::cout << "--- Could not read solver result from received message" << std::endl;
    }
}

void processing::try_read_sync_ready(::capnp::FlatArrayMessageReader &reader) {
    try {
        reader.getRoot<alica_msgs::SyncReady>();
        std::cout << "+++ Received sync ready" << std::endl;
    } catch (std::exception& e) {
        std::cout << "--- Could not read sync ready from received message" << std::endl;
    }
}

void processing::try_read_sync_talk(::capnp::FlatArrayMessageReader &reader) {
    try {
        reader.getRoot<alica_msgs::SyncTalk>();
        std::cout << "+++ Received sync talk" << std::endl;
    } catch (std::exception& e) {
        std::cout << "--- Could not read sync talk from received message" << std::endl;
    }
}