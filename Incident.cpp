#include "Incident.h"
#include "IncidentState.h"
#include "IncidentObserver.h"
#include "ReportedState.h"
#include <algorithm>

Incident::Incident(string id, string description, string location, int severity)
    : id(id), description(description), location(location), severity(severity)
{
    currentState = new ReportedState();
}

Incident::~Incident()
{
    delete currentState;
}

//--------------------obs-----------------------------------------------------------------
void Incident::attach(IncidentObserver* observer)
{
    observers.push_back(observer);
}

void Incident::detach(IncidentObserver* observer)
{
    observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
}

void Incident::notifyObservers()
{
    for (size_t i = 0; i < observers.size(); i++)
    {
        observers[i]->incidentUpdate(this);
    }
}

//-state part-----------------------------------------------------------------------------
void Incident::setState(IncidentState* state)
{
    delete currentState;
    currentState = state;
    notifyObservers();   // every transition automatically notifies so nothing is forgetten
}

void Incident::dispatch() { currentState->dispatch(this); }
void Incident::contain()  { currentState->contain(this); }
void Incident::resolve()  { currentState->resolve(this); }

string Incident::getStateName() const { return currentState->getName(); }

//------------------------------------------accessors -------------------------------------
string Incident::getId() const { return id; }
string Incident::getDescription() const { return description; }
string Incident::getLocation() const { return location; }
int Incident::getSeverity() const { return severity; }