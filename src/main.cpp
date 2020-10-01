#include <capnzero/Subscriber.h>
#include <serialization/JsonSerializationStrategy.h>
#include <handler/CapnprotoMessageHandler.h>
#include <handler/AlicaEngineInfoHandler.h>
#include <handler/AllocationAuthorityInfoHandler.h>
#include <handler/PlanTreeInfoHandler.h>
#include <handler/SolverResultHandler.h>
#include <handler/SyncTalkHandler.h>
#include <handler/RoleSwitchHandler.h>
#include <handler/SyncReadyHandler.h>

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

    SerializationStrategy* serializationStrategy = new JsonSerializationStrategy();

    CapnprotoMessageHandler* alicaEngineInfoHandler = new AlicaEngineInfoHandler(serializationStrategy);
    CapnprotoMessageHandler* allocationAuthorityInfoHandler = new AllocationAuthorityInfoHandler(serializationStrategy);
    CapnprotoMessageHandler* planTreeInfoHandler = new PlanTreeInfoHandler(serializationStrategy);
    CapnprotoMessageHandler* solverResultHandler = new SolverResultHandler(serializationStrategy);
    CapnprotoMessageHandler* syncTalkHandler = new SyncTalkHandler(serializationStrategy);
    CapnprotoMessageHandler* roleSwitchHandler = new RoleSwitchHandler(serializationStrategy);
    CapnprotoMessageHandler* syncReadyHandler = new SyncReadyHandler(serializationStrategy);

    alicaEngineInfoHandler->chain(allocationAuthorityInfoHandler)
                          ->chain(planTreeInfoHandler)
                          ->chain(solverResultHandler)
                          ->chain(syncTalkHandler)
                          ->chain(roleSwitchHandler)
                          ->chain(syncReadyHandler);

    void* ctx = zmq_ctx_new();
    capnzero::Subscriber subscriber(ctx, capnzero::UDP);
    subscriber.addAddress(address);
    for(const std::string& topic : topics) {
        subscriber.setTopic(topic);
    }

    subscriber.subscribe(&CapnprotoMessageHandler::handle, alicaEngineInfoHandler);

    while(true);
}