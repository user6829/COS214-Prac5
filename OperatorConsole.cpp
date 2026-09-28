#include "OperatorConsole.h"
#include <iostream>

OperatorConsole::OperatorConsole(IncidentMediator* med)
    : mediator(med) {}

OperatorConsole::~OperatorConsole() {
    for (Command* cmd : history) {
        delete cmd;
    }
    history.clear();
}

void OperatorConsole::setAndExecuteCommand(Command* cmd) {
    if (cmd) {
        cmd->execute();
        history.push_back(cmd);
    }
}

void OperatorConsole::undoLastCommand() {
    if (!history.empty()) {
        Command* lastCmd = history.back();
        lastCmd->undo();
        history.pop_back();
        delete lastCmd;
    } else {
        std::cout << "[OperatorConsole] No commands to undo." << std::endl;
    }
}

void OperatorConsole::showStatus(const std::string& message) {
    statusLog.push_back(message);
    std::cout << "[OperatorConsole Status] " << message << std::endl;
}

void OperatorConsole::printLog() {
    std::cout << "--- Operator Console Status Log ---" << std::endl;
    for (const auto& log : statusLog) {
        std::cout << "- " << log << std::endl;
    }
}