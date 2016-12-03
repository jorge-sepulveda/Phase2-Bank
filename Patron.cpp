//------------------------------------------------------------------------------
// Patron.cpp
//------------------------------------------------------------------------------

#include "std_lib_facilities_4.h"
#include "Money.h"
#include "Patron.h"
#include "Bank.h"

Patron::Patron(string n, int ac, double b)
: name(n), accountNumber(ac), balance(b)
{
	/*cout << name <<endl ;
	cout << accountNumber << endl;
	cout << balance << endl;*/
	if (b <= 0) error("Cannot have 0 or negative balance");
	else if (ac < 1 || ac > 9999) error("invalid account number, 1 to 4 digits only");
}

void Patron::withdrawFromPatron(double m)
{
	if (m < 0){
		cout << "Cannot withdraw negative money, cancelling withdrawal..." << endl;
	}
	else {
		balance -= m;
	}
}

void Patron::depositToPatron(double m)
{
	if (m < 0){
		cout << "Cannot add negative money, cancelling deposit..." << endl;
	}
	balance += m;
}

istream& operator>>(istream& is, Patron& pp )
{
	string name;
	int account_num;
	double balance;
	
	// Read in space delimited data and populate variables
	is >> name >> account_num >> balance;
	
	// If there were any errors on input, then return without constructing
	if (!is) return is;
	
	// Construct the object using data
	pp = Patron( name, account_num, balance);
	
	return is; // always return the istream
}

istream& operator>>(istream& is, Transaction& tt)
{
	Patron pp;
	string t;
	Chrono::Date date;
	Chrono::Time time;
	double amount;
	
	is >> pp >> t >> date >> time >> amount;
	
	// If there were any errors on input, then return without constructing
	if (!is) return is;
	
	// Construct the object using data
	tt = Transaction(pp,t,amount);
	tt.date = date;
	tt.time = time;
	
	return is; // always return the istream
}

ostream& operator<<(ostream&os, const Patron& p)
{
	return os 	<< fixed << setprecision(2)
				<< p.getName() << " "
				<< p.getAccountNumber(); //<< " "
				//<< p.getBalance() * xRateFromTo( Symbol::USD, Bank::getDefaultSymbol() );
}
				
ostream& operator<<(ostream&os, const Transaction& t)
{
	return os 	<< fixed << setprecision(2)
				<< t.patron << " "
			 	<< t.type << " "
			 	<< t.date << " " 
			  	<< t.time; // << " "
			  	//<< t.amount * xRateFromTo( Symbol::USD, Bank::getDefaultSymbol() );
}