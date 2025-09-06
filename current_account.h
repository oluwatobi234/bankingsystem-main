#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "User_account.h"
#include "savings.h"
#include "Bank_statement_Report.h"
#include <unordered_map>
#include <map>


using namespace std;

class current_account
{
private:
	User_account& student;
	double new_remaining;
	vector< string > categories;
	map<string, double> amount;
	savings* savingsAccount;
	Bank_statement_Report* Bank_report;
public:
	current_account(User_account& user);
	~current_account();
	User_account& get_student();
	void display_categories();
	void add_categories();
	void set_amount(string category);
	double collectIncome();
	double saving_allocation();
	double budget(double incomeRemaining);
	double getAmount(string category) const; 
	bool withdrawMoney();
	bool write_to_file();
	double display_Savingbalance(); 
	double calculate_interestForSavings();
	bool store_savingsBalance();
	void write_savings_update();
	void bank_statement(const string& category, double amount, double balance);
	void view_bank_statement();

}; 

