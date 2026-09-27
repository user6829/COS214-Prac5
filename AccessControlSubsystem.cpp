#include "AccessControlSubsystem.h"
#include "IncidentMediator.h"
#include <iostream>

AccessControlSubsystem::AccessControlSubsystem(IncidentMediator* med)
    : Colleague(med) {}

void AccessControlSubsystem::lockArea(const std::string& areaId) {
    areaLockStatus[areaId] = true;
    std::cout<< "[AccessControl] Locked area: " << areaId << std::endl;
    if (mediator) {
        mediator->notify(this, Event::AreaLocked, areaId);
    }
}

void AccessControlSubsystem::unlockArea(const std::string& areaId) {
    areaLockStatus[areaId] = false;
    std::cout << "[AccessControl] Unlocked area: " << areaId << std::endl;
}

void AccessControlSubsystem::onBreachDetected(const std::string& areaId) {
    std::cout << "[AccessControl] Security breach detected at: " << areaId << std::endl;
    if (mediator) {
        mediator->notify(this, Event::BreachDetected, areaId);
    }
}

bool AccessControlSubsystem::isLocked(const std::string& areaId) const {
    auto it = areaLockStatus.find(areaId);
    if (it != areaLockStatus.end()) {
        return it->second;
    }
    return false;
}