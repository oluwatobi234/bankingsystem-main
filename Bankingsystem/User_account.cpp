#include "User_account.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;




User_account::User_account()
{
    acc_number = 0;
}

void User_account::setPassword(const string& pass_word)
{
    password = pass_word;
}
string User_account::getPassword()
{
    return password;
}
// ask user for all their details  
void User_account:: getRegister() {

    const int minLength = 7;
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');// to clear the white space code taking from geeksforgeeks


    cout << "Enter your name: ";
    getline(cin, this->name);

    string age_str;

    cout << "Enter your age: ";
    getline(cin, age_str);
    age = stoi(age_str);


    cout << "Male or Female: ";
    getline(cin, gender);

    //ask for thier password and make sure they enter valid password
    while (true) {
        cout << "Create a password: maximum 7 character: ";

        getline(cin, password);
        if (password.size() < minLength) {
            cout << "Password must be atleast   " << minLength << "character long. Please try again" << endl;
            continue;
        }
        if (!strongpassword(password)) {
            cout << "Password is weak. Try again!";
            continue;
        }
        cout << "Password is strong, it's acceptable!" << endl;
        break;     
    }
    //generating password
    srand(time(0));
    acc_number = rand() % 1000000 + 1000000;
    cout << "Your account number is: " << acc_number << endl;
}

int User_account::get_AccNumber()
{
    return acc_number;
}

// create a register file and write the user infomation to it
bool User_account:: display_info() {
    ofstream user_record("Register.txt");
    try {
        if (!user_record.is_open()) {
            //throw in an exception if it doesnt open
            throw runtime_error("Unable to open file.");
            return false;
        }
        user_record << "Name: " << name << endl;
        user_record << "Age: " << age << endl;
        user_record << "Gender: " << gender << endl;
        user_record << "Password: " << password << endl;
        user_record << "Account Number: " << acc_number << endl;

        user_record.close();
        return true;
    }
    catch (const runtime_error& e) {
        cerr << e.what() << endl;
        return false;
    }
}
// Validates password strength by checking for uppercase, lowercase, and digits.
bool User_account::strongpassword(const string& password) {
    bool pass_Upper = false;
    bool pass_lower = false;
    bool pass_digit = false;
    try {
        for (char ch : password) {
            if (isupper(ch)) {
                pass_Upper = true;
            }
            if (islower(ch)) {
                pass_lower = true;
            }  
            if (isdigit(ch)) {
                pass_digit = true;
            }
        }
        // Throws an error message if any requirement is missing.
        
        if (!pass_Upper) {
            throw "Password must contain at least one Uppercase letter";

        }
        if (!pass_lower) {
            throw "Password must contain at least one lowercase letter.";


        }
        if (!pass_digit) {
            throw "Password must contain at least one digit.";
        }

    }
    catch (const char* msg) {
        cout << "Error:" << msg << endl;
        return false;
    }
    return true; 
}
// compare the stored password with the input one
bool User_account::compare_password(const string& inputPassword) {
    return  password == inputPassword;
}
// Opens the file and extracts the stored password to compare with user input
bool User_account::readRegister() {
    try {
        string line;
        ifstream user_record("Register.txt");
        if (!user_record.is_open()) {
            throw runtime_error("Unable to open file.");
            return false;
        }
        // Read each line from file and extract password after "Password: "
        bool foundPassword = false;
        while (getline(user_record, line)) {
            if (line.find("Password: ") != string::npos) {
                string extract_password;
                size_t pos = line.find(": ");
                if (pos != string::npos) {
                    extract_password = line.substr(pos + 2);
                }
                // Trim leading and trailing tabs from extracted password stackovew
                extract_password.erase(0, extract_password.find_first_not_of("\t"));
                extract_password.erase(extract_password.find_last_not_of("\t") + 1);
               
                setPassword(extract_password); 
                foundPassword = true;
                break;
            }
        }
        user_record.close();
        return foundPassword;
    }
    catch (const runtime_error& e) {
        cerr << e.what() << endl;
        return false;
    }
}
// This function handles user login by reading from file and verifying password
bool User_account::login() {
   while (true) {
    string inputPassword;
   
    cout << "Enter your password to login: ";
    cin >> ws;
    getline(cin, inputPassword);
        try {
       

            if (readRegister()) {
                if(compare_password(inputPassword)) {
                    cout << "Login successfully! " << endl;
                    return true;
                   
                }
                else {
                    cout << "Incorrect password. Please try again." << endl;
                }
            }
            else {
                cout << "Access denied. User not found." << endl;
                return false;
            }

        }
        catch (const char* msg) {
            cerr << "Error: " << msg << endl;
            return false;
        }
   }
}


