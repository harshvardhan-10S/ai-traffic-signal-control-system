# Smart & AI-Integrated Traffic Light Signal Control System

This project implements an **AI-driven adaptive traffic signal control system** that adjusts signal timings in real time based on actual traffic density. It combines **YOLO-based vehicle detection**, **Python data processing**, and a **Master–Slave Arduino architecture** to control multi-directional traffic lights with hardware-level synchronization. 

---

## 1. Project Overview

Conventional traffic signals use fixed-time cycles that do not react to changing traffic conditions. This often leads to:

- Unnecessary waiting at red lights  
- Longer queues in high-density lanes  
- Higher fuel consumption and emissions  

This project addresses these limitations by designing an **adaptive signal controller** that:

- Measures real-time traffic density using a camera and YOLO  
- Computes optimal green-time durations dynamically  
- Distributes timing decisions to Slave controllers driving the traffic lights  
- Ensures precise synchronization between all directions at an intersection   

---

## 2. Key Objectives

- Replace static signal timing with **demand-based control**  
- Integrate **computer vision (YOLO)** for vehicle detection and counting  
- Design a **robust Master–Slave embedded control system** for signal driving  
- Achieve reliable synchronization across multiple traffic approaches  
- Reduce congestion, idle time, and fuel wastage at urban intersections :contentReference[oaicite:2]{index=2}  

---

## 3. System Architecture

The system is organized into three main layers:

### 3.1 Perception Layer – AI & Sensing

- A camera (e.g., smartphone or IP camera) captures live traffic at the junction.  
- A Python application runs a **YOLO model (e.g., YOLOv8)** to detect vehicles in each lane.  
- For every cycle, the system counts vehicles per direction and sends these counts to the Master controller via serial communication (USB/UART). :contentReference[oaicite:3]{index=3}  

### 3.2 Decision Layer – Master Controller

- A **Master Arduino** receives aggregated vehicle counts from Python.  
- For each approach (e.g., North–South, East–West), it calculates:

  ```text
  Green_Time = Base_Time + (Vehicle_Count × Time_Factor)
- The Master generates a signal plan for the next cycle (GREEN/YELLOW/RED durations for each direction).
- It sends configuration packets to Slave Arduinos and issues a synchronization (SYNC) pulse to align all controllers to the same time base.

### 3.3 Actuation Layer – Slave Controllers & Signal Hardware

- Two (or more) Slave Arduinos control the physical traffic lights for each road pair/direction.
- Each Slave receives:
- Its assigned GREEN/YELLOW/RED durations
- Sync trigger from the Master
- High-power LED signal modules are driven using MOSFETs (or driver circuits) with appropriate current limiting and protection.

### 4. Hardware Components

- Arduino (Master) – Decision making and synchronization
- Arduino (Slaves) – Local signal control for each road direction
- Camera – Video feed for vehicle detection
- LEDs / Traffic Light Modules – Red/Yellow/Green indicators
- MOSFETs / Driver Circuits – High-current LED driving
- Resistors, Wiring, Power Supply – Support electronics

### 5. Control Logic & Timing

A simplified version of the adaptive timing logic:
For each direction i:
Count_i = Vehicles detected (YOLO)
Green_i = Base_Green + k × Count_i

Normalize Green_i to keep total cycle length within limits:
Sum(Green_i) + Sum(Yellow_i) + All_Red ≈ Cycle_Time_Max

Schedule phases:
Direction 1 GREEN → Direction 1 YELLOW → All RED →
Direction 2 GREEN → Direction 2 YELLOW → All RED →

## 6. Features

- Adaptive traffic signal timing  
- Real-time YOLO-based vehicle detection  
- Master–Slave Arduino control  
- Hardware synchronization for precise timing  
- MOSFET-driven LED signal actuation  
- Scalable for 3-way and 4-way intersections  
- Modular architecture for easy upgrades

## 7. Benefits & Impact

- Reduced traffic congestion  
- Lower fuel consumption and vehicle idling  
- Improved flow efficiency during peak hours  
- Higher responsiveness than fixed-time signals  
- Supports smart-city intelligent transport system models

## 8. Repository Structure (Recommended)

ai-traffic-signal-control-system/
│
├── software/
│   ├── python/
│   │   ├── yolo_inference.py
│   │   └── serial_comm.py
│   └── arduino/
│       ├── master_controller/
│       │   └── master_controller.ino
│       └── slave_controller/
│           └── slave_controller.ino
│
├── hardware/
│   ├── schematics/
│   │   └── traffic_controller_schematic.pdf
│   └── layouts/
│       └── wiring_diagram.png
│
├── docs/
│   ├── Advanced-Traffic-Signal-Control-System.pptx
│   ├── EDI_Project_Report.pdf
│   └── system_architecture.md
│
├── media/
│   ├── demo_input_detection.mp4
│   ├── demo_traffic_control.mp4
│   └── images/
│       ├── block_diagram.png
│       ├── hardware_setup.png
│       └── sample_frames.png
│
└── README.md

## 9. How to Run

### 9.1 Prerequisites
- Python 3.x  
- OpenCV  
- YOLO weights (e.g., yolov8n.pt)  
- PySerial  
- Arduino IDE  

### 9.2 Steps

1. Upload Arduino codes to Master & Slaves  
2. Connect LEDs & MOSFET driver circuits  
3. Run YOLO script:
4. YOLO sends vehicle count → Arduino  
5. Master computes timings & syncs Slaves  
6. Traffic lights operate adaptively based on density

## 10. Future Scope

- Integration with cloud-based traffic analytics  
- Emergency vehicle (ambulance) detection  
- Pedestrian crossing module  
- Deployment on Jetson Nano / Coral TPU  
- App-based monitoring dashboard  
- AI-driven accident detection

## 11. Skills Demonstrated

- Computer Vision (YOLO)  
- Python automation & serial communication  
- Arduino embedded system design  
- Real-time control & synchronization  
- MOSFET driver design for high-power LEDs  
- Modular system architecture and documentation  

## 12. Author

**Harshvardhan Shinde**  
Electronics & Telecommunication Engineering  
Interest Areas: Computer Vision, IoT, Embedded Systems, Transport Automation
 
LinkedIn: https://www.linkedin.com/in/harshvardhan-shinde-063699345  
