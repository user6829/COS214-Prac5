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

//-------- network of collaborators --------
struct CampusNetwork {
	CampusEmergencyMediator mediator;
	AccessControlSubsystem accessControl;
	ResponseUnitManager responseUnits;
	PagerBaseStation pagerStation;// Adaptee aka legacy
	PagerNotifier pager;   // adapter
	AlertService alertService;
	OperatorConsole console; // command invoker
	EmergencyDesk desk; // facade
	IncidentDashboard dashboard;
	IncidentLogger logger;

	CampusNetwork()
		: accessControl(&mediator),
		  responseUnits(&mediator),
		  pager(&pagerStation),
		  alertService(&mediator, &pager),
		  console(&mediator),
		  desk(responseUnits, accessControl, alertService, console)
	{
		mediator.setAccessControl(&accessControl);
		mediator.setResponseUnitManager(&responseUnits);
		mediator.setAlertService(&alertService);

		desk.addObserver(&dashboard);
		desk.addObserver(&logger);
	}
};

//----------------------------------display helpers---------------------------------------------
void heading(const string& title) {
	cout << "\n-------- " << title << " --------" << endl;
}

void showLock(const AccessControlSubsystem& access, const string& area) {
	cout << "[Main] " << area << " locked? " << (access.isLocked(area) ? "yes" : "no") << endl;
}

//-------- section 1: fire emergency, FULL 6 PATTERNS --------
string FireEmergency(CampusNetwork& net) {
	heading("1. Facade + Mediator + Adapter + State + Observer: Fire reported");
	string fireId = net.desk.handleFireEmergency("Science Building", Severity::Critical);

	heading("2. Command + Mediator: operator reinforces the response");
	net.console.setAndExecuteCommand(new DispatchUnitCommand(&net.responseUnits, "Security Patrol", "Science Building"));
	net.console.setAndExecuteCommand(new EvacuateAreaCommand(&net.alertService, "Science Building", Severity::Critical));

	heading("3. State + Observer: fire contained");
	net.desk.containIncident(fireId);

	heading("4. Command undo: operator cancels evacuation order");
	net.console.undoLastCommand();

	heading("5. State + Observer: fire resolved");
	net.desk.resolveIncident(fireId);

	return fireId;
}

//-------- section 2: medical emergency and access breach --------
string MedicalEmergencyAndBreach(CampusNetwork& net) {
	heading("6. Facade: medical emergency, different runtime data");
	string medId = net.desk.handleMedicalEmergency("Library", Severity::High);

	heading("7. Command + Mediator + Adapter: operator locks down Library");
	net.console.setAndExecuteCommand(new LockdownAreaCommand(&net.accessControl, "Library"));
	showLock(net.accessControl, "Library");

	heading("8. Mediator: door sensor reports a breach");
	net.accessControl.onBreachDetected("Library");

	heading("9. Mediator: casualty reported, medics sent, doors reopened");
	net.responseUnits.onCasualtyReported("Library");
	showLock(net.accessControl, "Library");

	return medId;
}

//-------- section 3: invalid operations ---------------------------------
void InvalidOperations(CampusNetwork& net, const string& medId) {
	heading("10. State failure cases: invalid operations are rejected, not ignored");
	net.desk.resolveIncident(medId);    // rejected, not yet contained
	net.desk.resolveIncident("INC-99");     // rejected, unknown incident
	net.desk.containIncident(medId);
	net.desk.resolveIncident(medId);
	net.desk.containIncident(medId);    // rejected, already resolved
}

//-------- section 4: command undo history, including an empty history --------
void EndOfShiftRollback(CampusNetwork& net) {
	heading("11. Command undo: end-of-shift rollback, then empty history");
	net.console.undoLastCommand();          // lockdown
	net.console.undoLastCommand();          // dispatch security patrol
	net.console.undoLastCommand();          // history now empty
}

//-------- section 5: final observer and console records --------
void FinalRecords(CampusNetwork& net) {
	heading("12. Observer + Console records");
	net.logger.printHistory();
	net.console.printLog();
}

int main() {
	cout << "=====~~~~~~~~~~~~~~~~~~~~~ CampusGuard: Emergency Response Coordination ~~~~~~~~=====" << endl;

	CampusNetwork net;

	string fireId = FireEmergency(net);
	string medId = MedicalEmergencyAndBreach(net);
	InvalidOperations(net, medId);
	EndOfShiftRollback(net);
	FinalRecords(net);

	cout << "\n===== Done =====" << endl;
	return 0;
}