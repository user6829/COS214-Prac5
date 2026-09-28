# CampusGuard: Emergency Response Coordination Platform

COS 214 - Practical 5 (2026)

## System Requirements
- Docker Engine (v20.10+) & Docker Compose (v2.0+)
- Alternatively: Linux environment with `g++` (C++11 support), `make`, and `valgrind`

---

## Docker Build & Run Instructions

### 1. Launch Full Application Build & Run (Mandatory Demonstration Target)
To build the image from scratch and launch the live application demonstration, run:
```bash
docker compose up --build

## Memory Management & Ownership Policy
- **Polymorphic Destruction**: All abstract base classes (`Command`, `Colleague`, `IncidentState`, `IncidentObserver`, `EmergencyNotifier`) define public virtual destructors to prevent undefined behavior upon polymorphic deletion.
- **Command Lifecycles**: `OperatorConsole` takes full ownership of queued `Command*` objects and deallocates them via `delete` upon undo operations or console destruction.
- **Mediator & Colleagues**: `CampusEmergencyMediator` maintains non-owning references to its colleague subsystems.
- **State & Observer Management**: `Incident` manages dynamic allocation for its active state, deallocating the prior state on transition, while maintaining non-owning observer registrations.