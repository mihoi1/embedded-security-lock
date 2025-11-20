# Embedded Security System (Bare-Metal AVR)

This project implements a hardware-level security controller on the AVR architecture (ATmega328P), designed to demonstrate low-level programming concepts without standard Arduino libraries.

## Features
* **Bare-Metal Implementation:** Direct register access for GPIO control (DDR, PORT, PIN registers).
* **Interrupt-Driven Panic Mode:** Uses Hardware Interrupts to interrupt the main loop for immediate alarm activation.
* **Non-Blocking Logic:** Avoids `delay()` for critical path execution.
* **Debouncing:** Implemented basic signal debouncing logic.

## Hardware Setup
* **MCU:** Arduino Uno R3
* **Inputs:** 2x Code Buttons (PD4, PD5), 1x Panic Button (PD2/INT0).
* **Outputs:** Green LED (PD6), Red LED (PD7).

## How it works
The system requires two buttons to be pressed simultaneously to unlock (Green LED). Pressing the Panic Button immediately triggers the ISR, locking the system in Alarm Mode (Red LED blinking) regardless of the main loop state.
