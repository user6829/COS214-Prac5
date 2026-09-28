#include "ReportedState.h"
#include "DispatchedState.h"
#include "Incident.h"
#include <iostream>
using namespace std;

void ReportedState::dispatch(Incident* incident)
{
    cout << "[State] Incident " << incident->getId() << " dispatched." << endl;
    incident->setState(new DispatchedState());
}

void ReportedState::contain(Incident* incident)
{
    cout << "[State] Rejected: incident " << incident->getId()
         << " cannot be contained before it is dispatched." << endl;
}

void ReportedState::resolve(Incident* incident)
{
    cout << "[State] Rejected: incident " << incident->getId()
         << " cannot be resolved before it is dispatched." << endl;
}

string ReportedState::getName() const { return "Reported"; }