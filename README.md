# Closed-Loop DC Motor Speed Control

## Project Overview

This project focuses on the simulation and development of a closed-loop DC motor speed control system. A feedback-based control approach is used to monitor motor speed and adjust the control input to achieve the desired speed. The project covers motor modeling, PWM generation, encoder feedback, PID control, and final system simulation.

## Objective

To design and simulate a closed-loop DC motor speed control system that demonstrates how feedback and PID control can be used to regulate motor speed under changing operating conditions.

## Key Features

- DC motor mathematical modeling
- PWM-based motor control
- Encoder-based speed feedback
- PID controller implementation
- Closed-loop speed regulation
- Simulation and response analysis
- Final system integration

## System Workflow

Reference Speed  
↓  
PID Controller  
↓  
PWM Control  
↓  
DC Motor Model  
↓  
Encoder / Speed Feedback  
↓  
Error Calculation  
↺

## Project Structure

```text
TI_Motor_Control_Project/
│
├── 02_Motor_Model/
├── 03_PWM/
├── 04_Encoder/
├── 05_PID/
├── 06_Final_Simulation/
└── 07_Documentation/