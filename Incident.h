#ifndef INCIDENT_H
#define INCIDENT_H


#include <string>
#include <vector>
using namespace std;

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
        void contain();
        void resolve();
        void dispatch();

        string getStateName() const;
        string getId() const;
        string getDescription() const;
        string getLocation() const;
        int getSeverity() const;

        ~Incident();

};








#endif