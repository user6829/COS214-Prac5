#ifndef ALERTSERVICE_H
#define ALERTSERVICE_H

#include "Colleague.h"
#include "IncidentTypes.h"
#include <string>

class EmergencyNotifier;

class AlertService : public Colleague{
private:
    EmergencyNotifier* notifier;

public:
    explicit AlertService(IncidentMediator* med= nullptr, EmergencyNotifier* notif = nullptr);
    virtual ~AlertService()=default;

    void broadcastAlert(const std::string& message, const std::string& areaId, Severity level);
    void cancelAlert(const std::string& areaId);
};

#endif