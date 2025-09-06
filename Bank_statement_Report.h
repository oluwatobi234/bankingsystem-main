#pragma once
#include <iostream>
#include <string>
using namespace std;


class Bank_statement_Report
{
public:
	string description;
	double amount;
	double balance;
	void expenses_report(string description, double amount, double balance);
	void Read_expenses_report();

};

