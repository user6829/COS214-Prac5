#ifndef INCIDENT_H
#define INCIDENT_H

using namespace std;
#include <string>
#include <vector>

class IncidentObserver;
class IncidentState;

class Incident {

    private:

        string id;
        string description;
        string location;
        int severity;
        IncidentState* currentState;
        vector<IncidentObserver*> observers;

    public:

        Incident(string id, string description, string location, int severity);

        void attach(IncidentObserver* observer);
        void detach(IncidentObserver* observer);
        void notifyObservers();

        void setState(IncidentState* state);
        string getState();
        void contain();
        void resolve();
        void dispatch();

        string getID();
        string getDescription();
        string getLocation();
        int getSeverity();

        ~Incident();

};








#endif INCIDENT_H