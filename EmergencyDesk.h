#ifndef EMERGENCYDESK_H
#define EMERGENCYDESK_H

#include "Severity.h"
#include <map>
#include <string>

class ResponseUnitManager;
class AccessControlSubsystem;
class AlertService;
class OperatorConsole;
class Incident;

class EmergencyDesk {
private:
    std::map<std::string, Incident*> incidents;

public:
    EmergencyDesk(ResponseUnitManager& res, AccessControlSubsystem& acc, AlertService& alert, OperatorConsole& opc);
    void handleFireEmergency(const std::string& location, Severity level);
    void handleMedicalEmergency(const std::string& location, Severity level);
    void resolveIncident(const std::string& id);
};

#endif
