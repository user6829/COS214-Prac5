#ifndef EMERGENCYDESK_H
#define EMERGENCYDESK_H

#include "ResponseUnitManager.h"
#include "AccessControlSubsystem.h"
#include "AlertService.h"
#include "OperatorConsole.h"
#include "Incident.h"
#include "IncidentObserver.h"
#include <map>
#include <string>
#include <vector>

class EmergencyDesk {
private:
    ResponseUnitManager& responseUnits;
    AccessControlSubsystem& accessControl;
    AlertService& alertService;
    OperatorConsole& console;
    std::map<std::string, Incident*> incidents;
    std::vector<IncidentObserver*> observers;
    int nextId;

    Incident* registerIncident(const std::string& description, const std::string& location, Severity level);
    Incident* findIncident(const std::string& id);

public:
    EmergencyDesk(ResponseUnitManager& res, AccessControlSubsystem& acc, AlertService& alert, OperatorConsole& opc);
    ~EmergencyDesk();
    EmergencyDesk(const EmergencyDesk&) = delete;
    EmergencyDesk& operator=(const EmergencyDesk&) = delete;

    void addObserver(IncidentObserver* observer);
    std::string handleFireEmergency(const std::string& location, Severity level);
    std::string handleMedicalEmergency(const std::string& location, Severity level);
    void containIncident(const std::string& id);
    void resolveIncident(const std::string& id);
};

#endif