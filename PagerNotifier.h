#ifndef PAGERNOTIFIER_H
#define PAGERNOTIFIER_H

#include "EmergencyNotifier.h"
#include "PagerBaseStation.h"
#include <map>
#include <string>

class PagerNotifier : public EmergencyNotifier {
private:
    PagerBaseStation* base;
    std::map<std::string, int> buildingZones;

public:
    explicit PagerNotifier(PagerBaseStation* station);
    virtual ~PagerNotifier() = default;

    bool notifyBuilding(const std::string& msg, Severity level, const std::string& building) override;
    int urgencyFor(Severity level) const;
    int zoneCodeOf(const std::string& building) const;
    std::string trimToPagerLimit(const std::string& msg) const;
};

#endif