#include "DispatchedState.h"
#include "ContainedState.h"
#include "Incident.h"
#include <iostream>
using namespace std;

void DispatchedState::dispatch(Incident* incident)
{
    cout << "[State] Rejected: incident " << incident->getId()
         << " has already been dispatched." << endl;
}

void DispatchedState::contain(Incident* incident)
{
    cout << "[State] Incident " << incident->getId() << " contained." << endl;
    incident->setState(new ContainedState());
}

void DispatchedState::resolve(Incident* incident)
{
    cout << "[State] Rejected: incident " << incident->getId()
         << " must be contained before it can be resolved." << endl;
}

string DispatchedState::getName() const { return "Dispatched"; }