#ifndef INCIDENTSTATE_H
#define INCIDENTSTATE_H

using namespace std;
#include <string>

class Incident;

class IncidentState {
    public:


        void dispatch(Incident* incident) = 0;
        void resolve(Incident* incident) = 0;
        void contain(Incident* incident) = 0;

        string getName() const = 0;



        virtual ~IncidentState() {}
};
















#endif INCIDENTSTATE_H