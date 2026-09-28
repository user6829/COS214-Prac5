#ifndef RESOLVEDSTATE_H
#define RESOLVEDSTATE_H


#include "IncidentState.h"

class ResolvedState : public IncidentState
{
    public:
        void dispatch(Incident* incident);
        void contain(Incident* incident);
        void resolve(Incident* incident);
        string getName() const;
};

#endif