#ifndef INCIDENTSTATE_H
#define INCIDENTSTATE_H

using namespace std;
#include <string>

class Incident;

class IncidentState {
    public:

        virtual void dispatch(Incident* incident) = 0;
        virtual void contain(Incident* incident) = 0;
        virtual void resolve(Incident* incident) = 0;
        virtual string getName() const = 0;
        virtual ~IncidentState() {}
};
















#endif