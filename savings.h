#pragma once
#include <string>
#include <iostream>
using namespace std;

class savings
{
private:
    double balance;
    double interest_Rate;
    string goal;
    double goal_amount;
public:
    savings();
    savings(double balance);
    void store_savings(double amount);
    double display_balance();
    //void withdraw_savings(double amount);
    double calculate_interest();
    bool write_toSaving_file();
    void interest_balanceUpdate();
    void saving_goal();
    //saving goal feature
};

