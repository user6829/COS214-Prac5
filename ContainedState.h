#ifndef CONTAINEDSTATE_H
#define CONTAINEDSTATE_H
#include "IncidentState.h"

class ContainedState : public IncidentState
{
    public:
        void dispatch(Incident* incident);
        void contain(Incident* incident);
        void resolve(Incident* incident);
        string getName() const;
};









#endif