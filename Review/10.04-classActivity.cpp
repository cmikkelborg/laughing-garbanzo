// 10.04-classActivity.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

class BankAcct
{
	/* Anything directly accessible by the program goes under "public".*/
public:
	/* Overloaded Constructors to initialize BankAcct objects. */
	BankAcct(string name, double balance);
	BankAcct(string name);
	BankAcct();
	/* Member function to display an account. */
	void display();
	/* Member function to add to the account. */
	void deposit(double amt);
	void withdraw(double amt);
	void transfer(BankAcct& BankAcct, double amt);

	/* Member variables should be private for classes.  All access by member functions only. */
	/* This makes the class behave more like other class such as int or string, */
	/*	changing the internal storage or rules of the class should not necessitate program changes. */
private:
	string name;
	double balance;

};


int main()
{
	string givenName;
	/* Some code to make doubles have two decimal points */
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);

	/* Create some accounts using overloaded constructors. */
	BankAcct wecu("WECU", 1000);
	BankAcct icu("ICU");
	/* Default constructor.  A constructor with no arguments does use (). */
	/* (BankAcct NorthCoast() looks to C++ like a function declaration that returns BankAcct.) */
	BankAcct NorthCoast;

	/* Use the display "accessor" member function. */
	wecu.display();
	icu.display();
	NorthCoast.display();

	/* Use the deposit "mutator" member function. */
	wecu.deposit(100);
	cout << "After deposit 100 to wecu, " << endl;

	wecu.display();
	system("pause");

	wecu.transfer(icu, 200);

	wecu.display();
	icu.display();

	system("pause");
	icu.withdraw(50);
	icu.display();

	system("pause");
	return 0;
}

/* Overloaded Constructor definitions for varying initial value calls. */
BankAcct::BankAcct(string n, double bal)
{
	name = n;
	balance = bal;
}
BankAcct::BankAcct(string n)
{
	name = n;
	balance = 0;
}
BankAcct::BankAcct()
{
	name = "---";
	balance = 0;
}
void BankAcct::display()
{
	cout << "Name: " << name << "\tBalance: " << balance << endl;
}
void BankAcct::deposit(double amt)
{
	balance += amt;
}

void BankAcct::withdraw(double amt)
{
	balance -= amt;
	cout << endl << "Withdrawing " << amt << " from " << name << " account." << endl << endl;
}

void BankAcct::transfer(BankAcct & BankAcct, double amt)
{
	balance -= amt;
	BankAcct.deposit(amt);
	cout << endl << "Transfering " << amt << " from " << name << " to " << BankAcct.name << "." << endl << endl;

}