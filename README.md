# 🏧 ATM System (C++)

A console-based ATM System built in C++ using a functional programming approach, simulating basic banking operations with a clean and modular structure.

![C++](https://img.shields.io/badge/C%2B%2B-Functional-blue)
![Platform](https://img.shields.io/badge/Platform-Windows-informational)
![IDE](https://img.shields.io/badge/IDE-Visual%20Studio%202022-purple)

---

## About

This project simulates an Automated Teller Machine (ATM) system where users can perform essential banking operations through a console interface.
It was developed to practice C++ programming with a focus on:

* Functional decomposition using multiple functions
* Organizing program flow clearly
* Simulating real-world system behavior

The system provides a simple and interactive way to manage a bank account.

---

## Features

* 🔐 User authentication (PIN system)
* 💰 Check account balance
* 💸 Deposit money
* 🏧 Withdraw money (Quick/Normal)
* 📊 Display updated balance after each transaction
* ✏️ Change Pin Code
* 🔁 Continuous operation until user exits
* ⚡ Simple and user-friendly interface

---

## Tech Stack

* C++ (Procedural / Functional style)
* Standard libraries:

  * iostream
  * string

---

## Project Structure

```
📁 ATMSystem/
├── 📁 Source Files/
    └── ATMSystem.cpp
```

---

## How It Works

1. The user enters their PIN to access the system.

2. The system verifies the PIN from "Clients Records.txt".

3. A menu is displayed with available operations:

   [1] Quik Withdraw.
   [2] Normal Withdraw.
   [3] Deposit.
   [4] Check Balance.
   [5] Change Pin Code.
   [6] Logout.

4. The user selects an operation.

5. The system processes the request and updates the balance.

6. The menu repeats until the user chooses to exit.

---

## Learning Objectives

* Practice function-based programming
* Understand program flow and menu systems
* Work with user input and validation
* Simulate real-world applications
* Improve problem-solving skills

---

## Getting Started

1. Clone the repository
2. Open `ATMSystem.sln` in Visual Studio 2022
3. Build the solution (Ctrl + Shift + B)
4. Run the project (F5)
