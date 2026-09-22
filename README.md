# 🏧 ATM System (C++)

A console-based ATM System built in C++ using a functional programming approach, simulating basic banking operations with a clean and modular structure.

![C++](https://img.shields.io/badge/C%2B%2B-Functional-blue)
![Platform](https://img.shields.io/badge/Platform-Windows-informational)
![IDE](https://img.shields.io/badge/IDE-Visual%20Studio%202022-purple)

---

## Project Description

This project simulates an ATM using a functional/procedural approach in C++.

Client data lives in `stClientData`: account number, PIN, name, phone number, balance, and a `MarkWantedClient` flag (used to mark a record as active/inactive for a soft delete, instead of physically removing it from the file). At startup, `fnReadFromClientFile` reads a delimited text file line by line, and `fnFillClientRecord` splits each line and fills one struct per client. All of this is collected into `vClientsData`, a `vector<stClientData>` that's always passed by reference so the whole client list never gets copied unnecessarily.

Login is checked in `fnCheckIfClientDataExists`, matching account number and PIN against the vector. On a match, that client's data is copied into `CurrentClient`, a global struct that represents the active session — so every menu operation reads and writes one object instead of searching the vector every time. Wrong credentials just clear the screen, print an invalid message, and loop back to the login prompt.

The main menu isn't loop-based — `prATMMainMenue` and `prGoBackToMainMenue` call each other recursively after each operation, which is a simpler way to keep returning to the menu.

Any operation that changes account state updates `CurrentClient` first, then two functions bring the rest of the system in sync: `prUpdateClientData` walks `vClientsData` by reference and overwrites the matching client, and `prUpdateClientFile` serializes the whole vector back to text and rewrites the file — so the file is never more than one transaction behind memory.

Withdrawals have two paths: Normal Withdraw only allows amounts in multiples of 5 and blocks the transaction if it exceeds the balance, gated behind a check that the account has more than 5 to begin with. Quick Withdraw restricts the user to a fixed set of preset amounts instead of free input, similar to how a real ATM is limited by the cash denominations it holds.

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

## Build and run

### Visual Studio 2022 Community

1. Install Visual Studio Community with the **Desktop development with C++** workload.
2. Clone the repo: `git clone https://github.com/MuhammedEsmer67/ATM-System.git`
3. Open the project:
   - If the repo contains a `.sln` file, double-click it.
   - Otherwise: **File > New > Project > Console App (C++)**, then in Solution Explorer right-click **Source Files > Add > Existing Item** and add `main.cpp`; do the same for `clsDblLinkedList.h` under **Header Files**. Remove the auto-generated `.cpp` file.
4. Press **Ctrl + F5** (Start Without Debugging). A console window shows the output.

### PowerShell (g++)

```
g++ -std=c++17 main.cpp -o ATMSystem
.\ATMSystem
```
