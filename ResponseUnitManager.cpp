#include "ResponseUnitManager.h"
#include "IncidentMediator.h"
#include <iostream>

ResponseUnitManager::ResponseUnitManager(IncidentMediator* med)
    : Colleague(med) {}

void ResponseUnitManager::dispatch(const std::string& unitType, const std::string& location) {
    std::cout << "[ResponseUnits] Dispatching " << unitType << " unit to " << location << std::endl;
    if (mediator) {
        mediator->notify(this, Event::UnitDispatched, location);
    }
}

void ResponseUnitManager::recall(const std::string& unitType, const std::string& location) {
    std::cout << "[ResponseUnits] Recalling " << unitType << " unit from " << location << std::endl;
}

void ResponseUnitManager::onCasualtyReported(const std::string& location) {
    std::cout << "[ResponseUnits] Casualty reported at: " << location << std::endl;
    if (mediator) {
        mediator->notify(this, Event::CasualtyReported, location);
    }
}