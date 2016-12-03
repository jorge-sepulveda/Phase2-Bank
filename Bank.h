//------------------------------------------------------------------------------
// Bank.h
//------------------------------------------------------------------------------

#ifndef BANK_H
#define BANK_H

#include "std_lib_facilities_4.h"
#include "Money.h"
#include "Patron.h"

class Bank
{
public:
	class Invalid{};
	
	// Money related
	Money* getMoney() { return &money; }
	Money setMoney( Money mm ) { money = mm; }

	// Patron related
	vector<Patron>* getPatrons(){ return &patrons; }
	void addPatron( Patron pp ){ patrons.push_back(pp); }
	Patron* findPatronByAcctNum( int acctNum );
	
	// Transaction related
	vector<Transaction>* getTransactions(){ return &transactions; }
	void addTransaction( Transaction tt ){ transactions.push_back(tt); }
	
	// Symbol related
	Symbol getDefaultSymbol(){ return defaultSymbol; }
	void setDefaultSymbol( Symbol s ){ defaultSymbol = s; }
	
private:

	Symbol defaultSymbol;
	
	Money money;
	vector<Patron> patrons;
	vector<Transaction> transactions;
};

// Helper functions

ostream& operator<<( ostream& os, Bank& b );
istream& operator>>( istream& is, Bank& b );

#endif //BANK_H