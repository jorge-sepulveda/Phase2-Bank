//------------------------------------------------------------------------------
// Main.cpp
//------------------------------------------------------------------------------

#include "std_lib_facilities_4.h"
#include "Money.h"
#include "Patron.h"
#include "Bank.h"


int main()
{
try{
    // Create the main bank object
    Bank bank;
    
/*
    // Ask to load a previous bank file
    cout << endl << "Please enter a filename to load (or enter for none): ";
    
     Get user input for filename
    string filename("");
    string input_string("");
    std::getline(cin, input_string);
    istringstream ss(input_string);
    filename = ss.str();
    
    if( ss.good() && filename != "" ) // If user entered a filename
    {
        // Load the file
        ifstream input_file(filename, ifstream::in);
	
	    if( !input_file.is_open() ){ //if the file can't be opened
		    error("Error reading file...\n");
	    }
	    else{
	        // Load the file into the main bank object
            input_file >> bank;
	    }
    }
*/
     // Instantiate a NEW Bank to defaults
        
        // asking which currency will be the default
    cout << "Welcome to the bank! \nEnter the default currency to use (1=USD, 2=GBP, 3=EUR, 4=JPY, 5=RUB): ";
    int chosen_int;
    cin >> chosen_int;
    Symbol chosen_sym = static_cast<Symbol>(chosen_int);
        
    if (!cin)
    {
        cout << "Not a valid option, bank will default to USD";
    }
    else
    {
        bank.setDefaultSymbol( chosen_sym );
    }
        
        // Initialize bank money. Bank always stores money in USD.
        Money m( Symbol::USD, 100000.00);
        bank.setMoney( m );
    
    
    // Menu loops until option 'K' is selected to quit the program
    while (true)
    {
        cout << "\nActions bank can do:\n";
        cout << "	A: Add money to the bank\n";
        cout << "	B: Remove money from the bank\n";
        cout << "	C: Display total money in the bank\n";
        cout << "	D: Add a new Patron to the bank\n";
        cout << "	E: Look up a Patron and display information\n";
        cout << "	F: Display all the Patrons in the bank\n";
        cout << "	G: Make a deposit for a Patron\n";
        cout << "	H: Make a withdrawal by a Patron\n";
        cout << "	I: Display all overdrawn Patrons\n";
        cout << "	J: Display list of transactions\n";
        cout << "	K: Quit the program\n";
        cout << "Enter the choice (upper or lower case): ";
        
        char choice;
        cin >> choice;
        choice = toupper(choice);
        if (!cin) error("incorrect input detected\n");
        if (!isupper(choice)) error("Number or special character detected");
        
        // Evaluate the user's menu choice
        switch (choice)
        {
            //--------------------------------------------------------------
            // Adding money to the Bank
            // (Edited to work with the Bank Class)
            // (checked by Dan)
            //--------------------------------------------------------------
            case 'A':
            {
                cout << "Adding money to Bank...\n";
                
                cout << "Which currency are you adding? (1=USD, 2=GBP, 3=EUR, 4=JPY, 5=RUB): ";
                int chosen_int;
                cin >> chosen_int;
                Symbol chosen_sym = static_cast<Symbol>(chosen_int);
                
                //get appropiate Money and add its money afterwards
                cout << "Enter the amount to add to the bank (nonnegative number): ";
                double add_amount;
                cin >> add_amount;

                Money *bm = bank.getMoney();
                
                cout << fixed << setprecision(2);
                
                // [Default Symbol] [Amount in Default Symbol] [Inputting Symbol] [Amount in Inputting Symbol]
                cout << "Old money in Bank: "
                     << SymbolToStr( Bank::getDefaultSymbol() ) << " "  << bm->getAmount( Bank::getDefaultSymbol() ) << " "
                     << "(" << SymbolToStr( chosen_sym ) << " "  << bm->getAmount( chosen_sym ) << ")" << "\n";
                
                add_amount *= xRateFromTo( chosen_sym, Symbol::USD );
                bm->add_money( add_amount );
                
                cout << "New money in Bank: "
                     << SymbolToStr( Bank::getDefaultSymbol() ) << " "  << bm->getAmount( Bank::getDefaultSymbol() ) << " "
                     << "(" << SymbolToStr( chosen_sym ) << " "  << bm->getAmount( chosen_sym ) << ")" << "\n";
                
                break;
            }
            //--------------------------------------------------------------
            // Remove money from the Bank (Edited to work with the Bank Class)
            //--------------------------------------------------------------
            case 'B':
            {
                cout << "Withdrawing money from Bank...\n";
                
                cout << "Which currency are you withdrawling? (1=USD, 2=GBP, 3=EUR, 4=JPY, 5=RUB): ";
                int chosen_int;
                cin >> chosen_int;
                Symbol chosen_sym = static_cast<Symbol>(chosen_int);
                
                //get appropiate Money and add its money afterwards
                cout << "Enter the amount to withdrawl from the bank (nonnegative number): ";
                double withdrawl_amount;
                cin >> withdrawl_amount;

                Money *bm = bank.getMoney();
                
                cout << fixed << setprecision(2);
                
                // [Default Symbol] [Amount in Default Symbol] [Inputting Symbol] [Amount in Inputting Symbol]
                cout << "Old money in Bank: "
                     << SymbolToStr( Bank::getDefaultSymbol() ) << " "  << bm->getAmount( Bank::getDefaultSymbol() ) << " "
                     << "(" << SymbolToStr( chosen_sym ) << " "  << bm->getAmount( chosen_sym ) << ")" << "\n";
                
                withdrawl_amount *= xRateFromTo( chosen_sym, Symbol::USD);
                bm->withdraw_money( withdrawl_amount );
                
                cout << "New money in Bank: "
                     << SymbolToStr( Bank::getDefaultSymbol() ) << " "  << bm->getAmount( Bank::getDefaultSymbol() ) << " "
                     << "(" << SymbolToStr( chosen_sym ) << " "  << bm->getAmount( chosen_sym ) << ")" << "\n";
                
                break;
            }
            //--------------------------------------------------------------
            // Display total money in Bank
            // (Checked by Dan)
            //--------------------------------------------------------------
            case 'C':
            {
                cout << "Display the Bank's total money in which currency? (1=USD, 2=GBP, 3=EUR, 4=JPY, 5=RUB): ";
                int chosen_int;
                cin >> chosen_int;
                Symbol chosen_sym = static_cast<Symbol>(chosen_int);
                
                Money *bm = bank.getMoney();
                
                cout << fixed << setprecision(2);
                
                cout << "Displaying Total Money in bank...\n"
                     << SymbolToStr( chosen_sym ) << " "  << bm->getAmount( chosen_sym ) << "\n";

                break;
            }
            //--------------------------------------------------------------
            // Add a new Patron to bank
            // (checked by Dan)
            // (edited to work with Bank)
            //--------------------------------------------------------------
            case 'D':
            {
                cout << "Creating a patron profile...\n";
                
                string name("");
                int accountNumber;
                double balance;
                
                cout << "Enter your name in the format 'First_Last': ";
                cin >> name;
                
                while(true) // loops until we break
                {
                    cout << "Enter a number between 1 and 9999 for your account number: ";
                    cin >> accountNumber;
                    
                    if ( bank.findPatronByAcctNum( accountNumber ) == nullptr )
                    {
                        // patron with account number not located,
                        // it's ok to use this account number for new acct
                        break; 
                    }else{
                        cout << "Account number already exists, try a different one.\n";
                    }
                }
                
                cout << "Specify the currency type for starting balance (1=USD, 2=GBP, 3=EUR, 4=JPY, 5=RUB): ";
                int chosen_int;
                cin >> chosen_int;
                Symbol chosen_sym = static_cast<Symbol>(chosen_int);
                    
                cout << "Enter the starting balance (has to be > than 0): ";
                cin >> balance;
                balance *= xRateFromTo( chosen_sym, Symbol::USD);
                
                Patron patron(name, accountNumber, balance );
                bank.addPatron(patron);
                
                Money* m = bank.getMoney();
                m->add_money( balance );
                
                break;
            }
            //--------------------------------------------------------------
            // Look up a Patron and display their information
            // (checked by Dan)
            //--------------------------------------------------------------
            case 'E':
            {
                cout << "Accessing patron database...\n";
                cout << "Enter an account number you would like to look up: ";
                
                int acctNum;
                cin >> acctNum; // get user input for Patron account number

                Patron* p = bank.findPatronByAcctNum( acctNum );
                
                if( p != nullptr )
                {
                    cout << *p;
                }else{
                    cout << "An account was not found with that number, "
                         << "exiting lookup...\n";
                }

                break;
            }
            //--------------------------------------------------------------
            // Display all the Patrons in the bank
            // (edited to work with bank class)
            // (checked by Dan)
            //--------------------------------------------------------------
            case 'F':
            {
                //Edited to work with bank class.
                //display all Patrons using a for loop.
                cout << "Displaying all Patrons...\n";
                
                vector<Patron>* patrons = bank.getPatrons();
                
                for (int i = 0; i < patrons->size() ; i++)
                {
                    Patron patron = patrons->at(i);
                    
                    cout << patron << "\n";
                }
                
                break;
            }
            //--------------------------------------------------------------
            // Make a deposit for a Patron
            // (checked by Dan)
            //--------------------------------------------------------------
            case 'G':
            {
                cout << "Making a patron deposit...\n";
                
                cout << "Enter Patron's account number: ";
                int accountNumber;
                cin >> accountNumber;
                
                Patron* patron = bank.findPatronByAcctNum( accountNumber );
                
                if( patron == nullptr )
                {
                    cout << "A patron was not found with that account number, exiting deposit...\n";
                }else{
                    
                    cout << "Make a patron deposit in which currency? (1=USD, 2=GBP, 3=EUR, 4=JPY, 5=RUB): ";
                    int chosen_int;
                    cin >> chosen_int;
                    Symbol chosen_sym = static_cast<Symbol>(chosen_int);
                    
                    cout << "Enter an amount for the deposit (non-negative number): ";
                    double deposit_amount;
                    cin >> deposit_amount;
                    
                    deposit_amount *= xRateFromTo( chosen_sym, Symbol::USD);
                    
                    patron->depositToPatron( deposit_amount );
                    
                    // Also add paton's  deposit to Bank money
                    Money* bm = bank.getMoney();
                    bm->add_money( deposit_amount );
                    
                    bank.addTransaction( Transaction( *patron, "deposit", deposit_amount) );
                }
                
                break;
            }
            //--------------------------------------------------------------
            // Make a withdrawal for a Patron (edited to work with Bank)
            // (checked by Dan)
            //--------------------------------------------------------------
            case 'H': 
            {
                cout << "Making a patron withdrawl...\n";
                
                cout << "Enter patron account number: ";
                int accountNumber;
                cin >> accountNumber;
                
                Patron* patron = bank.findPatronByAcctNum( accountNumber );
                
                if( patron == nullptr )
                {
                    cout << "A patron was not found with that account number, exiting deposit...\n";
                }else{
                
                    cout << "Specify withdrawl currency type (1=USD, 2=GBP, 3=EUR, 4=JPY, 5=RUB): ";
                    int chosen_int;
                    cin >> chosen_int;
                    Symbol chosen_sym = static_cast<Symbol>(chosen_int);
                    
                    cout << "Enter withdrawl amount (non-negative number): ";
                    double withdrawl_amount;
                    cin >> withdrawl_amount;
                    
                    withdrawl_amount *= xRateFromTo( chosen_sym, Symbol::USD);
                    
                    Money* bm = bank.getMoney();
                    
                    if( withdrawl_amount > bm->getAmount() )
                    {
                        cout << "Warning: Bank cannot be overdrawn, cancelling withdrawal.\n";
                    }else{
                        
                        patron->withdrawFromPatron( withdrawl_amount );
                        bm->withdraw_money( withdrawl_amount );
                        
                        if( patron->getBalance() < 0)
                        {
                            cout << "Warning: Patron account is now overdrawn.";
                        }
                        
                        bank.addTransaction( Transaction( *patron, "withdrawal", withdrawl_amount) );
                    }
                }
                
                break;
            }
            //--------------------------------------------------------------
            // Display all overdrawn patrons (balance less than 0)
            // (edited to work with bank class)
            // (checked by Dan)
            //--------------------------------------------------------------
            case 'I':
            {
                cout << "Displaying overdrawn patrons...\n";
                
                bool none_overdrawn = true;
                
                vector<Patron>* patrons = bank.getPatrons();
                
                for (int i = 0; i < patrons->size(); i++)
                {
                    if( patrons->at(i).getBalance() < 0)
                    {
                        Patron patron = patrons->at(i);

                        cout << patron << "\n";
                        
                        none_overdrawn = false;
                    }
                }
                
                if( none_overdrawn )
                {
                    cout << "No patrons are overdrawn\n";
                }
                
                break;
            }
            //--------------------------------------------------------------
            // Display ALL transactions
            // (edited to work with Banks implementation)
            // (Checked by Dan)
            //--------------------------------------------------------------.
            case 'J':
            {
                cout << "Displaying all Transactions...\n";
                
                vector<Transaction>* transactions = bank.getTransactions();
                
                for( int i = 0; i < transactions->size(); i++ )
                {
                    Transaction transaction = transactions->at(i);

                    cout << transaction << "\n";
                }
                
                break;
            }
            //--------------------------------------------------------------
            // Exits the bank! But asks to save file first.
            //--------------------------------------------------------------
            case 'K':
            {
                // Just exits the bank, ask for text file within switch.
                cout << "Exiting Bank...\n";
                
                cout << "Enter the name of the file to save the bank (or just enter to quit): ";
                string filename("");
                cin >> filename;
                
                //if ( !ss.good() ) { throw runtime_error("Invalid filename input."); }
                
                if( filename != "" ) //if user entered a filename
                {
                    ofstream out_file(filename, ios::trunc);

                    if( !out_file.is_open() )
                    {
                        throw runtime_error("Unable to open file for writing.");
                    } else {
                        out_file << bank;

                        out_file.close();
                    }
                }
                
                cout << "\n";
                
                return 0;
                break;
            }
            //--------------------------------------------------------------
            // Default case, warn about a making a wrong menu choice
            //--------------------------------------------------------------
            default:
            {
                cout << "Invalid Option\n";
            }
        } //end switch
    } //end while
} //end try
catch(exception& e)
{
    cerr << "exception: " << e.what() << '\n';
    return 1;
}
catch (...)
{
    cerr << "Some exception\n";
    return 2;
}
} //end main()