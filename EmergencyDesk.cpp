#include "EmergencyDesk.h"
#include <iostream>

EmergencyDesk::EmergencyDesk(ResponseUnitManager& res, AccessControlSubsystem& acc, AlertService& alert, OperatorConsole& opc)
    : responseUnits(res), accessControl(acc), alertService(alert), console(opc), nextId(1) {}

EmergencyDesk::~EmergencyDesk() {
    for (auto& entry : incidents) {
        delete entry.second;
    }
}

void EmergencyDesk::addObserver(IncidentObserver* observer) {
    observers.push_back(observer);
}

//
Incident* EmergencyDesk::registerIncident(const std::string& description, const std::string& location, Severity level) {
    std::string id = "INC-" + std::to_string(nextId++);
    Incident* incident = new Incident(id, description, location, static_cast<int>(level));
    for (IncidentObserver* observer : observers) {
        incident->attach(observer);
    }
    incidents[id] = incident;
    incident->notifyObservers();
    return incident;
}

Incident* EmergencyDesk::findIncident(const std::string& id) {
    auto it = incidents.find(id);
    if (it == incidents.end()) {
        std::cout << "[EmergencyDesk] Rejected: incident " << id << " not found." << std::endl;
        return nullptr;
    }
    return it->second;
}

//-------- facade
std::string EmergencyDesk::handleFireEmergency(const std::string& location, Severity level) {
    std::cout << "[EmergencyDesk] Handling Fire Emergency at: " << location << std::endl;

    Incident* incident = registerIncident("Fire", location, level);
    console.showStatus("Fire Emergency reported at " + location);
    accessControl.lockArea(location);
    alertService.broadcastAlert("Fire Emergency! Evacuate immediately.", location, level);
    responseUnits.dispatch("Fire Response", location);
    incident->dispatch();
    return incident->getId();
}

std::string EmergencyDesk::handleMedicalEmergency(const std::string& location, Severity level) {
    std::cout << "[EmergencyDesk] Handling Medical Emergency at: " << location << std::endl;

    Incident* incident = registerIncident("Medical", location, level);
    console.showStatus("Medical Emergency reported at " + location);
    alertService.broadcastAlert("Medical Emergency in progress. Clear the area.", location, level);
    responseUnits.dispatch("Medical Response", location);
    incident->dispatch();
    return incident->getId();
}

//-------- lifecycle
void EmergencyDesk::containIncident(const std::string& id) {
    Incident* incident = findIncident(id);
    if (incident) {
        incident->contain();
        console.showStatus("Incident " + id + " is now " + incident->getStateName());
    }
}

void EmergencyDesk::resolveIncident(const std::string& id) {
    Incident* incident = findIncident(id);
    if (incident) {
        incident->resolve();
        console.showStatus("Incident " + id + " is now " + incident->getStateName());
    }
}