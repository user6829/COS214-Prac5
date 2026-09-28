//-------- main.cpp : CampusGuard end-to-end demonstration
#include <iostream>
#include <string>
#include "CampusEmergencyMediator.h"
#include "AccessControlSubsystem.h"
#include "ResponseUnitManager.h"
#include "AlertService.h"
#include "PagerBaseStation.h"
#include "PagerNotifier.h"
#include "OperatorConsole.h"
#include "ConcreteCommands.h"
#include "EmergencyDesk.h"
#include "IncidentDashboard.h"
#include "IncidentLogger.h"

using namespace std;

static void heading(const string& title)
{
    cout << "\n-------- " << title << " --------" << endl;
}

static void showLock(const AccessControlSubsystem& access, const string& area)
{
    cout << "[Main] " << area << " locked? " << (access.isLocked(area) ? "yes" : "no") << endl;
}

int main()
{
    //-------- Wiring (Mediator colleagues, Adapter, Facade, Observers)
    CampusEmergencyMediator mediator;
    AccessControlSubsystem accessControl(&mediator);
    ResponseUnitManager responseUnits(&mediator);

    PagerBaseStation pagerStation;          // Adaptee (legacy)
    PagerNotifier pager(&pagerStation);     // Adapter
    AlertService alertService(&mediator, &pager);

    mediator.setAccessControl(&accessControl);
    mediator.setResponseUnitManager(&responseUnits);
    mediator.setAlertService(&alertService);

    OperatorConsole console(&mediator);     // Command invoker
    EmergencyDesk desk(responseUnits, accessControl, alertService, console);   // Facade

    IncidentDashboard dashboard;
    IncidentLogger logger;
    desk.addObserver(&dashboard);
    desk.addObserver(&logger);

    //-------- Scenario 1: Fire in the Science Building
    heading("Scenario 1a: Facade + Mediator + Adapter + State + Observer");
    string fireId = desk.handleFireEmergency("Science Building", Severity::Critical);

    heading("Scenario 1b: Command + Mediator (operator reinforces the response)");
    console.setAndExecuteCommand(new DispatchUnitCommand(&responseUnits, "Security Patrol", "Science Building"));
    console.setAndExecuteCommand(new EvacuateAreaCommand(&alertService, "Science Building", Severity::Critical));

    heading("Scenario 1c: State + Observer (fire contained)");
    desk.containIncident(fireId);

    heading("Scenario 1d: Command undo (operator cancels evacuation order)");
    console.undoLastCommand();

    heading("Scenario 1e: State + Observer (fire resolved)");
    desk.resolveIncident(fireId);

    //-------- Scenario 2: Medical emergency and breach at the Library
    heading("Scenario 2a: Facade (medical emergency, different runtime data)");
    string medId = desk.handleMedicalEmergency("Library", Severity::High);

    heading("Scenario 2b: Command + Mediator + Adapter (operator locks down Library)");
    console.setAndExecuteCommand(new LockdownAreaCommand(&accessControl, "Library"));
    showLock(accessControl, "Library");

    heading("Scenario 2c: Mediator (door sensor reports a breach)");
    accessControl.onBreachDetected("Library");

    heading("Scenario 2d: Mediator (casualty reported: medics sent, doors reopened)");
    responseUnits.onCasualtyReported("Library");
    showLock(accessControl, "Library");

    heading("Scenario 2e: State failure cases (invalid operations are reported)");
    desk.resolveIncident(medId);        // rejected: not yet contained
    desk.resolveIncident("INC-99");     // rejected: unknown incident
    desk.containIncident(medId);
    desk.resolveIncident(medId);
    desk.containIncident(medId);        // rejected: already resolved

    heading("Scenario 2f: Command undo (end of shift rollback, then empty history)");
    console.undoLastCommand();          // lockdown
    console.undoLastCommand();          // dispatch security patrol
    console.undoLastCommand();          // nothing left

    //-------- Final records
    heading("Observer + Console records");
    logger.printHistory();
    console.printLog();

    return 0;
}