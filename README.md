# In-Memory Database With Transaction Support

## Overview
This project implements an in-memory key-value database with transaction support in C++. It allows users to:
- Start a transaction (`begin_transaction()`).
- Add or update key-value pairs (`put(key, value)`).
- Retrieve values (`get(key)`).
- Commit changes (`commit()`).
- Roll back uncommitted changes (`rollback()`).

The implementation includes error handling for invalid operations and ensures data consistency during transactions.

---

## Setup Instructions
### Requirements
- A C++ compiler (e.g., GCC, Clang) or an IDE like CLion.
- Git (to clone the repository).

### Steps to Run the Code
1. Clone the repository:
   ```bash
   git clone https://github.com/Tony-coder95/In-Memory-Database-With-Transaction-Support.git
2. Navigate to the project directory:
   ```bash
   cd In-Memory-Database-With-Transaction-Support
3. Compile the code:
   ```bash
   g++ main.cpp -o InMemoryDB
4. Run the executable:
   ```bash
   ./InMemoryDB

### A brief (3-5 sentences) write-up within the README of how this assignment should be modified in order to become an “official” assignment in the future
In my opinion to make this assignment an "official" assignment, the instructions should define expected behaviors for edge cases, such as retrieving a key during a transaction or rolling back non-existent changes.
Additionally, an automated grading script could be provided to validate functionality and handle edge cases consistently, to add fairness in assessment.
The assignment could also be enhanced by including advanced features, such as nested or concurrent transaction support and database persistence, to better simulate real-world scenarios. 
Finally, I believe the grading rubric should focus on code clarity, proper documentation, and comprehensive test cases, to promote professional software development practices.
