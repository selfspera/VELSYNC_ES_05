# VELSYNC_ES_05

# Smart Health Monitoring System (IoT)

## Objective
To build a real-time IoT-based health monitoring system that tracks vital parameters and uploads data to the cloud.

## Components Used
- ESP32 Dev Board
- DHT11 Temperature Sensor
- HW-827 Pulse Sensor
- Active Buzzer
- Breadboard & Jumper Wires

## Working
The ESP32 reads temperature and heart rate data from sensors.  
The collected data is uploaded to Firebase Realtime Database for live monitoring.  
If any parameter crosses a predefined threshold, a local alert is generated using a buzzer.

## Cloud Integration
Firebase Realtime Database is used to store and visualize real-time sensor data.

## Alert Logic
- Temperature > 38°C → Alert
- Heart Rate < 50 BPM or > 120 BPM → Alert

## Result
The system successfully monitors health parameters in real time and logs them to the cloud.

## Conclusion
This project demonstrates an end-to-end IoT health monitoring solution using ESP32 and Firebase.
