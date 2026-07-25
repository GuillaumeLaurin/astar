# Autonomous Delivery Drone (F' / NASA GDS)

An autonomous multirotor drone project built on [NASA's F' (F Prime)](https://github.com/nasa/fprime) flight software framework, operated and monitored through the NASA Ground Data System (GDS). This is a personal engineering project used to gain hands-on aerospace / embedded systems experience across software, electrical, mechanical, and systems engineering disciplines.

> ⚠️ **Status: Early development / learning project.** The system is being built incrementally, starting from a minimal F' software skeleton before any real flight hardware is involved. See [Roadmap](#roadmap) below.

---

## Overview

| | |
|---|---|
| **Airframe** | Multirotor (quad/hex), VTOL |
| **Mission** | Last-mile autonomous payload delivery |
| **Autonomy level** | Full autonomy with real-time obstacle detection & avoidance |
| **Flight software** | [F' (F Prime)](https://fprime.jpl.nasa.gov/) |
| **Ground segment** | NASA GDS |
| **Payload capacity (target)** | ~3 kg |
| **MTOW (target)** | ≤ 25 kg |

The drone receives a mission plan (waypoints + delivery point) from the ground station, flies the mission fully autonomously — including local obstacle avoidance and re-planning — performs a precision landing/descent at the delivery point, releases its payload, and returns, all without manual intervention under nominal conditions. A hardware kill switch / manual RC override remains independent of the F' software stack at all times.

## Key Features (planned)

- [ ] Autonomous end-to-end mission execution (takeoff → delivery → return)
- [ ] Real-time obstacle detection and local re-planning (stereo/LiDAR fusion)
- [ ] GPS-denied fallback via visual-inertial odometry
- [ ] Geofencing with hard enforcement
- [ ] Battery-aware automatic Return-To-Home (RTH)
- [ ] F' native FDIR (Fault Detection, Isolation, and Recovery)
- [ ] Full command/telemetry/event integration with NASA GDS
- [ ] Independent hardware kill switch (manual override, bypasses F')

## System Architecture

The software is organized as an F' topology composed of the following functional modules. See [`docs/architecture.md`](docs/architecture.md) *(or the project requirements workbook)* for the full breakdown of F' components per module.

```
Ground Segment (NASA GDS)
        │  telemetry link (Cmd / Tlm / Evr)
        ▼
Companion Computer — F' Flight Software
 ├── Communications (Svc::CmdDispatcher, Svc::TlmChan, Svc::ActiveLogger)
 ├── Software Core (topology, rate groups, Svc::Health / FDIR, Svc::PrmDb)
 ├── Mission Manager / Path Planning (mission sequencing, obstacle avoidance re-planning, geofence)
 ├── Navigation & Guidance (state estimation, attitude/position control)
 ├── Perception (obstacle detection & classification)
 └── Payload Manager (release mechanism, precision landing)
        │  MAVLink / UART
        ▼
Low-level Flight Controller (attitude stabilization, motor mixing)
 ├── IMU / GPS / Barometer / Magnetometer
 ├── ESCs / Motors
 └── Independent RC receiver (manual override / kill switch — safety-critical, bypasses companion computer)
```

## Tech Stack

- **Flight software:** F' (F Prime) — C++ / Python component definitions
- **Ground software:** NASA GDS
- **Low-level flight control:** MAVLink-compatible autopilot (TBD)
- **Companion computer:** TBD (e.g. Raspberry Pi / Jetson-class SBC)
- **Simulation:** F' SIL (software-in-the-loop) before any hardware-in-the-loop or flight testing

## Repository Structure

```
.
├── Deployment/           # F' deployment(s) — topology, main entry point
├── Components/           # Custom F' components (one folder per component)
├── docs/                 # Design & engineering documentation
│   ├── requirements/     # Requirements traceability matrix, ICD, BOM, test matrix, risk register
│   └── architecture.md   # Architecture & module breakdown
├── config/                # Configuration, parameter (Prm) defaults
├── test/                 # SIL / HIL test scripts and scenarios
└── README.md
```

*(Structure will evolve as the F' topology skeleton is built out — see Roadmap.)*

## Getting Started

### Prerequisites

- Python 3.9+
- [F' (F Prime)](https://fprime.jpl.nasa.gov/latest/docs/getting-started/installing-fprime/) framework and CLI tools (`fprime-bootstrap`, `fprime-util`)
- NASA GDS (bundled with F' tooling)
- A C++ toolchain (for building F' deployments)

### Setup

```bash
# Clone the repository
git clone <repo-url>
cd <repo-name>

# Set up a Python virtual environment for F' tooling
python3 -m venv fprime-venv
source fprime-venv/bin/activate
pip install fprime-bootstrap

# Build the deployment (software-in-the-loop target first)
fprime-util build

# Launch the deployment together with the GDS
fprime-gds
```

> Detailed build/run instructions will be filled in as the deployment skeleton is committed.

## Roadmap

The project follows an incremental crawl-walk-run validation approach rather than building the full system at once:

| Phase | Goal |
|---|---|
| **0 — SIL** | Minimal F' topology skeleton running in simulation, validated against the GDS (no hardware) |
| **1 — Manual flight + telemetry** | Manual RC flight with F'/GDS telemetry chain validated, kill switch verified |
| **2 — Supervised waypoints** | Autonomous waypoint following under continuous operator supervision |
| **3 — Obstacle avoidance** | Perception + local re-planning introduced in a controlled test environment |
| **4 — Full autonomous delivery** | End-to-end mission: navigation, avoidance, precision landing, payload release, return |

Engineering reviews (SRR → PDR → CDR → TRR → FRR) are tracked alongside these phases — see the project's requirements documentation for entry/exit criteria per milestone.

## Safety

This project involves a real flying vehicle. At minimum:

- An independent, F'-agnostic RC receiver provides manual override / kill switch capability at all times.
- No autonomous flight testing is performed without a designated safety pilot and a pre-flight checklist.
- Geofencing and automatic RTH-on-low-battery are treated as safety-critical requirements, not optional features.

## Documentation

Full requirements traceability (IDs, priorities, verification methods), the module architecture breakdown, BOM, Interface Control Document (ICD), test matrix, risk register, and review milestones are maintained in the project's requirements workbook under `docs/requirements/`.

## Acknowledgments

- [NASA F' (F Prime)](https://github.com/nasa/fprime) flight software framework
- NASA Ground Data System (GDS)

## License

This project is licensed under the **Apache License, Version 2.0** — see the [`LICENSE`](LICENSE) file for the full text.

```
Copyright [2026] [Guillaume Laurin]

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
```