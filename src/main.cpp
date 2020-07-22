#include <vector>
#include <iostream>
#include <string>
#include <processing.h>
#include "../modules/capnzero/capnzero/include/capnzero/Subscriber.h"

void callback(::capnp::FlatArrayMessageReader& reader) {
    const std::string json;

    try {
        processing::alica_engine_info_capnproto_to_json(reader);
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }

    try {
        processing::allocation_authority_info_capnproto_to_json(reader);
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }

    try {
        processing::plan_tree_info_capnproto_to_json(reader);
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }

    try {
        processing::role_switch_capnproto_to_json(reader);
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }

    try {
        processing::solver_result_canproto_to_json(reader);
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }

    try {
        processing::sync_ready_capnproto_to_json(reader);
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }

    try {
        processing::sync_talk_capnproto_to_json(reader);
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }

    if(json.empty()) {
        std::cout << "Could not parse message into available message types, skipping" << std::endl;
    } else {
        std::cout << std::endl << json << std::endl << std::endl;
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