#include <iostream>
#include "User_account.h"
#include "current_account.h"
#include "savings.h"



void menu(current_account& studentAccount) {
    using namespace std;
    int choice;
    bool loggedIn = false;
    bool registerd = false;

    do {
        if (!loggedIn) {
            cout << "1. Register" << endl;
            cout << "2. Login" << endl;
            cout << "3. Exit" << endl;
            cout << "Enter your choice: ";
            //code taking from geeksforgeeks
            if (!(cin >> choice)) {
                cin.clear(); // clear error
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); //  // skips the invalid input
                cout << "Invalid input. Please enter a number.\n";
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clears any leftover input


            switch (choice) {
            case 1:
                studentAccount.get_student().getRegister();
                studentAccount.get_student().display_info();
                registerd = true;
                cout << "Registration successful! Please login." << endl;
                continue;
                
            case 2:
                if (!registerd) {
                    cout << "Please register first." << endl;
                    continue;
                }
                else {
                   studentAccount.get_student().login();
                   loggedIn = true;
                   break;  
                }

                continue;
            case 3:
            cout << "Exiting..." << endl;
            return;
              
            default:
                cout << "Invalid choice" << endl;
                break;
            }
        }
        else {
            cout << "\n=== Account Menu ===" << endl;
            cout << "1. Manage account(View and add categories/ Deposit/Allocate savings/ Budget)" << endl;
            cout << "2. Withdraw money" << endl;
            cout << "3. View Account Information " << endl;
            cout << "4. Logout" << endl;
            cout << "5. Exit" << endl;
            cout << "Enter your choice: ";
            if (!(cin >> choice)) {
                cin.clear(); // clear error
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard input
                cout << "Invalid input. Please enter a number.\n";
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');


            switch (choice)
            {
            case 1:
                studentAccount.display_categories();
                studentAccount.write_to_file();
                studentAccount.store_savingsBalance();
                continue;
                
            case 2:
                studentAccount.withdrawMoney();
                continue;

            case 3:
                int view_choice;
                cout << "Press 1 to view your account balance or 2 for bank statement report: ";
                cin >> view_choice;
                if (view_choice == 1)
                {
                    studentAccount.get_student().display_info();
                    studentAccount.display_Savingbalance();
                }
                else if (view_choice == 2) {
                    studentAccount.view_bank_statement();
                }
                else {
                    cout << "Invalid choice!" << endl;
                }
                
                continue;

            case 4:
                loggedIn = false;
                cout << "Logged out successfully! Thank you for using our banking system." << endl;
                break;
            case 5:
                cout << "Exiting..." << endl;
                return;
            default:
                cout << "Invalid choice" << endl;
                break;
            }
        }
        
    }while(true);
}
int main() {
    cout << "welcome to your bank" << endl;

    User_account student1;  
    
    current_account studentAccount(student1);

    menu(studentAccount);
    
    return 0;
}

