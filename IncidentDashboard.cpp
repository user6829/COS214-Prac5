#include "IncidentDashboard.h"
#include "Incident.h"
#include <iostream>
using namespace std;

void IncidentDashboard::incidentUpdate(Incident* incident)
{
    cout << "[Dashboard] Incident " << incident->getId()
         << " (" << incident->getLocation() << ") is now: "
         << incident->getStateName() << endl;
}