#include "CampusEmergencyMediator.h"
#include "AccessControlSubsystem.h"
#include "ResponseUnitManager.h"
#include "AlertService.h"
#include <iostream>

CampusEmergencyMediator::CampusEmergencyMediator()
    : accessControl(nullptr), responseUnitManager(nullptr), alertService(nullptr) {}

void CampusEmergencyMediator::setAccessControl(AccessControlSubsystem* ac) {
    accessControl = ac;
    colleagueList.push_back(ac);
}

void CampusEmergencyMediator::setResponseUnitManager(ResponseUnitManager* rm) {
    responseUnitManager = rm;
    colleagueList.push_back(rm);
}

void CampusEmergencyMediator::setAlertService(AlertService* as) {
    alertService = as;
    colleagueList.push_back(as);
}

void CampusEmergencyMediator::notify(Colleague* sender, Event event, const std::string& location) {
    switch (event) {
        case Event::BreachDetected:
            std::cout << "[Mediator] Breach detected event handled. Dispatching security & sounding alert." << std::endl;
            if (responseUnitManager && sender != responseUnitManager) {
                responseUnitManager->dispatch("Armed Security", location);
            }
            if (alertService && sender != alertService) {
                alertService->broadcastAlert("Perimeter Breach! Shelter in place.", location, Severity::High);
            }
            break;

        case Event::AreaLocked:
            std::cout << "[Mediator] Area locked event handled. Broadcasting warning to area." << std::endl;
            if (alertService && sender != alertService) {
                alertService->broadcastAlert("Area is locked down. Remain calm.", location, Severity::Medium);
            }
            break;

        case Event::CasualtyReported:
            std::cout << "[Mediator] Casualty reported event handled. Opening doors for medics." << std::endl;
            if (responseUnitManager && sender != responseUnitManager) {
                responseUnitManager->dispatch("Medical Emergency Unit", location);
            }
            if (accessControl && sender != accessControl) {
                accessControl->unlockArea(location);
            }
            break;

        case Event::UnitDispatched:
            std::cout << "[Mediator] Unit dispatched to " << location << ". Notifying central logs." << std::endl;
            break;

        case Event::AlertBroadcast:
        case Event::AlertCancelled:
            std::cout << "[Mediator] Alert status updated for " << location << std::endl;
            break;

        default:
            break;
    }
}