#include "ContainedState.h"
#include "ResolvedState.h"
#include "Incident.h"
#include <iostream>
using namespace std;

void ContainedState::dispatch(Incident* incident)
{
    cout << "[State] Rejected: incident " << incident->getId()
         << " has already moved past dispatch." << endl;
}

void ContainedState::contain(Incident* incident)
{
    cout << "[State] Rejected: incident " << incident->getId()
         << " has already been contained." << endl;
}

void ContainedState::resolve(Incident* incident)
{
    cout << "[State] Incident " << incident->getId() << " resolved." << endl;
    incident->setState(new ResolvedState());
}

string ContainedState::getName() const { return "Contained"; }