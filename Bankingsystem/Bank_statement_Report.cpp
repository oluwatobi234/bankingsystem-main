#include "Bank_statement_Report.h"
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <iomanip>h 


// write the banking statement to the a text file
void Bank_statement_Report::expenses_report(string description, double amount, double balance)
{
	this->description = description;
	this->amount = amount;
	this->balance = balance;
	


	try {
		ofstream report_record("Bank statement.txt", ios ::app);
		if (!report_record.is_open()) {
			throw runtime_error("Unable to open the bank report");
		}
		// capture the exact time the transaction happen
		time_t transcation_date = time(0);
		char current_dateTime[26];
		ctime_s(current_dateTime, sizeof(current_dateTime), &transcation_date);

		// to set the width of the table 
		report_record << left
			<< setw(30) << "Date"
			<< setw(30) << "Description"
			<< setw(10) << "Amount"
			<< setw(10) << "Balance" << endl;

		report_record << left
			<< setw(30) << current_dateTime
			<< setw(30) << description
			<< setw(10) << amount
			<< setw(10) << balance << endl;
	}
	catch (const runtime_error& e) {
		cerr << e.what() << endl;
	}
	

}

// read the file to console if the user choose to

void Bank_statement_Report::Read_expenses_report(){
	try {
		ifstream report_record("Bank statement.txt");
		string line;
		if (!report_record.is_open()) {
			throw runtime_error("Unable to open bank report");
		}
		while (getline(report_record, line)) {
			cout << line << endl;
		}

	}
	catch (const runtime_error& e) {
		cerr << e.what() << endl;
	}

}
