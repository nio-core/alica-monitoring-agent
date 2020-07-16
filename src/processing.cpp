#include <processing.h>
#include <iostream>
#include <AlicaEngineInfo.capnp.h>
#include <AllocationAuthorityInfo.capnp.h>
#include <PlanTreeInfo.capnp.h>
#include <RoleSwitch.capnp.h>
#include <SolverResult.capnp.h>
#include <SyncReady.capnp.h>
#include <SyncTalk.capnp.h>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>

std::string processing::try_read_alica_engine_info(::capnp::FlatArrayMessageReader& reader) {
    try {
        auto alica_engine_info = reader.getRoot<alica_msgs::AlicaEngineInfo>();
        std::cout << "+++ Received alica engine information" << std::endl;

        rapidjson::Document doc(rapidjson::kObjectType);
        rapidjson::Value obj(rapidjson::kObjectType);
        rapidjson::Value array(rapidjson::kArrayType);
        rapidjson::Value val;

        obj.AddMember("type", alica_engine_info.getSenderId().getType(), doc.GetAllocator());
        auto value = std::string(alica_engine_info.getSenderId().getValue().begin(), alica_engine_info.getSenderId().getValue().end());
        val.SetString(value.c_str(), static_cast<rapidjson::SizeType>(value.size()));
        obj.AddMember("value", val, doc.GetAllocator());
        doc.AddMember("senderId", obj, doc.GetAllocator());

        val.SetString(alica_engine_info.getCurrentPlan().cStr(), static_cast<rapidjson::SizeType>(alica_engine_info.getCurrentPlan().size()));
        doc.AddMember("currentPlan", val, doc.GetAllocator());

        val.SetString(alica_engine_info.getMasterPlan().cStr(), static_cast<rapidjson::SizeType>(alica_engine_info.getMasterPlan().size()));
        doc.AddMember("masterPlan", val, doc.GetAllocator());

        val.SetString(alica_engine_info.getCurrentState().cStr(), static_cast<rapidjson::SizeType>(alica_engine_info.getCurrentState().size()));
        doc.AddMember("currentState", val, doc.GetAllocator());

        val.SetString(alica_engine_info.getCurrentRole().cStr(), static_cast<rapidjson::SizeType>(alica_engine_info.getCurrentRole().size()));
        doc.AddMember("currentRole", val, doc.GetAllocator());

        val.SetString(alica_engine_info.getCurrentTask().cStr(), static_cast<rapidjson::SizeType>(alica_engine_info.getCurrentTask().size()));
        doc.AddMember("currentTask", val, doc.GetAllocator());

        for(auto agent: alica_engine_info.getAgentIdsWithMe()) {
            rapidjson::Value entry(rapidjson::kObjectType);
            entry.AddMember("type", agent.getType(), doc.GetAllocator());
            value = std::string(agent.getValue().begin(), agent.getValue().end());
            val.SetString(value.c_str(), static_cast<rapidjson::SizeType>(value.size()));
            entry.AddMember("value", val, doc.GetAllocator());
            array.PushBack(entry, doc.GetAllocator());
        }
        doc.AddMember("agentsWithMe", array, doc.GetAllocator());

        rapidjson::StringBuffer buffer;
        rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
        doc.Accept(writer);

        return buffer.GetString();
    } catch (std::exception& e) {
        std::cout << "--- Could not read alica engine information from received message" << std::endl;
        return "";
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