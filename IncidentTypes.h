#ifndef INCIDENTTYPES_H
#define INCIDENTTYPES_H

enum class Event{
    UnitDispatched,
    CasualtyReported,
    BreachDetected,
    AreaLocked,
    AlertBroadcast,
    AlertCancelled
};

enum class Severity{
    Low,
    Medium,
    High,
    Critical
};

#endif