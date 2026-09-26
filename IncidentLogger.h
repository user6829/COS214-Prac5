#ifndef INCIDENTLOGGER_H
#define INCIDENTLOGGER_H
#include "IncidentObserver.h"
#include <vector>
#include <string>
using namespace std;

class IncidentLogger : public IncidentObserver {
    private:
        vector<string> history;

    public:
        void incidentUpdate(Incident* incident);
        void printHistory() const;
};




#endif INCIDENTLOGGER_H