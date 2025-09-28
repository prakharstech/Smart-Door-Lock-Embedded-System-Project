# 🔐 Password-Based Smart Door Lock

An Embedded Systems Lab project for ICT 2223, designed to enhance access control and security using **password authentication** with an ARM Cortex-M3 (LPC1768) microcontroller.

---

## 📘 Overview

The **Password-Based Smart Door Lock** replaces traditional lock-and-key mechanisms with a **secure 4-digit password system**. Users enter a password via a 4x4 keypad, and the LPC1768 verifies it against a stored password.

* ✅ **Correct password** → LCD displays success message & stepper motor unlocks the door.
* ❌ **Incorrect password** → LCD shows error & buzzer activates, with increasing timeout delays.

This project demonstrates the integration of **keypad input, LCD output, motor control, and buzzer alerts** in a compact embedded system.

---

## 🎯 Objectives

* Provide secure, password-based access control.
* Demonstrate microcontroller interfacing with multiple peripherals.
* Create a cost-effective and reliable smart lock prototype.

---

## 🌟 Features

* 🔢 **4-Digit Password Authentication**
* ⚡ **Stepper Motor** simulates door lock/unlock mechanism
* 📺 **LCD Display** shows real-time status (success/error)
* 🚨 **Buzzer Alert** for incorrect attempts
* ⏱️ **Timeout Mechanism** (delay increases after repeated wrong attempts)

---

## 🛠️ Hardware Components

| Component                    | Description                                   |
| ---------------------------- | --------------------------------------------- |
| **LPC1768 Microcontroller**  | ARM Cortex-M3 MCU used for core control logic |
| **4x4 Matrix Keypad**        | User input for entering password              |
| **Stepper Motor (28BYJ-48)** | Simulates locking/unlocking action            |
| **LCD Display (16x2)**       | Displays authentication status                |
| **Buzzer**                   | Audio feedback on incorrect password          |
| **Power Supply**             | Regulated 3.3V/5V for logic and motor         |
| **ULN2003 Driver Module**    | Drives stepper motor safely                   |

---

## 🔌 Pin Configuration

| Component         | Pin                | LPC1768 GPIO Pin |
| ----------------- | ------------------ | ---------------- |
| **LCD Display**   | RS                 | P0.27            |
|                   | E (Enable)         | P0.28            |
|                   | Data Lines (D4–D7) | P0.23 – P0.26    |
| **Keypad**        | Rows               | P2.10 – P2.13    |
|                   | Columns            | P1.23 – P1.26    |
| **Stepper Motor** | IN1 – IN4          | P0.4 – P0.7      |
| **Buzzer**        | Control            | P0.15            |

---

## 🧱 System Architecture

```text
+--------------------------+
|   4x4 Keypad             |
+--------------------------+
            |
            v
+----------------------------+
|   LPC1768 Microcontroller  |
| - Password Verification    |
| - LCD Feedback             |
| - Stepper Motor Control    |
| - Buzzer Control           |
+----------------------------+
      |              |
      v              v
+-----------+   +------------+
| Stepper   |   |   LCD      |
| Motor     |   |   Display  |
+-----------+   +------------+
       |
       v
+-----------+
|   Buzzer  |
+-----------+
```

---

## 🔑 Default Password

```text
7 4 6 2
```

---

## 🖥️ Software Environment

* **Programming Language:** C
* **IDE:** Keil µVision (or ARM-compatible toolchain)
* **Drivers:** LPC17xx CMSIS library
* **Programmer Tool:** Flash Magic (for LPC1768)

---

## 🧪 Results & Relevance

* ✅ Secure password-based access control
* ✅ Smooth stepper motor control for door simulation
* ✅ Real-time LCD messages for feedback
* ✅ Buzzer alerts prevent brute-force entry
* ✅ Timeout mechanism strengthens security

---

## 👨‍💻 Team

* Prakhar Srivastava – 230911246
* Tanay Aggarwal – 230911278
* Raghav Khetarpal – 230911266

*Department of I&CT, MIT Manipal*
*April 2025 – Embedded Systems Lab (ICT 2223)*

---

📄 References

Aruna Kommu, Naveen Kumar Uttakar, Raghavendra Rao Kanchi.
Design and development of sensor-based mini projects for embedded system laboratory using ARM Cortex-M3 (LPC1768).

## 📜 License

This project is open-source and licensed under the **MIT License**.
See the [LICENSE](LICENSE) file for details.
