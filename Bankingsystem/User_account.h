#pragma once
#include <string>
using namespace std;
class User_account
{
    private:
        string name;
        int age;
        string gender;
        string password;
        int acc_number;
    public:
       User_account();
       void setPassword(const string& pass_word);
       string getPassword();
       void getRegister();
       int get_AccNumber();
       bool display_info();
       bool strongpassword(const string& password);     
       bool compare_password(const string& inputPassword);
       bool readRegister();
       bool login();
};



