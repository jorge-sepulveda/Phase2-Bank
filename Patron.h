//------------------------------------------------------------------------------
// Patron.h
//------------------------------------------------------------------------------
#ifndef PATRON_H
#define PATRON_H

#include "std_lib_facilities_4.h"
#include "Chrono.h"

class Patron
{
public:
	Patron(){};
	//constructors
	Patron(string n, int an, double b);

	class Invalid{};
	
	//getters
	string getName() const { return name; }
	int getAccountNumber() const { return accountNumber; }
	double getBalance() const { return balance; }
	
	//void methods for adding money
	void depositToPatron(double m);
	void withdrawFromPatron(double m);
	
private:
	string name;
	int accountNumber;
	double balance;
};

// Helper functions
ostream& operator<<(ostream&os, const Patron& p);
istream& operator>>(istream&is, Patron& pp);

//------------------------------------------------------------------------------
// struct Transaction

struct Transaction
{
	Patron patron;
	Chrono::Date date;
	Chrono::Time time;
	string type;
	double amount; 
	
	Transaction(){};
	
	Transaction(Patron p, string t, double d)
	: patron(p), type(t), date(Chrono::Date()), time(Chrono::Time()), amount(d)
	{
	}
};

// Helper Functions
ostream& operator<<(ostream &os, const Transaction& t);
istream& operator>>(istream&is, Transaction& tt);

#endif // PATRON_H