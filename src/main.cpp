#include <capnzero/CapnZero.h>
#include <vector>
#include <string>
#include <AlicaEngineInfo.capnp.h>
#include <AllocationAuthorityInfo.capnp.h>
#include <PlanTreeInfo.capnp.h>
#include <RoleSwitch.capnp.h>
#include <SolverResult.capnp.h>
#include <SyncReady.capnp.h>
#include <SyncTalk.capnp.h>

void callback(::capnp::FlatArrayMessageReader& reader) {
    try {
        reader.getRoot<alica_msgs::AllocationAuthorityInfo>();
        std::cout << "+++ Received allocation authority information" << std::endl;
    } catch (std::exception& e) {
        std::cout << "--- Could not read allocation authority info from received message" << std::endl;
    }

    try {
        reader.getRoot<alica_msgs::AlicaEngineInfo>();
        std::cout << "+++ Received alica engine information" << std::endl;
    } catch (std::exception& e) {
        std::cout << "--- Could not read alica engine information from received message" << std::endl;
    }

    try {
        reader.getRoot<alica_msgs::PlanTreeInfo>();
        std::cout << "+++ Received plan tree information" << std::endl;
    } catch (std::exception& e) {
        std::cout << "--- Could not read plan tree information from received message" << std::endl;
    }

    try {
        reader.getRoot<alica_msgs::RoleSwitch>();
        std::cout << "+++ Received role switch" << std::endl;
    } catch (std::exception& e) {
        std::cout << "--- Could not read role switch from received message" << std::endl;
    }

    try {
        reader.getRoot<alica_msgs::SolverResult>();
        std::cout << "+++ Received solver result" << std::endl;
    } catch (std::exception& e) {
        std::cout << "--- Could not read solver result from received message" << std::endl;
    }

    try {
        reader.getRoot<alica_msgs::SyncReady>();
        std::cout << "+++ Received sync ready" << std::endl;
    } catch (std::exception& e) {
        std::cout << "--- Could not read sync ready from received message" << std::endl;
    }

    try {
        reader.getRoot<alica_msgs::SyncTalk>();
        std::cout << "+++ Received sync talk" << std::endl;
    } catch (std::exception& e) {
        std::cout << "--- Could not read sync talk from received message" << std::endl;
    }
}

void usage() {
    std::cout << "task-allocation-monitor <options>" << std::endl
              << "required options:" << std::endl
              << "\t-a, --address: IP address to bind the subscriber to." << std::endl
              << "\t-t, --topic: REPEATABLE, topics to join the subscriber to." << std::endl;
}

int main(int argc, char* argv[]) {
    std::string address;
    std::vector<std::string> topics;

    if(argc < 5) {
        std::cerr << "Invalid amount of arguments supplied" << std::endl;
        usage();
        return 1;
    }

    for(int i = 1; i < argc - 1; i++) {
        if(strcmp(argv[i], "--address") == 0 || strcmp(argv[i], "-a") == 0) {
            address = argv[++i];
        } else if(strcmp(argv[i], "--topic") == 0 || strcmp(argv[i], "-t") == 0) {
            topics.emplace_back(argv[++i]);
        } else {
            std::cout << "Skipping unknown argument " << argv[i] << std::endl;
        }
    }

    void* ctx = zmq_ctx_new();
    capnzero::Subscriber subscriber(ctx, capnzero::UDP);
    subscriber.addAddress(address);
    for(const std::string& topic : topics) {
        subscriber.setTopic(topic);
    }

    subscriber.subscribe(&callback);

    while(true);

    return 0;
}