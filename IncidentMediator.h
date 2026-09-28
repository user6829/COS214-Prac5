#ifndef INCIDENTMEDIATOR_H
#define INCIDENTMEDIATOR_H

#include "IncidentTypes.h"
#include <string>

class Colleague;

class IncidentMediator{
public:
    virtual ~IncidentMediator()=default;
    virtual void notify(Colleague* sender,Event event,const std::string& location) = 0;
};

#endif