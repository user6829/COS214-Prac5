#ifndef CAMPUSEMERGENCYMEDIATOR_H
#define CAMPUSEMERGENCYMEDIATOR_H

#include "IncidentMediator.h"
#include <vector>

class AccessControlSubsystem;
class ResponseUnitManager;
class AlertService;

class CampusEmergencyMediator:public IncidentMediator{
private:
    std::vector<Colleague*> colleagueList;
    AccessControlSubsystem* accessControl;
    ResponseUnitManager* responseUnitManager;
    AlertService* alertService;

public:
    CampusEmergencyMediator();
    virtual ~CampusEmergencyMediator()=default;

    void setAccessControl(AccessControlSubsystem* ac);
    void setResponseUnitManager(ResponseUnitManager* rm);
    void setAlertService(AlertService* as);

    void notify(Colleague* sender, Event event, const std::string& location) override;
};

#endif