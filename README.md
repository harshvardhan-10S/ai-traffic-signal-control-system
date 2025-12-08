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
