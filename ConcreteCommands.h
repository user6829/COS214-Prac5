#ifndef CONCRETECOMMANDS_H
#define CONCRETECOMMANDS_H

#include "Command.h"
#include "IncidentTypes.h"
#include <string>

class AccessControlSubsystem;
class ResponseUnitManager;
class AlertService;

class LockdownAreaCommand:public Command{
private:
    AccessControlSubsystem* receiver;
    std::string areaId;
    bool previousState;

public:
    LockdownAreaCommand(AccessControlSubsystem* r, const std::string& id);
    virtual ~LockdownAreaCommand()=default;

    void execute() override;
    void undo() override;
};

class DispatchUnitCommand:public Command{
private:
    ResponseUnitManager* receiver;
    std::string unitType;
    std::string location;

public:
    DispatchUnitCommand(ResponseUnitManager* r, const std::string& type, const std::string& loc);
    virtual ~DispatchUnitCommand()= default;

    void execute() override;
    void undo() override;
};

class EvacuateAreaCommand:public Command{
private:
    AlertService* receiver;
    std::string areaId;
    Severity level;

public:
    EvacuateAreaCommand(AlertService* r, const std::string& id, Severity lvl);
    virtual ~EvacuateAreaCommand()=default;

    void execute() override;
    void undo() override;
};

#endif