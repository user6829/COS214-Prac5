#ifndef INCIDENTDASHBOARD_H
#define INCIDENTDASHBOARD_H
#include "IncidentObserver.h"

class IncidentDashboard : public IncidentObserver {
    public:
        void incidentUpdate(Incident* incident);
};



#endif