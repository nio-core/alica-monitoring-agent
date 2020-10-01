#include <capnzero/Subscriber.h>
#include <handler.h>

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

    CapnprotoMessageHandler* alicaEngineInfoHandler = new AlicaEngineInfoHandler();
    CapnprotoMessageHandler* allocationAuthorityInfoHandler = new AllocationAuthorityInfoHandler();
    CapnprotoMessageHandler* planTreeInfoHandler = new PlanTreeInfoHandler();
    CapnprotoMessageHandler* solverResultHandler = new SolverResultHandler();
    CapnprotoMessageHandler* syncTalkHandler = new SyncTalkHandler();
    CapnprotoMessageHandler* roleSwitchHandler = new RoleSwitchHandler();
    CapnprotoMessageHandler* syncReadyHandler = new SyncReadyHandler();

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