#ifndef COLLEAGUE_H
#define COLLEAGUE_H

class IncidentMediator;

class Colleague{
protected:
    IncidentMediator* mediator;

public:
    explicit Colleague(IncidentMediator* med=nullptr):mediator(med){}
    virtual ~Colleague()=default;

    void setMediator(IncidentMediator* med){
        this->mediator=med;
    }
};

#endif