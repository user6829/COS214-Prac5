#include "IncidentLogger.h"
#include "Incident.h"
#include <iostream>
using namespace std;

void IncidentLogger::incidentUpdate(Incident* incident)
{
    string entry = "Incident " + incident->getId() + " -> " + incident->getStateName();
    history.push_back(entry);
}

void IncidentLogger::printHistory() const
{
    cout << "[Logger] History:" << endl;
    for (size_t i = 0; i < history.size(); i++)
    {
        cout << "  " << history[i] << endl;
    }
}