#include <iostream>
#include <fstream>
#include <string>
#include <exception>
#include <cstdlib> // For system("cls")

using namespace std;

class Account {
protected:
    int accountNumber;
    double balance;
    int customerID;

public:
    Account(int accNum = 0, double bal = 0.0, int custID = 0) 
        : accountNumber(accNum), balance(bal), customerID(custID) {}

    virtual void deposit(double amount) {
        balance += amount;
    }

    virtual bool withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            return true;
        }
        return false;
    }

    int getAccountNumber() const {
        return accountNumber;
    }

    double getBalance() const {
        return balance;
    }

    virtual void displayAccountInfo() const = 0;
    virtual void saveAccount(ofstream &outFile) const = 0;

    virtual ~Account() {}
};

class SavingsAccount : public Account {
    double interestRate;

public:
    SavingsAccount(int accNum = 0, double bal = 0.0, int custID = 0, double rate = 2.5)
        : Account(accNum, bal, custID), interestRate(rate) {}

    void applyInterest() {
        balance += balance * (interestRate / 100);
    }

    void displayAccountInfo() const override {
        cout << "Savings Account Number: " << accountNumber 
             << "\nBalance: " << balance << "\nInterest Rate: " << interestRate << "%\n";
    }

    void saveAccount(ofstream &outFile) const override {
        outFile << accountNumber << " " << balance << " SavingsAccount\n";
    }
};

class CurrentAccount : public Account {
    double overdraftLimit;

public:
    CurrentAccount(int accNum = 0, double bal = 0.0, int custID = 0, double limit = 1000.0)
        : Account(accNum, bal, custID), overdraftLimit(limit) {}

    bool withdraw(double amount) override {
        if (balance + overdraftLimit >= amount) {
            balance -= amount;
            return true;
        }
        return false;
    }

    void displayAccountInfo() const override {
        cout << "Current Account Number: " << accountNumber 
             << "\nBalance: " << balance << "\nOverdraft Limit: " << overdraftLimit << "\n";
    }

    void saveAccount(ofstream &outFile) const override {
        outFile << accountNumber << " " << balance << " CurrentAccount\n";
    }
};

class Transaction {
public:
    static void deposit(Account &account, double amount) {
        account.deposit(amount);
    }

    static bool withdraw(Account &account, double amount) {
        return account.withdraw(amount);
    }

    static bool transfer(Account &from, Account &to, double amount) {
        if (from.withdraw(amount)) {
            to.deposit(amount);
            return true;
        }
        return false;
    }
};

class Bank {
public:
    Account* createSavingsAccount(int accountNumber, double initialDeposit) {
        Account* account = new SavingsAccount(accountNumber, initialDeposit, 1);
        saveAccountToFile(account);
        return account;
    }

    Account* createCurrentAccount(int accountNumber, double initialDeposit) {
        Account* account = new CurrentAccount(accountNumber, initialDeposit, 1);
        saveAccountToFile(account);
        return account;
    }

    void saveAccountToFile(Account *account) {
        ofstream outFile("accounts.txt", ios::app);
        account->saveAccount(outFile);
        outFile.close();
    }

    bool updateAccountInFile(int accNum, Account *updatedAccount) {
        ifstream inFile("accounts.txt");
        ofstream tempFile("temp.txt");

        if (!inFile || !tempFile) {
            cerr << "File error!\n";
            return false;
        }

        int accNumber;
        double balance;
        string accountType;

        while (inFile >> accNumber >> balance >> accountType) {
            if (accNumber == accNum) {
                updatedAccount->saveAccount(tempFile);
            } else {
                tempFile << accNumber << " " << balance << " " << accountType << "\n";
            }
        }

        inFile.close();
        tempFile.close();
        remove("accounts.txt");
        rename("temp.txt", "accounts.txt");

        return true;
    }

    Account* loadAccountFromFile(int accNum) {
        ifstream inFile("accounts.txt");
        int accNumber;
        double balance;
        string accountType;

        while (inFile >> accNumber >> balance >> accountType) {
            if (accNumber == accNum) {
                if (accountType == "SavingsAccount") {
                    return new SavingsAccount(accNumber, balance, 1);
                } else if (accountType == "CurrentAccount") {
                    return new CurrentAccount(accNumber, balance, 1);
                }
            }
        }
        inFile.close();
        return nullptr;
    }

    void displayAllAccounts() {
        ifstream inFile("accounts.txt");
        int accNumber;
        double balance;
        string accountType;

        while (inFile >> accNumber >> balance >> accountType) {
            cout << "Account Number: " << accNumber << "\n";
            cout << "Balance: " << balance << "\n";
            if (accountType == "SavingsAccount") {
                cout << "Account Type: Savings\n";
            } else if (accountType == "CurrentAccount") {
                cout << "Account Type: Current\n";
            }
            cout << "--------------------------\n";
        }
        inFile.close();
    }
};

int main() {
    Bank bank;
    int choice;
    do {
        system("cls");
        cout << "Banking System Menu:\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit in Account\n";
        cout << "3. Withdrawal from Account\n";
        cout << "4. Transfer Funds\n";
        cout << "5. Show All Accounts\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int accType, accNum;
                double initialDeposit;
                cout << "Enter Account Number: ";
                cin >> accNum;
                cout << "Enter Initial Deposit: ";
                cin >> initialDeposit;
                cout << "Select Account Type:\n";
                cout << "1. Savings Account\n";
                cout << "2. Current Account\n";
                cout << "Enter your choice: ";
                cin >> accType;

                if (accType == 1) {
                    bank.createSavingsAccount(accNum, initialDeposit);
                    cout << "Savings account created successfully!\n";
                } else if (accType == 2) {
                    bank.createCurrentAccount(accNum, initialDeposit);
                    cout << "Current account created successfully!\n";
                } else {
                    cout << "Invalid account type!\n";
                }
                system("pause");
                break;
            }
            case 2: {
                int accNum;
                double amount;
                cout << "Enter Account Number: ";
                cin >> accNum;
                cout << "Enter Deposit Amount: ";
                cin >> amount;

                Account* acc = bank.loadAccountFromFile(accNum);
                if (acc != nullptr) {
                    Transaction::deposit(*acc, amount);
                    bank.updateAccountInFile(accNum, acc);
                    cout << "Amount deposited successfully!\n";
                } else {
                    cerr << "Invalid account number!\n";
                }
                system("pause");
                break;
            }
            case 3: {
                int accNum;
                double amount;
                cout << "Enter Account Number: ";
                cin >> accNum;
                cout << "Enter Withdrawal Amount: ";
                cin >> amount;

                Account* acc = bank.loadAccountFromFile(accNum);
                if (acc != nullptr) {
                    if (Transaction::withdraw(*acc, amount)) {
                        bank.updateAccountInFile(accNum, acc);
                        cout << "Amount withdrawn successfully!\n";
                    } else {
                        cerr << "Insufficient funds!\n";
                    }
                } else {
                    cerr << "Invalid account number!\n";
                }
                system("pause");
                break;
            }
            case 4: {
                int fromAccNum, toAccNum;
                double amount;
                cout << "Enter Source Account Number: ";
                cin >> fromAccNum;
                cout << "Enter Destination Account Number: ";
                cin >> toAccNum;
                cout << "Enter Transfer Amount: ";
                cin >> amount;

                Account* fromAcc = bank.loadAccountFromFile(fromAccNum);
                Account* toAcc = bank.loadAccountFromFile(toAccNum);
                if (fromAcc != nullptr && toAcc != nullptr) {
                    if (Transaction::transfer(*fromAcc, *toAcc, amount)) {
                        bank.updateAccountInFile(fromAccNum, fromAcc);
                        bank.updateAccountInFile(toAccNum, toAcc);
                        cout << "Amount transferred successfully!\n";
                    } else {
                        cerr << "Insufficient funds!\n";
                    }
                } else {
                    cerr << "Invalid account number(s)!\n";
                }
                system("pause");
                break;
            }
            case 5: {
                cout << "List of All Accounts:\n";
                bank.displayAllAccounts();
                system("pause");
                break;
            }
            case 6: {
                cout << "Exiting...\n";
                break;
            }
            default: {
                cout << "Invalid choice! Please try again.\n";
                system("pause");
            }
        }
    } while (choice != 6);

    return 0;
}
