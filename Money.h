//------------------------------------------------------------------------------
// Money.h
//------------------------------------------------------------------------------

#ifndef MONEY_H
#define MONEY_H

#include "std_lib_facilities_4.h"

//------------------------------------------------------------------------------

// Both mean the same thing
enum Symbol { USD=1, GBP, EUR, JPY, RUB };

//------------------------------------------------------------------------------

// Returns the given currency's exchange rate in dollars
double xRate( Symbol s );

double xRateFromTo( Symbol from, Symbol to );

string SymbolToStr( Symbol s );

Symbol StrToSymbol( string s );

//------------------------------------------------------------------------------

class Money
{
private:
	double amount;
	Symbol symbol;

public:
	class Invalid{};
	
	Money(){};
	Money( Symbol s, double a );

	//getters
	Symbol getSymbol() const { return symbol; }
	
	double getAmount( Symbol s = Symbol::USD ) const { return amount * xRateFromTo( this->symbol, s ); }
	
	//setters and modifying functions
	void add_money(double m);
	void withdraw_money(double m);
	
};

// Helper functions
ostream& operator<<(ostream&os, const Money& m);
istream& operator>>(istream&is, Money& mm);

//------------------------------------------------------------------------------

#endif // MONEY_H