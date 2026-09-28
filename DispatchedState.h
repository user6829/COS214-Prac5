#ifndef DISPATCHEDSTATE_H
#define DISPATCHEDSTATE_H

#include "IncidentState.h"

class DispatchedState : public IncidentState
{
    public:
        void dispatch(Incident* incident);
        void contain(Incident* incident);
        void resolve(Incident* incident);
        string getName() const;
};























#endif DISPATCHEDSTATE_H