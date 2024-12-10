#include <iostream>
#include <unordered_map>
#include <stdexcept>
#include <string>
#include <optional>

class InMemoryDB {
private:
    std::unordered_map<std::string, int> database;       // Main database
    std::unordered_map<std::string, std::optional<int>> transaction; // Temporary changes
    bool transactionActive = false;

public:
    void begin_transaction() {
        if (transactionActive) {
            throw std::runtime_error("Transaction already in progress.");
        }
        transactionActive = true;
        transaction.clear();
    }

    void put(const std::string& key, int value) {
        if (!transactionActive) {
            throw std::runtime_error("No active transaction.");
        }
        transaction[key] = value;
    }

    std::optional<int> get(const std::string& key) {
        if (transactionActive && transaction.find(key) != transaction.end()) {
            return transaction[key];
        }
        if (database.find(key) != database.end()) {
            return database[key];
        }
        return std::nullopt;
    }

    void commit() {
        if (!transactionActive) {
            throw std::runtime_error("No active transaction to commit.");
        }
        for (const auto& [key, value] : transaction) {
            if (value.has_value()) {
                database[key] = value.value();
            } else {
                database.erase(key);
            }
        }
        transactionActive = false;
        transaction.clear();
    }

    void rollback() {
        if (!transactionActive) {
            throw std::runtime_error("No active transaction to rollback.");
        }
        transaction.clear();
        transactionActive = false;
    }
};

int main() {
    InMemoryDB db;

    try {
        // Test 1: Basic commit and rollback
        db.begin_transaction();
        db.put("A", 5);
        std::cout << "Value of A (uncommitted): " << db.get("A").value_or(-1) << "\n";
        db.commit();

        std::cout << "Value of A (committed): " << db.get("A").value_or(-1) << "\n";

        db.begin_transaction();
        db.put("B", 10);
        db.rollback();

        std::cout << "Value of B (after rollback): " << db.get("B").value_or(-1) << "\n";

        // Test 2: Error handling - put() without transaction
        try {
            db.put("C", 20);
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n"; // Expected: "No active transaction."
        }

        // Test 3: Overwriting values
        db.begin_transaction();
        db.put("A", 15); // Overwrite value of A
        db.commit();
        std::cout << "Value of A (after overwrite): " << db.get("A").value_or(-1) << "\n";

        // Test 4: Nested transactions
        try {
            db.begin_transaction();
            db.begin_transaction(); // Attempt nested transaction
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n"; // Expected: "Transaction already in progress."
        }

    } catch (const std::exception& e) {
        std::cerr << "Unexpected Error: " << e.what() << "\n";
    }

    return 0;
}
