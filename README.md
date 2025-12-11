# 🚦 Smart & AI-Integrated Traffic Control System

An AI-driven adaptive traffic signal system that adjusts signal timings in real time using **YOLO-based vehicle detection** and a **Master–Slave Arduino architecture**. Designed to reduce congestion and improve traffic flow at urban intersections.

---

## 1️⃣ Project Overview
This system replaces traditional fixed-time traffic lights with an **intelligent adaptive model**.  
A live camera feed is processed using YOLO to count vehicles, and signal timings are updated dynamically based on real-time road density.

**Key Highlights:**
- Real-time vehicle detection (YOLO)
- Dynamic signal timing
- Master–Slave Arduino control
- Hardware synchronization
- Scalable multi-road support

---

## 2️⃣ System Architecture

### 📷 **AI Detection Layer**
- YOLO processes live video to detect and count vehicles  
- Python computes traffic density per road  
- Data is transferred to the Master Arduino via serial communication  

### 🧠 **Decision Layer (Master Arduino)**
- Computes adaptive green time using:  
  `Green_Time = Base_Time + k × Vehicle_Count`
- Sends timing information to all Slave controllers  
- Generates a synchronization (SYNC) signal to align the start of every cycle  

### 🔌 **Actuation Layer (Slave Controllers)**
- Slave Arduinos control Red, Yellow, and Green LEDs  
- Execute timing cycles based on Master instructions  
- Run a state-machine sequence:
  - GREEN → YELLOW → RED  
- All Slaves stay synchronized using the Master’s SYNC pulse  

---

## 3️⃣ Features
- 🔹 Adaptive green-time allocation  
- 🔹 Real-time AI-based vehicle counting  
- 🔹 Master–Slave embedded control  
- 🔹 Multi-direction traffic light management  
- 🔹 Synchronized signal switching  
- 🔹 Efficient and modular architecture  

---

## 4️⃣ Circuit Diagram
Block diagram.png

The file must be located at: Block diagram.png

---

## 5️⃣ Project Structure
smart-ai-traffic-control-system/
│
├── software/
│ ├── python/
│ │ ├── yolo_inference.py
│ │ └── serial_comm.py
│ └── arduino/
│ ├── master_controller.ino
│ └── slave_controller.ino
│
├── hardware/
│ └── circuit_diagram.png
│
├── docs/
│ ├── project_presentation.pptx
│ └── report.pdf
│
└── README.md

---

## 6️⃣ How It Works (Step-by-Step)
1. 📸 YOLO detects vehicles from camera feed  
2. 🔢 Python counts vehicles per lane  
3. 🧠 Master Arduino computes green signal time  
4. 📤 Sends timing to Slave Arduinos  
5. ⚡ SYNC pulse aligns all controllers  
6. 🚦 Traffic signals operate adaptively based on density  

---

## 7️⃣ Future Enhancements
- Emergency vehicle detection  
- Pedestrian signal integration  
- Deployment on Nvidia Jetson / Edge TPU  
- Cloud-based monitoring dashboard  
- Multi-intersection coordination  


## 📊 System Architecture & Workflow

The following diagram represents the complete workflow of the **Smart & AI-Integrated Traffic Signal Control System**, showing how YOLO-based vehicle detection, air-quality monitoring, and Arduino-based signal control operate together in real time.

### 🔷 Flowchart / Architecture Diagram
![System Flowchart](media/system_flowchart.jpg)

### 📌 Key Highlights of the Architecture
- **Dual-lane real-time video processing** using YOLO for vehicle counting  
- **Python engine** handles detection logic + displays dashboard data  
- **Master Arduino UNO** executes timing algorithms based on density and air-quality  
- **I²C communication** enables synchronized operation across all Arduino controllers  
- **Slave Arduinos** manage independent signal control for each lane  
- **MQ135 sensor** continuously monitors air pollution levels (A0 input)  
- **Centralized logic** ensures adaptive, efficient, congestion-aware signal switching  

---

## 👤 Author
**Harshvardhan Shinde**  
Electronics & Telecommunication Engineering  
Focus: Embedded Systems • IoT • AI-Vision  

🔗 LinkedIn: https://www.linkedin.com/in/harshvardhan-shinde-063699345
