#include "AlertService.h"
#include "EmergencyNotifier.h"
#include "IncidentMediator.h"
#include <iostream>

AlertService::AlertService(IncidentMediator* med, EmergencyNotifier* notif)
    : Colleague(med), notifier(notif) {}

void AlertService::broadcastAlert(const std::string& message, const std::string& areaId, Severity level) {
    std::cout << "[AlertService] Broadcast alert for " << areaId
              << " | Level: " << static_cast<int>(level)
              << " | Message: " << message << std::endl;

    if (notifier && !notifier->notifyBuilding(message, level, areaId)) {
        std::cout << "[AlertService] Warning: pager delivery failed for " << areaId << std::endl;
    }

    if (mediator) {
        mediator->notify(this, Event::AlertBroadcast, areaId);
    }
}

void AlertService::cancelAlert(const std::string& areaId) {
    std::cout << "[AlertService] Alert cancelled for area: " << areaId << std::endl;
    if (mediator) {
        mediator->notify(this, Event::AlertCancelled, areaId);
    }
}