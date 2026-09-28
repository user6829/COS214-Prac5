#include "ResolvedState.h"
#include "Incident.h"
#include <iostream>
using namespace std;

void ResolvedState::dispatch(Incident* incident)
{
    cout << "[State] Rejected: incident " << incident->getId() << " is already resolved." << endl;
}

void ResolvedState::contain(Incident* incident)
{
    cout << "[State] Rejected: incident " << incident->getId() << " is already resolved." << endl;
}

void ResolvedState::resolve(Incident* incident)
{
    cout << "[State] Rejected: incident " << incident->getId() << " is already resolved." << endl;
}

string ResolvedState::getName() const { return "Resolved"; }