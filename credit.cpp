#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;


bool validateCreditCard(const string& cardNumber) {
    // Credit card validation logic 
    int sum = 0;
    int numDigits = cardNumber.length();
    int parity = numDigits % 2;

    for (int i = 0; i < numDigits; i++) {
        int digit = cardNumber[i] - '0';

        if (i % 2 == parity) {
            digit *= 2;
            if (digit > 9) {
                digit -= 9;
            }
        }

        sum += digit;
    }

    return (sum % 10 == 0);
}

bool login(const string& username, const string& password) {
    ifstream inputFile("users.txt");
    string fileUsername, filePassword;

    if (!inputFile) {
        cerr << "Error opening file." << endl;
        return false;
    }

    while (inputFile >> fileUsername >> filePassword) {
        if (fileUsername == username && filePassword == password) {
            inputFile.close();
            return true;
        }
    }

    inputFile.close();
    return false;
}

void registerUser(const string& username, const string& password) {
    ofstream outputFile("users.txt", ios::app);

    if (!outputFile) {
        cerr << "Error opening file." << endl;
        return;
    }

    outputFile << username << " " << password << endl;
    outputFile.close();
    cout << "User registered successfully!" << endl;
}

int main() {
    int choice;
    string username, password;
    cout << "Choose an option:" << endl;
    cout << "1. Login" << endl;
    cout << "2. Register" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
        cout << "Enter your username: ";
        cin >> username;
        cout << "Enter your password: ";
        cin >> password;

        if (login(username, password)) {
            cout << "Login successful!" << endl;

            string cardNumber;
            cout << "Enter a credit card number: ";
            cin >> cardNumber;

            if (validateCreditCard(cardNumber)) {
                cout << "Credit card number is valid." << endl;
            } else {
                cout << "Credit card number is invalid." << endl;
            }
        } else {
            cout << "Invalid username or password." << endl;
        }
    } else if (choice == 2) {
        cout << "Enter a new username: ";
        cin >> username;
        cout << "Enter a new password: ";
        cin >> password;

        registerUser(username, password);
    } else {
        cout << "Invalid choice." << endl;
    }

    return 0;
}
