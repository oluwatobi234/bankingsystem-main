#include "savings.h"
#include <iostream>
#include <string>
#include <cmath>
#include <fstream>

using namespace std;
savings::savings() {
    balance = 0.0;
}
savings::savings(double new_balance){
    balance = new_balance;
}
//this function deposit the money from the saving allocation in current account and update the balance
void savings::store_savings(double amount) {
    if (amount > 0) {
        balance += amount;
    }
}
double savings::display_balance()
{
    cout << "Your balance is: " << balance << endl;  
    return balance;
}
// handle the logic from the withdrawing function in savings class


double savings::calculate_interest()
{
    double new_amount, interest_Rate;
    double principal = balance;
    double time = 1;
    int compound = 12;
    interest_Rate = 5.1;
    interest_Rate = interest_Rate / 100;
    new_amount = principal * pow((1 + (interest_Rate / compound)), (compound * time ));
    cout << "Your new balance is: " << new_amount << endl;
    balance= new_amount;
    return balance;
}

bool savings::write_toSaving_file()
{
    ofstream saving_record("savings.txt");
    try {
        if (!saving_record.is_open()) {
            throw runtime_error("Error opening file");
            return false;
        }
        else {
            saving_record << balance << endl;
            saving_record.close();
        }
        
    }
    catch (const runtime_error& e) {
        cerr << e.what() << endl;
    }  
}
//write the time the last interest update happened on the saving deposit
void savings::interest_balanceUpdate()
{
    try {
        ofstream balance_record("savings.txt", ios::app);
        if (!balance_record.is_open()) {
            throw runtime_error("Unable to open file for writing.");
        }
        //code line 86 to 88 was taking from stack overflow
        time_t current_time = time(0);
        char dt[26];
        ctime_s(dt, sizeof(dt), &current_time);
        balance_record << "Latest balance for your interest is: " << balance << " at: " << dt << endl;
        cout << "Current date and time: " << dt << endl;
        balance_record.close();
        cout << "Daily balance update recorded successfully." << endl;
    }
    catch (const runtime_error& e) {
        cerr << e.what() << endl;
    }
}
// this function deals with saving goals
void savings::saving_goal()
{
    double target_goal;
    cout << "what are you saving for: ";
    cin >> goal;

    cout << "what is your targeted amount:$ ";
    cin >> target_goal;

    cout << "how much do you want to save now:";
    cin >> goal_amount;
    balance += goal_amount;

    cout << "You are saving for " << goal << " with a target of " << target_goal << endl;
    cout << "Your current progress is: $" << balance << endl;

    double remaining = target_goal - balance;
    double saving_progress = 0;
    if (target_goal > 0) {
        saving_progress = (balance / target_goal) * 100;
    }
    else {
        cout << "Invalid goal amount. Please enter a positive value." << endl;
    }
    cout << "You have saved " << saving_progress << "% of your target" << endl;
    cout << "You have " << remaining << " left to save" << endl;

    interest_balanceUpdate();
}



