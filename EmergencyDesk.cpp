#include "EmergencyDesk.h"
#include <string>
#include <iostream>
using namespace std;

EmergencyDesk::EmergencyDesk(ResponseUnitManager& res, AccessControlSubsystem& acc, AlertService& alert, OperatorConsole& opc)
    : responseUnits(res), accessControl(acc), alertService(alert), console(opc) {}

void EmergencyDesk::handleFireEmergency(const std::string& location, Severity level) {
    std::cout << "[EmergencyDesk] Handling Fire Emergency at: " << location << std::endl;
    
    console.showStatus("Fire Emergency reported at " + location);
    accessControl.lockArea(location);
    alertService.broadcastAlert("Fire Emergency! Evacuate immediately.", location, level);
    responseUnits.dispatch("Fire Response", location);
}

void EmergencyDesk::handleMedicalEmergency(const std::string& location, Severity level) {
    std::cout << "[EmergencyDesk] Handling Medical Emergency at: " << location << std::endl;
    
    console.showStatus("Medical Emergency reported at " + location);
    alertService.broadcastAlert("Medical Emergency in progress. Clear the area.", location, level);
    responseUnits.dispatch("Medical Response", location);
}

void EmergencyDesk::resolveIncident(const std::string& id) {
    std::cout << "[EmergencyDesk] Resolving Incident ID: " << id << std::endl;
    
    auto it = incidents.find(id);
    if (it != incidents.end()) {
        Incident* inc = it->second;
        if (inc) {
            inc->resolve();
        }
        console.showStatus("Incident " + id + " has been resolved.");
    } else {
        std::cout << "[EmergencyDesk] Incident ID " << id << " not found." << std::endl;
    }
}