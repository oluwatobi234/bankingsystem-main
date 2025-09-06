#include "current_account.h"
#include "savings.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <map>
#include <ctime>

using namespace std;

current_account::current_account(User_account& user) : student (user) {
	categories = { "Food" , "rent" , "transport","entertainment", "Shopping", "Healthcare", "Education", "Travel", "Miscellaneous"};
	amount = {};
	// creating new instance of the classes 
	savingsAccount = new savings(0.0);
	Bank_report = new Bank_statement_Report();
	
}
// a destructor to clean up the resources in other to avoid memory leaks
current_account::~current_account() {
	delete savingsAccount;
	delete Bank_report;
}

User_account& current_account::get_student()
{
	return student;
}


// Displays existing categories and lets the user choose to view or add more.
// Then continues to call the budgeting function or throws an error for invalid input.
void current_account::display_categories() {
	try {
		int category_option;
		cout << "pick num 1 to view your categories or 2 add to your categories: ";
		cin >> category_option;
		cout << "current categories: \n";
		
		switch (category_option)
		{
		case 1:
			for (const auto& element : categories) {
				cout << element << endl;
			}
			set_amount("");
			break;
		case 2:
			add_categories();
			set_amount("");
			break;
		default:
			throw invalid_argument(" Error Not a valid input:");
			cout << "Wrong options!" << endl;
			break;
		}
	}
	catch (const invalid_argument& e) {
		cerr << e.what() << endl;
	}

}
// This method displays the current categories and allows the user to add new ones.
// The updated list is shown after each addition.
void current_account::add_categories() {

	string newcategories;
	int option;
	for (const auto& element : categories) {
		cout << element << endl;
	}
	cout << "enter new categories: ";   
	cin >> newcategories;

	categories.push_back(newcategories);
	cout << "updated categories list:";
	for (const auto& element : categories) {
		cout << element << endl;
	}
	// It continues to prompt the user to add more categories until they choose to stop.
	while (true) {
		cout << "Want to add more categories? 1 for yes and 2 for no: "; 
		cin >> option;
		if (option == 1) {
			cout << "enter new category: ";
			cin >> newcategories;
			categories.push_back(newcategories);
		}
		else if (option == 2) {
			break;
		}
		else {
			"enter a valid option:";
		}
		cout << "Updated categories list: \n";
		for (const auto& element : categories) {
			cout << element << endl;
		}
	}
	cout << "Final categories list: \n";
	for (const auto& element : categories) {
		cout << element << endl;
	}
}

//Distributes income between savings, current, and budget categories.
void current_account::set_amount(string category) {
	double income = collectIncome();
	double savingAllocation = saving_allocation();
	double currentAccount_money = income -= savingAllocation;
	
	new_remaining = budget(currentAccount_money);
	
	
}
//this deposit the users money
double current_account::collectIncome()
{
	double income;
	cout << "Enter your income: $";
	cin >> income;
	return income;
}
// handle when user choose to move money to saving account 
double current_account::saving_allocation()
{
	double savingAllocation = 0.00;
	string choosenTo_save;
	cout << "Do you want to move to saving account? Y or N: ";
	cin >> choosenTo_save;

	//Handle savings allocation by storing and transferring it to the saving class
	if (choosenTo_save == "Y" || choosenTo_save == "y") {
		cout << "How much £ do you want to allocate to your savings account: $";
		cin >> savingAllocation;

		char goal_choice;
		cout << "Do you want to set a goal for your savings account? Y or N: ";
		cin >> goal_choice;

		if (goal_choice == 'Y' || goal_choice == 'y') {
			savingsAccount->saving_goal();
		}

		// call the savings class method to deposit the saving allocated to it
		savingsAccount->store_savings(savingAllocation);
		calculate_interestForSavings();
	}
	else if (choosenTo_save == "N" || choosenTo_save == "n") {
		cout << "All income are in your current account";  
	}

	return savingAllocation;
}
double current_account::budget(double incomeRemaining)
{
	for (const auto& element : categories) {
		double category_amount;
		cout << "Remaining income: $" << incomeRemaining << endl; 
		if (incomeRemaining <= 20 && incomeRemaining > 0.00) {
			cout << "Low balance!You are running out of money" << endl;
		}
		else if (incomeRemaining == 0.00) {
			cout << "You have no more money to allocate" << endl;
			break;
		}
		cout << "Enter amount for each category: " << element << ":$"; 
		
		cin >> category_amount;
		// check input and make sure it does not exceed remaining income
		if (incomeRemaining != 0.00) {
			while (category_amount > incomeRemaining) {
				cout << "Error: Amount exceeds remaining income." << endl;
				cout << "Please re-enter amount for " << element << " :";
				cin >> category_amount;
			}
			//Store amount for each category and update remaining income
			amount[element] = category_amount;
			incomeRemaining -= category_amount;

			bank_statement(element, category_amount, incomeRemaining);
		}
	}
	return incomeRemaining;
}
	// the function check how much money is allocate for each category
// got this code from stack overflow  
double current_account::getAmount(string category) const {
	auto it = amount.find(category);
	return (it != amount.end()) ? it->second :-1.0;
}

//this allow the user to withdraw 
bool current_account::withdrawMoney()
{
	if (new_remaining <= 0.00) {
		cout << "You need to deposit money to your account" << endl;
		return false;
	}
	double amount;
	cout << "Enter the amount you want to withdraw: ";
	cin >> amount;
	if (amount > new_remaining) {
		cout << "Insufficient funds" << endl;
		return false;
	}
	else {
		new_remaining -= amount;
		cout << "Successful! You withdrawn: " << amount << "\n" << "Your new balance is :" << new_remaining << endl;
		return true;
	}
}
// write the final budget to it own record file
bool current_account:: write_to_file() {
	ofstream budget_record ("budgeting_record.txt"); 
	cout << "Writing expense to file..." << endl;
	try {
		if (!budget_record.is_open()) {
			throw runtime_error("Unable to open file for writing.");
			return false;
		}
		for (const auto& element : amount) {
			budget_record << element.first << ":£" << element.second << endl;
		}
		budget_record.close();
		cout << "Expense written to file successfully." << endl;
	}
	catch (const runtime_error& e) {
		cerr << e.what() << endl;
	}
}

// handle the method of the savings account displaying the saving balance
double current_account::display_Savingbalance()
{
	return savingsAccount->display_balance();
	
}

// handle the logic from the withdrawing function in savings class using composite object relationship

double current_account::calculate_interestForSavings()
{
	return savingsAccount ->calculate_interest();  
}

bool current_account::store_savingsBalance()
{
	if (savingsAccount->write_toSaving_file())
	{
		return true;
	}
	return false;
}

void current_account::write_savings_update()
{
	savingsAccount->interest_balanceUpdate();
}

void current_account::bank_statement(const string& category, double amount, double balance) {
	Bank_report->expenses_report(category, amount, balance);
}
void current_account::view_bank_statement() {
	Bank_report->Read_expenses_report();
}





