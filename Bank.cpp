#include "std_lib_facilities_4.h"
#include "Money.h"
#include "Patron.h"
#include "Bank.h"

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
        
        os << patron << " " << patron.getBalance();
        
        if( i < patrons->size()-1 ){ os << " "; }
    }
    
    os << "\n";
    
    // Output transactions
    vector<Transaction>* transactions = b.getTransactions();
                
    for (int i = 0; i < transactions->size(); i++)
    {
        Transaction transaction = transactions->at(i);
        
        os << transaction << " " << transaction.amount ;
        
        if( i < transactions->size()-1 ){ os << " "; }
    }
    
    os << "\n";
    
    return os;
}

// Import the whole Bank from a file
istream& operator>>( istream& is, Bank& b )
{
    // buffers for each line of the file as it is read
    string line;
    istringstream iss;
    
    getline( is, line );  // read a single line from the file
    iss.str( line );        // convert string into istringstream object
    
    // import the default symbol for the bank
    Symbol s;
    int c;
    iss >> c;
    s = static_cast<Symbol>(c);
    b.setDefaultSymbol( s );
    
    // import the money for the Bank
    Money m;
    iss >> m;
    b.setMoney( m );
    
    iss.clear(); // before re-using the istringstream object, clear the flags
    getline( is, line );  // read a single line from the file
    iss.str(line);        // convert into istringstream object
    
    Patron p; // Construct a blank patron object
    while( iss >> p ){ b.addPatron( p ); }
    
    iss.clear(); // before re-using the istringstream object, clear the flags
    getline( is, line );  // read a single line from the file
    iss.str(line);        // convert into istringstream object
    
    Transaction t; // Construct a blank patron object
    while( iss >> t ){ b.addTransaction( t ); }
    
    return is; // always return the istream
}

