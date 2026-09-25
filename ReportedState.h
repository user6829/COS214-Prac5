#ifndef REPORTEDSTATE_H
#define REPORTEDSTATE_HSTATE_H
#include "IncidentState.h"

class ReportedState : public IncidentState
{
    public:
        void dispatch(Incident* incident);
        void contain(Incident* incident);
        void resolve(Incident* incident);
        string getName() const;
};












#endif REPORTEDSTATE_HSTATE_H