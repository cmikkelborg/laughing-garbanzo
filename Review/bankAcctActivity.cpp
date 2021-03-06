// bankAcctActivity.cpp : Defines the entry point for the console application.
// 

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
using namespace std;



class bankAcct
{
public:
	bankAcct(string name, double balance);
	bankAcct(string name);
	bankAcct();
	void makeAcctName(string name) { name; };
	void makeAcctBalance(double balance) { balance = balance; };
	void display();
	void displayName();
	int displayBal();
	void deposit(double amt);
	void withdraw(double amt);
	void transfer(bankAcct& bankAcct, double amt);

private:
	string name;
	double balance;

};

// this function displays the bank  menu and accounts in the vector.
void displayAcct(vector<bankAcct> &bankAcct);

int main()
{
	// VARIABLES //
	string name, newName;
	double balance, deposit, withdraw, transAmt;
	char choice;
	int acctNum, transAcct, remove;
	
	// code to keep the decimal to two places.
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);

	// BANK ACCOUNTS //
	bankAcct wecu("WECU", 1000);
	bankAcct icu("ICU");
	bankAcct northCoast;

	// Vector of bank accounts
	vector <bankAcct> bankList{ bankAcct(wecu), bankAcct(icu) };

	displayAcct(bankList);

	cin >> choice;
	//cout << "(D)eposit   (W)ithdraw   (T)ransfer   (C)lose Account: ";
	while (choice != 'Q' && choice != 'q')
	{
		switch (choice)
		{
		case 'D': case 'd': // DEPOSIT
			if (bankList.empty())
			{
				cout << "\a";
				cout << "No accounts exist to process your request. Please select a different option. ";
				system("pause");
				displayAcct(bankList);
				break;
			}
			else
			{
				cout << "Enter the number of the account you would like to make a deposit: ";
				cin >> acctNum;
				while (cin.fail())
				{
					cin.clear(); // clear input buffer to restore cin to a usable state
					cin.ignore(INT_MAX, '\n'); // ignore last input
					cout << "You can only enter numbers. " << endl;
					cout << "Enter the number of the account you would like to make a deposit: ";
					cin >> acctNum;
				}
				if (bankList.empty())
				{
					cout << "\a";
					cout << "No accounts exist to process your request. Please select a different option. ";
					system("pause");
					displayAcct(bankList);
					break;
				}
				if (acctNum - 1 > bankList.size() || acctNum - 1 < 0)
				{
					cout << "\a";
					cout << "Error: Please enter a valid account number. ";
					system("pause");
					displayAcct(bankList);
					break;
				}
				else
				{
					cout << "How much would you like to deposit into ";
					bankList[acctNum - 1].displayName();
					cout << "?" << endl;
					cin >> deposit;
					while (cin.fail())
					{
						cin.clear();
						cin.ignore(INT_MAX, '\n');
						cout << "You can only enter numbers. " << endl;
						cout << "How much would you like to deposit into ";
						bankList[acctNum - 1].displayName();
						cin >> deposit;
					}
					if (deposit < 0.01)
					{
						cout << "\a";
						cout << "Error: Please enter a valid dollar amount. ";
						system("pause");
						displayAcct(bankList);
						break;
					}
					bankList[acctNum - 1].deposit(deposit);
					displayAcct(bankList);
					break;
				}
			}
		case 'W': case 'w': // WITHDRAW
			if (bankList.empty())
			{
				cout << "\a";
				cout << "No accounts exist to process your request. Please select a different option. ";
				system("pause");
				displayAcct(bankList);
				break;
			}
			else
			{
				cout << "Enter the number of the account you would like to make a withdraw: ";
				cin >> acctNum;
				while (cin.fail())
				{
					cin.clear();
					cin.ignore(INT_MAX, '\n');
					cout << "You can only enter numbers. " << endl;
					cout << "Enter the number of the account you would like to make a withdraw: ";
					cin >> acctNum;
				}
				if (acctNum - 1 > bankList.size() || acctNum - 1 < 0)
				{
					cout << "\a";
					cout << "Error: Please enter a valid account number. ";
					system("pause");
					displayAcct(bankList);
					break;
				}
				else
				{
					cout << "How much would you like to withdraw from ";
					bankList[acctNum - 1].displayName();
					cout << "?" << endl;
					cin >> withdraw;
					while (cin.fail())
					{
						cin.clear();
						cin.ignore(INT_MAX, '\n');
						cout << "You can only enter numbers. " << endl;
						cout << "How much would you like to withdraw from ";
						bankList[acctNum - 1].displayName();
						cout << "? ";
						cin >> withdraw;
					}
					if (withdraw < 0.01)
					{
						cout << "\a";
						cout << "Error: Please enter a valid dollar amount. ";
						system("pause");
						displayAcct(bankList);
						break;
					}
					if (withdraw > bankList[acctNum - 1].displayBal())
					{
						cout << "\a";
						cout << "Error: Unable to complete transaction.\n" << "Insufficient funds. ";
						system("pause");
						displayAcct(bankList);
						break;
					}
					else
					{
						bankList[acctNum - 1].withdraw(withdraw);
						displayAcct(bankList);
						break;
					}
				}
			}
		case 'T': case 't': // TRANSFER
			if (bankList.empty())
			{
				cout << "\a";
				cout << "No accounts exist to process your request. Please select a different option. ";
				system("pause");
				displayAcct(bankList);
				break;
			}
			else
			{
				cout << "Enter the number of the source account of the transfer: ";
				cin >> acctNum;
				while (cin.fail())
				{
					cin.clear();
					cin.ignore(INT_MAX, '\n');
					cout << "You can only enter numbers. " << endl;
					cout << "Enter the number of the source account of the transfer: ";
					cin >> acctNum;
				}
				if (acctNum - 1 > bankList.size() || acctNum - 1 < 0)
				{
					cout << "\a";
					cout << "Error: Please enter a valid account number. ";
					system("pause");
					displayAcct(bankList);
					break;
				}
				else
				{
					cout << "Enter the number of the destination account of the transfer: ";
					cin >> transAcct;
					while (cin.fail())
					{
						cin.clear();
						cin.ignore(INT_MAX, '\n');
						cout << "You can only enter numbers. " << endl;
						cout << "Enter the number of the destination account of the transfer: ";
						cin >> transAcct;
					}
					if (transAcct - 1 > bankList.size() || transAcct - 1 < 0)
					{
						cout << "\a";
						cout << "Error: Please enter a valid account number. ";
						system("pause");
						displayAcct(bankList);
						break;
					}
					else
					{
						cout << "Enter the dollar amount you wish to transfer from ";
						bankList[acctNum - 1].displayName();
						cout << " to ";
						bankList[transAcct - 1].displayName();
						cout << ":" << endl;
						cin >> transAmt;
						while (cin.fail())
						{
							cin.clear();
							cin.ignore(INT_MAX, '\n');
							cout << "You can only enter numbers. " << endl;
							cout << "Enter the dollar amount you wish to transfer from ";
							bankList[acctNum - 1].displayName();
							cout << " to ";
							bankList[transAcct - 1].displayName();
							cout << ": ";
							cin >> transAmt;
						}
						if (transAmt < 0.01)
						{
							cout << "\a";
							cout << "Error: Please enter a valid dollar amount. ";
							system("pause");
							displayAcct(bankList);
							break;
						}
						if (transAmt > bankList[acctNum - 1].displayBal())
						{
							cout << "\a";
							cout << "Error: Unable to complete transaction.\n Insufficient funds. ";
							system("pause");
							displayAcct(bankList);
							break;
						}
						else
						{
							bankList[acctNum - 1].transfer(bankList[transAcct - 1], transAmt);
							displayAcct(bankList);
							break;
						}
					}
				}
			}
		case 'A': case 'a': // ADD ACCOUNTS
			cout << "Enter the name of institution of the new account: " << endl;
			cin.ignore(1000, '\n');
			getline(cin, newName);
			bankList.push_back(newName);
			displayAcct(bankList);
			break;

		case 'C': case 'c': // CLOSE ACCOUNTS
			if (bankList.empty())
			{
				cout << "\a";
				cout << "No accounts exist to process your request. Please select a different option. ";
				system("pause");
				displayAcct(bankList);
				break;
			}
			if (bankList.size() >= 1)
			{
				cout << "Please enter the number of the account you would like to close: ";
				cin >> remove;
				while (cin.fail())
				{
					cin.clear();
					cin.ignore(INT_MAX, '\n');
					cout << "You can only enter numbers. " << endl;
					cout << "Please enter the number of the account you would like to close: ";
					cin >> remove;
				}
				if (remove > bankList.size() || remove < 0)
				{
					cout << "\a";
					cout << "Error: Account does not exist.\n" << "You must enter a valid account number. ";
					system("pause");
					displayAcct(bankList);
					break;
				}
				else
				{
					bankList.erase(bankList.begin() + remove - 1);
					displayAcct(bankList);
				}
			}
			else
			{
				cout << "\a";
				cout << "Error: No accounts exist to close." << endl;
				system("pause");
				displayAcct(bankList);
				break;
			}

		case 'Q': case 'q': // QUIT
			break;
		}
		cin >> choice;
	}
	
	//system("pause");
    return 0;
	
}

bankAcct::bankAcct(string n, double bal)
{
	name = n;
	balance = bal;
}

bankAcct::bankAcct(string n)
{
	name = n;
	balance = 0;
}

bankAcct::bankAcct()
{
	name = "---";
	balance = 0;
}

void bankAcct::display()
{
	cout << "Name: " << name << "\tBalance: " << balance << endl;
}

void bankAcct::displayName()
{
	cout << name;
}

int bankAcct::displayBal()
{
	return balance;
}

void bankAcct::deposit(double amt)
{
	balance += amt;
	cout << endl << "Depositing " << amt << " into " << name << "." << endl << endl;

	system("pause");
}

void bankAcct::withdraw(double amt)
{
	balance -= amt;
	cout << endl << "Withdrawing " << amt << " from " << name << "." << endl << endl;

	system("pause");
}

void bankAcct::transfer(bankAcct & bankAcct, double amt)
{
	balance -= amt;
	cout << endl << "Transfering " << amt << " from " << name << " to " << bankAcct.name << "." << endl << endl;
	cout << "Withdrawing " << amt << " from " << name;
	bankAcct.deposit(amt);
}

void displayAcct(vector<bankAcct> &bankAcct)
{
	system("cls");
	cout << " \t\tAccounts" << endl << "-----------------------------------------" << endl;
	for (int i = 0; i < bankAcct.size(); i++)
	{
		cout << i + 1 << "\t";
		bankAcct[i].display();
	}

	cout << endl << endl;
	cout << "What would you like to do? " << endl;
	cout << "(D)eposit   (W)ithdraw   (T)ransfer   (C)lose Account    (A)dd Account   (Q)uit: ";
	cout << endl;
}