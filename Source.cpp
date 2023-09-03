#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Define a structure to represent a bank account
struct BankAccount {
    string accountNumber;
    string accountHolderName;
    string accountType;
    double balance;
};

// Function to generate a unique account number
string generateAccountNumber(const vector<BankAccount>& accounts) {
    return "ACCT" + to_string(accounts.size() + 1);
}

// Function to create a new account and display account details
void createAccount(vector<BankAccount>& accounts) {
    BankAccount newAccount;

    // Collect account details from the user
    cout << "Enter Account Holder Name: ";
    cin.ignore(); // Clear any previous newline characters in the input buffer
    getline(cin, newAccount.accountHolderName);
    cout << "Enter Account Type (e.g., Savings, Checking): ";
    cin >> newAccount.accountType;
    cout << "Enter Initial Deposit: $";
    cin >> newAccount.balance;

    // Generate a unique account number
    newAccount.accountNumber = generateAccountNumber(accounts);

    // Add the new account to the vector of accounts
    accounts.push_back(newAccount);

    cout << "\nAccount created successfully!\n" << endl;

    // Display the account details
    cout << "Account Number: " << newAccount.accountNumber << endl;
    cout << "Account Holder: " << newAccount.accountHolderName << endl;
    cout << "Account Type: " << newAccount.accountType << endl;
    cout << "Account Balance: $" << newAccount.balance << endl;

}

// Function to deposit funds into an account (case-insensitive)
void depositFunds(vector<BankAccount>& accounts) {
    string accountNumber;
    double amount;

    cout << "Enter Account Number: ";
    cin >> accountNumber;

    // Convert the input account number to lowercase (or uppercase)
    transform(accountNumber.begin(), accountNumber.end(), accountNumber.begin(), ::tolower);

    // Search for the account
    for (BankAccount& account : accounts) {
        // Convert the account number in the vector to lowercase (or uppercase) for comparison
        string accountNumLowerCase = account.accountNumber;
        transform(accountNumLowerCase.begin(), accountNumLowerCase.end(), accountNumLowerCase.begin(), ::tolower);

        if (accountNumLowerCase == accountNumber) {
            cout << "Enter Amount to Deposit: $";
            cin >> amount;

            if (amount <= 0) {
                cout << "Invalid deposit amount." << endl;
            }
            else {
                account.balance += amount;
                cout << "Deposit successful. New balance: $" << account.balance << endl;
            }

            return;
        }
    }

    cout << "Account not found." << endl;
}

// Function to withdraw funds from an account (case-insensitive)
void withdrawFunds(vector<BankAccount>& accounts) {
    string accountNumber;
    double amount;

    cout << "Enter Account Number: ";
    cin >> accountNumber;

    // Convert the input account number to lowercase (or uppercase)
    transform(accountNumber.begin(), accountNumber.end(), accountNumber.begin(), ::tolower);

    // Search for the account
    for (BankAccount& account : accounts) {
        // Convert the account number in the vector to lowercase (or uppercase) for comparison
        string accountNumLowerCase = account.accountNumber;
        transform(accountNumLowerCase.begin(), accountNumLowerCase.end(), accountNumLowerCase.begin(), ::tolower);

        if (accountNumLowerCase == accountNumber) {
            cout << "Enter Amount to Withdraw: $";
            cin >> amount;

            if (amount <= 0 || amount > account.balance) {
                cout << "Invalid withdrawal amount or insufficient balance." << endl;
            }
            else {
                account.balance -= amount;
                cout << "Withdrawal successful. New balance: $" << account.balance << endl;
            }

            return;
        }
    }

    cout << "Account not found." << endl;
}

// Function to transfer funds between two accounts (case-insensitive)
void transferFunds(vector<BankAccount>& accounts) {
    string sourceAccountNumber, targetAccountNumber;
    double amount;

    cout << "Enter Source Account Number: ";
    cin >> sourceAccountNumber;

    cout << "Enter Target Account Number: ";
    cin >> targetAccountNumber;

    // Convert the input account numbers to lowercase (or uppercase)
    transform(sourceAccountNumber.begin(), sourceAccountNumber.end(), sourceAccountNumber.begin(), ::tolower);
    transform(targetAccountNumber.begin(), targetAccountNumber.end(), targetAccountNumber.begin(), ::tolower);

    // Find the source and target accounts
    BankAccount* sourceAccount = nullptr;
    BankAccount* targetAccount = nullptr;

    for (BankAccount& account : accounts) {
        // Convert the account number in the vector to lowercase (or uppercase) for comparison
        string accountNumLowerCase = account.accountNumber;
        transform(accountNumLowerCase.begin(), accountNumLowerCase.end(), accountNumLowerCase.begin(), ::tolower);

        if (accountNumLowerCase == sourceAccountNumber) {
            sourceAccount = &account;
        }
        if (accountNumLowerCase == targetAccountNumber) {
            targetAccount = &account;
        }
    }

    if (sourceAccount == nullptr || targetAccount == nullptr) {
        cout << "One or both accounts not found." << endl;
        return;
    }

    cout << "Enter Amount to Transfer: $";
    cin >> amount;

    if (amount <= 0 || amount > sourceAccount->balance) {
        cout << "Invalid transfer amount or insufficient balance." << endl;
    }
    else {
        sourceAccount->balance -= amount;
        targetAccount->balance += amount;
        cout << "Transfer successful." << endl;
        cout << "Source Account Balance: $" << sourceAccount->balance << endl;
        cout << "Target Account Balance: $" << targetAccount->balance << endl;
    }
}


// Function to check the balance of an account (case-insensitive)
void checkBalance(const vector<BankAccount>& accounts) {
    string accountNumber;

    cout << "Enter Account Number: ";
    cin >> accountNumber;

    // Convert the input account number to lowercase (or uppercase)
    transform(accountNumber.begin(), accountNumber.end(), accountNumber.begin(), ::tolower);

    // Search for the account and display its balance
    for (const BankAccount& account : accounts) {
        // Convert the account number in the vector to lowercase (or uppercase) for comparison
        string accountNumLowerCase = account.accountNumber;
        transform(accountNumLowerCase.begin(), accountNumLowerCase.end(), accountNumLowerCase.begin(), ::tolower);

        if (accountNumLowerCase == accountNumber) {
            cout << "Account Holder: " << account.accountHolderName << endl;
            cout << "Account Type: " << account.accountType << endl;
            cout << "Account Balance: $" << account.balance << endl;
            return;
        }
    }

    cout << "Account not found." << endl;
}

int main() {
    vector<BankAccount> accounts; // Vector to store bank accounts

    int choice;

    do {
        // Display the menu
        cout << "===== Banking System Menu =====" << endl;
        cout << "1. Create an Account" << endl;
        cout << "2. Deposit Funds" << endl;
        cout << "3. Withdraw Funds" << endl;
        cout << "4. Transfer Funds" << endl;
        cout << "5. Check Balance" << endl;
        cout << "6. Exit" << endl;
        cout << "===============================" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        // Perform actions based on user's choice
        switch (choice) {
        case 1:
            cout << endl;
            createAccount(accounts);
            cout << endl;
            break;
        case 2:
            cout << endl;
            depositFunds(accounts);
            cout << endl;
            break;
        case 3:
            cout << endl;
            withdrawFunds(accounts);
            cout << endl;
            break;
        case 4:
            cout << endl;
            transferFunds(accounts);
            cout << endl;
            break;
        case 5:
            cout << endl;
            checkBalance(accounts);
            cout << endl;
            break;
        case 6:
            cout << endl;
            cout << "Exiting the system. Goodbye!" << endl;
            cout << endl;
            break;
        default:
            cout << endl;
            cout << "Invalid choice. Please try again." << endl;
            cout << endl;
            break;
        }

    } while (choice != 6);

    return 0;
}
