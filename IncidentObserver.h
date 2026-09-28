#ifndef INCIDENTOBSERVER_H
#define INCIDENTOBSERVER_H

using namecpace std;
#include <string>
class Incident;


class IncidentObserver {
    public:
        virtual void incidentUpdate(Incident* incident) = 0;
        virtual ~IncidentObserver() {};

    
};






#endif INCIDENTOBSERVER_H