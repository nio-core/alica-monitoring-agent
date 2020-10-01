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
#include <storage/SawtoothCliBasedStorage.h>

void usage() {
    std::cout << "task-allocation-monitor <options>" << std::endl
              << "required options:" << std::endl
              << "\t-a, --address: IP address to bind the subscriber to." << std::endl
              << "\t-t, --topic: REPEATABLE, topics to join the subscriber to." << std::endl
              << "\t-C, --connect: ZMQ URI of the validator. Follows scheme <protocol>://<host>:<port>" << std::endl;
}

int main(int argc, char* argv[]) {
    std::string address;
    std::vector<std::string> topics;
    std::string validatorAddress;

    for(int i = 1; i < argc - 1; i++) {
        if(strcmp(argv[i], "--address") == 0 || strcmp(argv[i], "-a") == 0) {
            address = argv[++i];
        } else if(strcmp(argv[i], "--topic") == 0 || strcmp(argv[i], "-t") == 0) {
            topics.emplace_back(argv[++i]);
        } else if(strcmp(argv[i], "--connect") == 0 || strcmp(argv[i], "-C") == 0) {
            validatorAddress = argv[++i];
        } else {
            std::cout << "Skipping unknown argument " << argv[i] << std::endl;
        }
    }

    if(address.empty()) {
        std::cerr << "Task Allocation Monitor needs to be bound to an ADDRESS" << std::endl;
        return 1;
    }

    if(topics.empty()) {
        std::cerr << "No Topics supplied" << std::endl;
        return 2;
    }

    if(validatorAddress.empty()) {
        std::cerr << "Sawtooth Client needs address of validator" << std::endl;
        return 3;
    }

    SerializationStrategy* serializationStrategy = new JsonSerializationStrategy();
    StorageStrategy* storageStrategy = new SawtoothCliBasedStorage(validatorAddress);

    CapnprotoMessageHandler* alicaEngineInfoHandler = new AlicaEngineInfoHandler(serializationStrategy, storageStrategy);
    CapnprotoMessageHandler* allocationAuthorityInfoHandler = new AllocationAuthorityInfoHandler(serializationStrategy, storageStrategy);
    CapnprotoMessageHandler* planTreeInfoHandler = new PlanTreeInfoHandler(serializationStrategy, storageStrategy);
    CapnprotoMessageHandler* solverResultHandler = new SolverResultHandler(serializationStrategy, storageStrategy);
    CapnprotoMessageHandler* syncTalkHandler = new SyncTalkHandler(serializationStrategy, storageStrategy);
    CapnprotoMessageHandler* roleSwitchHandler = new RoleSwitchHandler(serializationStrategy, storageStrategy);
    CapnprotoMessageHandler* syncReadyHandler = new SyncReadyHandler(serializationStrategy, storageStrategy);

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

    delete serializationStrategy;
    delete storageStrategy;
    zmq_ctx_shutdown(ctx);
}