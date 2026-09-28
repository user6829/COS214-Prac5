#ifndef RESPONSEUNITMANAGER_H
#define RESPONSEUNITMANAGER_H

#include "Colleague.h"
#include <string>

class ResponseUnitManager :public Colleague{
public:
    explicit ResponseUnitManager(IncidentMediator* med=nullptr);
    virtual ~ResponseUnitManager()= default;

    void dispatch(const std::string& unitType, const std::string& location);
    void recall(const std::string& unitType, const std::string& location);
    void onCasualtyReported(const std::string& location);
};

#endif