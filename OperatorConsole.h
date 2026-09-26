#ifndef OPERATORCONSOLE_H
#define OPERATORCONSOLE_H

#include "Command.h"
#include <vector>
#include <string>
class IncidentMediator;

class OperatorConsole{
private:
    std::vector<std::string> statusLog;
    std::vector<Command*> history;
    IncidentMediator* mediator;

public:
    explicit OperatorConsole(IncidentMediator* med= nullptr);
    virtual ~OperatorConsole();
    void setAndExecuteCommand(Command* cmd);
    void undoLastCommand();
    void showStatus(const std::string& message);
    void printLog();
};

#endif