#include <handler/CapnprotoMessageHandler.h>
#include <conversion.h>
#include <iostream>

CapnprotoMessageHandler::CapnprotoMessageHandler(CapnprotoMessageHandler *successor) : successor_(successor) {}
