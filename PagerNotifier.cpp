#include "PagerNotifier.h"
#include <iostream>

bool PagerNotifier::notifyBuilding(const std::string& msg, Severity level, const std::string& building) {
    if (!base) {
        return false;
    }

    int zoneCode = zoneCodeOf(building);
    int urgency = urgencyFor(level);
    std::string trimmedMsg = trimToPagerLimit(msg);

    int result = base->transmitPage(zoneCode, trimmedMsg, urgency);
    return result == 0;
}

int PagerNotifier::urgencyFor(Severity level) const {
    switch (level) {
        case Severity::Low:      return 1;
        case Severity::Medium:   return 2;
        case Severity::High:     return 3;
        case Severity::Critical: return 4;
        default:                 return 1;
    }
}

int PagerNotifier::zoneCodeOf(const std::string& building) const {
    auto it = buildingZones.find(building);
    if (it != buildingZones.end()) {
        return it->second;
    }
    return 0; // Default fallback zone code
}

std::string PagerNotifier::trimToPagerLimit(const std::string& msg) const {
    const size_t PAGER_LIMIT = 160;
    if (msg.length() > PAGER_LIMIT) {
        return msg.substr(0, PAGER_LIMIT);
    }
    return msg;
}