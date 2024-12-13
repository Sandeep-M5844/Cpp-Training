#include <iostream>
#include <string>
#include <vector>
//#include <bits/stdc++.h>

using namespace std;

// Class representing a bank account
class BankAccount {
protected:
    int accountNumber;
    string accountHolder;
    double balance;

public:
    // Constructor
    BankAccount(int accNum, string holder, double initialBalance)
        : accountNumber(accNum), accountHolder(holder), balance(initialBalance) {
        cout << "BankAccount created for " << accountHolder << " with initial balance $" << balance << endl;
    }

    // Deposit money into the account
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited: $" << amount << ". New balance: $" << balance << endl;
        }
        else {
            cout << "Deposit amount must be positive!" << endl;
        }
    }

    // Withdraw money from the account
    void withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient funds. Withdrawal of $" << amount << " failed." << endl;
        }
        else if (amount <= 0) {
            cout << "Withdrawal amount must be positive!" << endl;
        }
        else {
            balance -= amount;
            cout << "Withdrew: $" << amount << ". New balance: $" << balance << endl;
        }
    }

    // Display account information
    void display() const {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder: " << accountHolder << endl;
        cout << "Balance: $" << balance << endl;
    }

    int getAccountNumber() const {
        return accountNumber;
    }

    // Virtual destructor (commented out for now)
    ///*virtual ~BankAccount() {
    //    cout << "BankAccount for " << accountHolder << " is being closed." << endl;
    //}*/
};

// Class representing a bank branch
class BankBranch {
private:
    string branchName;
    string branchAddress;
    vector<BankAccount> accounts;

public:
    // Constructor
    BankBranch(const string& name, const string& address)
        : branchName(name), branchAddress(address) {}

    // Add an account to the branch
    void addAccount(int accountNum, const string& accountName, double balance) {
        BankAccount newAcc(accountNum, accountName, balance);
        accounts.push_back(newAcc);
        cout << "Account created for " << accountName << " with account number: " << accountNum << endl;
    }

    // Find an account by account number
    BankAccount* findAccount(int accountNum) {
        for (auto& account : accounts) {
            if (account.getAccountNumber() == accountNum) {
                return &account;
            }
        }
        cout << "Account number: " << accountNum << " not found." << endl;
        return nullptr;
    }

    // Display all accounts in the branch
    void displayAllAccs() const {
        cout << "All bank accounts in branch " << branchName << ":" << endl;
        for (const auto& account : accounts) {
            account.display();
        }
    }

    string getBranch() const {
        return branchName;
    }
};

// Class representing the bank system
class BankSystem {
private:
    vector<vector<BankAccount>> branches; // A vector of branches, each with a vector of accounts

public:
    // Constructor to initialize a specified number of branches
    BankSystem(int noOfBranches) {
        branches.resize(noOfBranches);
    }

    // Add an account to a specific branch
    void addAccountToBranch(int branchIndex, const BankAccount account) {
        if (branchIndex < branches.size()) {
            branches[branchIndex].push_back(account);
        }
        else {
            cout << "Branch index out of range" << endl;
        }
    }

    // Display all branches and accounts
    void displayAllBranches() const {
        for (int i = 0; i < branches.size(); i++) {
            cout << "Branch " << i + 1 << ":" << endl;
            for (const auto& account : branches[i]) {
                account.display();
            }
        }
    }

    // Deposit money into an account in a specified branch
    void depositToAccount(int branchIndex, int accountNum, double amount) {
        if (branchIndex < branches.size()) {
            for (auto& account : branches[branchIndex]) {
                if (account.getAccountNumber() == accountNum) {
                    account.deposit(amount);
                    cout << "Deposited $" << amount << " to account " << accountNum << " in branch " << branchIndex << endl;
                    return;
                }
            }
            cout << "Account not found in branch " << branchIndex << endl;
        }
        else {
            cout << "Branch index out of range" << endl;
        }
    }

    // Withdraw money from an account in a specified branch
    void withdrawFromAccount(int branchIndex, int accountNum, double amount) {
        if (branchIndex < branches.size()) {
            for (auto& account : branches[branchIndex]) {
                if (account.getAccountNumber() == accountNum) {
                    account.withdraw(amount);
                    return;
                }
            }
            cout << "Account not found in branch " << branchIndex << endl;
        }
        else {
            cout << "Branch index out of range" << endl;
        }
    }
};

int main() {
    BankSystem bank(2); // Bank system with 2 branches

    // Adding accounts to branches
    bank.addAccountToBranch(0, BankAccount(10001, "User1", 10000.00));
    bank.addAccountToBranch(0, BankAccount(2001, "User2", 100.00));
    bank.addAccountToBranch(1, BankAccount(3001, "User21", 500.00));
    bank.addAccountToBranch(1, BankAccount(4001, "User22", 500000.00));
    bank.addAccountToBranch(1, BankAccount(50001, "User23", 40000.00));

    // Display all branches and accounts
    bank.displayAllBranches();

    // Deposit money to accounts
    cout << "Deposit:" << endl;
    bank.depositToAccount(0, 2001, 300.0);
    bank.depositToAccount(1, 50001, 1000.0);

    // Withdraw money from accounts
    bank.withdrawFromAccount(1, 50001, 30000.0);
    bank.withdrawFromAccount(0, 10001, 5000.0);

    return 0;
}
