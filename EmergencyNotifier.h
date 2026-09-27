#ifndef EMERGENCYNOTIFIER_H
#define EMERGENCYNOTIFIER_H

#include <string>
#include "Severity.h"

class EmergencyNotifier {
public:
    virtual bool notifyBuilding(const std::string& msg, Severity level, const std::string& building) = 0;
    virtual ~EmergencyNotifier();
};

#endif
