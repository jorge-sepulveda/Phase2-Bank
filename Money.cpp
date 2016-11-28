//------------------------------------------------------------------------------
// Money.cpp
//------------------------------------------------------------------------------

#include "std_lib_facilities_4.h"
#include "Money.h"
#include "Patron.h"
#include "Bank.h"

Money::Money(Symbol s, double a) : symbol(s), amount(a)
{
	if (a < 0) throw "Negative amount of money";
}

void Money::add_money(double m)
{
	if (m < 0){
		cout << "Cannot add negative money, cancelling deposit..." << endl;
	}
	else{
		amount += m;
	}
}

void Money::withdraw_money(double m)
{
	if (m < 0) {
		cout << "Negative amount, cancelling withdrawal... " << endl;
	}
	else if (m >= amount){
		cout << "Not enough money to do this.cancelling withdrawal..." << endl;
	}
	else{
		amount -= m;
	}
}

double xRate( Symbol t )
{
	switch( t ){
		case Symbol::USD : return 1.0; break;
		case Symbol::GBP : return 0.76; break;
		case Symbol::EUR : return 0.89; break;
		case Symbol::JPY : return 102.09; break;
		case Symbol::RUB : return 65.97; break;
	}
}

double xRateFromTo( Symbol from, Symbol to )
{
	double rate_f = 1.0 / xRate(from);
	double rate_t = xRate(to);


	double rate = rate_f * rate_t;
	return rate;
}

string SymbolToStr( Symbol s )
{
	switch( s ){
		case Symbol::USD : return "USD"; break;
		case Symbol::GBP : return "GBP"; break;
		case Symbol::EUR : return "EUR"; break;
		case Symbol::JPY : return "JPY"; break;
		case Symbol::RUB : return "RUB"; break;
	}
}

istream& operator>>(istream& is, Money& mm)
{
	int c;
	Symbol s;
	double a;
	is >> c >> a;
	s = static_cast<Symbol>(c);
	if (!is) return is;
	mm = Money(s,a);
	return is;
}

ostream& operator<<(ostream& os, const Money& m)
{
	return os  << fixed << setprecision(2)
			   << m.getSymbol() << " "
			   << m.getAmount();
}