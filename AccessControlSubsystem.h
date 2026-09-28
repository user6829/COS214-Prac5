#ifndef ACCESSCONTROLSUBSYSTEM_H
#define ACCESSCONTROLSUBSYSTEM_H

#include "Colleague.h"
#include <string>
#include <map>

class AccessControlSubsystem:public Colleague {
private:
    std::map<std::string, bool> areaLockStatus;

public:
    explicit AccessControlSubsystem(IncidentMediator* med=nullptr);
    virtual ~AccessControlSubsystem()=default;

    void lockArea(const std::string& areaId);
    void unlockArea(const std::string& areaId);
    void onBreachDetected(const std::string& areaId);
    bool isLocked(const std::string& areaId) const;
};

#endif