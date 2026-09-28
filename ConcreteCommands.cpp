#include "ConcreteCommands.h"
#include "AccessControlSubsystem.h"
#include "ResponseUnitManager.h"
#include "AlertService.h"

// LockdownAreaCommand
LockdownAreaCommand::LockdownAreaCommand(AccessControlSubsystem* r, const std::string& id)
    : receiver(r), areaId(id), previousState(false) {}

void LockdownAreaCommand::execute() {
    if (receiver) {
        previousState = receiver->isLocked(areaId);
        receiver->lockArea(areaId);
    }
}

void LockdownAreaCommand::undo() {
    if (receiver) {
        if (!previousState) {
            receiver->unlockArea(areaId);
        } else {
            receiver->lockArea(areaId);
        }
    }
}


// DispatchUnitCommand
DispatchUnitCommand::DispatchUnitCommand(ResponseUnitManager* r, const std::string& type, const std::string& loc)
    : receiver(r), unitType(type), location(loc) {}

void DispatchUnitCommand::execute() {
    if (receiver) {
        receiver->dispatch(unitType, location);
    }
}

void DispatchUnitCommand::undo() {
    if (receiver) {
        receiver->recall(unitType, location);
    }
}

// EvacuateAreaCommand
EvacuateAreaCommand::EvacuateAreaCommand(AlertService* r, const std::string& id, Severity lvl)
    : receiver(r), areaId(id), level(lvl) {}

void EvacuateAreaCommand::execute() {
    if (receiver) {
        receiver->broadcastAlert("EVACUATE AREA IMMEDIATELY", areaId, level);
    }
}

void EvacuateAreaCommand::undo() {
    if (receiver) {
        receiver->cancelAlert(areaId);
    }
}