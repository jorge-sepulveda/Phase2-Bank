#include "std_lib_facilities_4.h"
#include "Money.h"
#include "Patron.h"
#include "Bank.h"

// Initialize static member variables
Symbol Bank::defaultSymbol = Symbol::USD;

// Return a Patron object with given account number
Patron* Bank::findPatronByAcctNum( int acctNum )
{
	for( int i = 0; i < patrons.size(); i++ )
	{
		if( acctNum == patrons.at(i).getAccountNumber() )
		{
		    // Patron was found
			return &patrons.at(i);
		}
	}
	
	// If it gets this far, no patron was found.
	return nullptr;
}


// Output the whole Bank to a file
ostream& operator<<( ostream&os, Bank& b )
{
    // Output bank and its money properties
    os  << b.getDefaultSymbol() << " "
        << *(b.getMoney());
    
    os << "\n";
    
    // Output patrons
    vector<Patron>* patrons = b.getPatrons();
    
    
    for (int i = 0; i < patrons->size(); i++)
    {
        Patron patron = patrons->at(i);
        
        os << patron;
        
        if( i < patrons->size()-1 ){ os << " "; }
    }
    
    os << "\n";
    
    // Output transactions
    vector<Transaction>* transactions = b.getTransactions();
                
    for (int i = 0; i < transactions->size(); i++)
    {
        Transaction transaction = transactions->at(i);
        
        os << transaction;
        
        if( i < transactions->size()-1 ){ os << " "; }
    }
    
    os << "\n";
    
    return os;
}

// Import the whole Bank from a file
/*istream& operator>>( istream& is, Bank& b )
{
    Symbol s;
    int c;
    is >> c;
    s = static_cast<Symbol>(c);
    b.setDefaultSymbol( s );
    
    Money m;
    is >> m;
    b.setMoney( m );
    
    is.clear();
    

    string line("");
    getline( is, line );
    istringstream ss(line);
        
    Patron p;
    while( ss >> p )
    {
        //b.addPatron(p);
        cout << p;
    }
    
    /*
    
    if (is.peek() == '\n') { cout << "here1"; }
    
    is.ignore('\n');
    
    Patron p;
    while ( ( is.peek() != '\n' ) && ( is >> p ) )
    {
        b.addPatron(p);
    }
    
    string line3("");
    getline( is, line3 );
    
    //is.ignore('\n');
    
    Transaction t;
    while ( ( is.peek() != '\n' ) && ( is >> t ))
    {
        b.addTransaction(t);
    }
    
}*/
