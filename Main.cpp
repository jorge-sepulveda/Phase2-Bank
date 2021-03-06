//------------------------------------------------------------------------------
// Main.cpp
//------------------------------------------------------------------------------

#include "std_lib_facilities_4.h"
#include "Money.h"
#include "Patron.h"
#include "Bank.h"
#include "BankGui.h"

void Bank_window::runMenu( char option )
{
    // Evaluate the user's menu choice
    
    switch (option)
    {
        //--------------------------------------------------------------
        // Adding money to the Bank
        // (Edited to work with the Bank Class)
        // (checked by Dan)
        //--------------------------------------------------------------
        case 'A':
        {
            bbox.put("addMoney!");
            input_1.put("add/ cur, amt");
            int chosen_int;
            string inbox1 =  input_2.get_string();
            Symbol chosen_sym = StrToSymbol( inbox1 );
            
            //get appropiate Money and add its money afterwards

            double add_amount = stod( input_3.get_string() );

            Money *bm = bank.getMoney();
            
            add_amount *= xRateFromTo( chosen_sym, Symbol::USD );
            bm->add_money( add_amount );
            
            
            stringstream ss;
            ss << fixed << setprecision(2)<< bm->getAmount();
            
            usd_out.put(ss.str());
        
            break;
        }
        //--------------------------------------------------------------
        // Remove money from the Bank (Edited to work with the Bank Class)
        //--------------------------------------------------------------
        case 'B':
        {
            //cout << "Withdrawing money from Bank...\n";
            bbox.put("remove money");
            input_1.put("rem/ cur, amt");
            
            string inbox1 = input_2.get_string();
            Symbol chosen_sym = StrToSymbol( inbox1 );
            

            double remove_amount = stod( input_3.get_string() );
    
            Money *bm = bank.getMoney();

            
            remove_amount *= xRateFromTo( chosen_sym, Symbol::USD);
            bm->withdraw_money( remove_amount );
            
            stringstream ss;
            ss << fixed << setprecision(2)<< bm->getAmount();
            
            usd_out.put(ss.str());

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
            //cout << "Creating a patron profile...\n";
            
            input_1.put("addP/ name, act, cur, amt");
            
            string name("");
            int accountNumber;
            double balance;
            
            string inboxcur =  input_4.get_string();
            Symbol chosen_sym = StrToSymbol( inboxcur );
            
            name = input_2.get_string();
            accountNumber = input_3.get_int();
            balance = stod( input_5.get_string() );
            
            
                
            if ( bank.findPatronByAcctNum( accountNumber ) == nullptr )
            {
                //number is ok for usage
                balance *= xRateFromTo( chosen_sym, Symbol::USD);
            
                Patron patron(name, accountNumber, balance );
                bank.addPatron(patron);
                        
                stringstream ss;
                ss << patron << " " << patron.getBalance()*xRateFromTo(Symbol::USD, bank.getDefaultSymbol()) << "\n";;
                bbox.put(ss.str());
                
                ss.str(string());
                
                Money* m = bank.getMoney();
                m->add_money( balance );
                        
                ss << fixed << setprecision(2)<< m->getAmount();
                usd_out.put(ss.str());
            }else{
                output_1.put("Account already exists");
                output_2.put("try a different one");
            }
            
            
            
            break;
        }
        //--------------------------------------------------------------
        // Look up a Patron and display their information
        // (checked by Dan)
        //--------------------------------------------------------------
        case 'E':
        {
            //cout << "Accessing patron database...\n";
            //cout << "Enter an account number you would like to look up: ";
            
            int acctNum;
            acctNum = input_2.get_int();
            //cin >> acctNum; // get user input for Patron account number
    
            Patron* p = bank.findPatronByAcctNum( acctNum );
            
            stringstream ss;
            
            if( p != nullptr )
            {
                ss << *p << " " << p->getBalance() << "\n";
                bbox.put(ss.str());
            }else{
                output_1.put("account not found");
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
            //cout << "Displaying all Patrons...\n";
            
            vector<Patron>* patrons = bank.getPatrons();
            
            stringstream ss;
            
            for (int i = 0; i < patrons->size() ; i++)
            {
                Patron patron = patrons->at(i);
                
                ss << patron << " " << patron.getBalance()*xRateFromTo(Symbol::USD, bank.getDefaultSymbol())<< "\n";
            }
            bbox.put(ss.str());
            
            break;
        }
        //--------------------------------------------------------------
        // Make a deposit for a Patron
        // (checked by Dan)
        //--------------------------------------------------------------
        case 'G':
        {
            //cout << "Making a patron deposit...\n";
            input_1.put("depP/ act, cur, amt");
            int accountNumber;
            accountNumber = input_2.get_int();
            
            Patron* patron = bank.findPatronByAcctNum( accountNumber );
            
            if( patron == nullptr )
            {
                bbox.put("patron not found");
            }else{
                
                string inboxcur =  input_3.get_string();
                Symbol chosen_sym = StrToSymbol( inboxcur );
                
                double amount = stod ( input_4.get_string() );
                
                amount *= xRateFromTo( chosen_sym, Symbol::USD);
                
                patron->depositToPatron( amount );
                
                // Also add paton's  deposit to Bank money
                Money* bm = bank.getMoney();
                bm->add_money( amount );
                
                stringstream ss;
                ss << fixed << setprecision(2)<< bm->getAmount();
                usd_out.put(ss.str());
                
                ss.str(string());
                
                bank.addTransaction( Transaction( *patron, "deposit", amount) );
                ss << *patron << " " << patron->getBalance()*xRateFromTo(Symbol::USD, bank.getDefaultSymbol()) << "\n";
                bbox.put(ss.str());
            }
            
            break;
        }
        //--------------------------------------------------------------
        // Make a withdrawal for a Patron (edited to work with Bank)
        // (checked by Dan)
        //--------------------------------------------------------------
        case 'H': 
        {
            input_1.put("wtdP/ act, cur, amt");
            //cout << "Making a patron withdrawl...\n";
            
            //cout << "Enter patron account number: ";
            int accountNumber;
            accountNumber = input_2.get_int();
            //cin >> accountNumber;
            
            Patron* patron = bank.findPatronByAcctNum( accountNumber );
            
            if( patron == nullptr )
            {
                output_1.put("patron not found");
            }else{
                
                string inboxcur =  input_3.get_string();
                Symbol chosen_sym = StrToSymbol( inboxcur );
            
                
                double amount = stod( input_4.get_string() );
                
                amount *= xRateFromTo( chosen_sym, Symbol::USD);
                
                Money* bm = bank.getMoney();
                
                if( amount > bm->getAmount() )
                {
                    output_1.put("Bank cannot be overdrawn");
                    output_2.put("cancelling withdrawal");
                }else{
                    
                    patron->withdrawFromPatron( amount );
                    bm->withdraw_money( amount );
                    
                    if( patron->getBalance() < 0)
                    {
                        output_3.put("patron overdrawn");
                    }
                    
                    stringstream ss;
                    ss << fixed << setprecision(2)<< bm->getAmount();
                    usd_out.put(ss.str());
                    bbox.put("withdrawal successful");
                    
                    ss.str(string());
                    
                    bank.addTransaction( Transaction( *patron, "withdrawal", amount*xRateFromTo(Symbol::USD, bank.getDefaultSymbol())) );
                    ss << *patron << " " << patron->getBalance()*xRateFromTo(Symbol::USD, bank.getDefaultSymbol()) << "\n";
                    bbox.put(ss.str());
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
            input_1.put("deadbeats");
            
            bool none_overdrawn = true;
            
            vector<Patron>* patrons = bank.getPatrons();
            
            stringstream ss;
            
            for (int i = 0; i < patrons->size(); i++)
            {
                if( patrons->at(i).getBalance() < 0)
                {
                    Patron patron = patrons->at(i);
                    
                    ss << patron << " " << patron.getBalance()*xRateFromTo(Symbol::USD, bank.getDefaultSymbol()) << "\n";
                    
                    none_overdrawn = false;
                }
            }
            
            if( none_overdrawn )
            {
                output_1.put("none overdrawn");
            }
            else if ( !none_overdrawn )
            {
                bbox.put(ss.str());
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
            input_1.put("transactions");
            
            vector<Transaction>* transactions = bank.getTransactions();
            
            stringstream ss;
            
            for( int i = 0; i < transactions->size(); i++ )
            {
                Transaction transaction = transactions->at(i);
                
                Patron patron = transaction.patron;
    
                ss  << patron << " " << patron.getBalance()*xRateFromTo(Symbol::USD, bank.getDefaultSymbol())
                    << " "
                    << transaction << " "
                    << transaction.amount*xRateFromTo(Symbol::USD, bank.getDefaultSymbol()) << "\n";
            }
            bbox.put(ss.str());
            
            break;
        }
        //--------------------------------------------------------------
        // Exits the bank! But asks to save file first.
        //--------------------------------------------------------------
        case 'K':
        {
            // Just exits the bank, ask for text file within switch.
            cout << "Exiting Bank...\n";
            
            string defaultSymbol = SymbolToStr( bank.getDefaultSymbol() );
            
            
            
            cout << "Enter the name of the file to save the "<< defaultSymbol << " bank (or just enter to quit): ";
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
            
            break;
        }
        //--------------------------------------------------------------
        // Transfers money betweeen banks
        //--------------------------------------------------------------
        case 'L':
        {
            
        }
        //--------------------------------------------------------------
        // Default case, warn about a making a wrong menu choice
        //--------------------------------------------------------------
        default:
        {
            cout << "Invalid Option\n";
        }
    } //end switch
} //end runMenu

int main()
{
try{
    Bank_window win_usd(Point(100,100),900,500,"USD");
    Bank_window win_gbp(Point(125,125),900,500,"GBP");
    Bank_window win_eur(Point(150,150),900,500,"EUR");
    Bank_window win_jpy(Point(175,175),900,500,"JPY");
    Bank_window win_rub(Point(200,200),900,500,"RUB");

    vector<Bank_window*> windows; // save a pointer to each bank window

    windows.push_back( &win_usd );
    windows.push_back( &win_gbp );
    windows.push_back( &win_eur );
    windows.push_back( &win_jpy );
    windows.push_back( &win_rub );

    for( int i = 1; i<=5; i++ ) // cycle through the five banks
    {
        Bank bank;

        //convert i to USD, GBP, etc.
        string defaultSymbol = SymbolToStr( static_cast<Symbol>(i) );

        // Ask to load a previous bank file
        cout << endl << "Please enter a filename to load the " << defaultSymbol << " bank (or enter for none): ";

        //Get user input for filename
        string filename("");
        string input_string("");
        std::getline(cin, input_string);
        istringstream ss(input_string);
        filename = ss.str();

        bool good_read = false;

        if( ss.good() && filename != "" ) // If user entered a filename
        {
            // Load the file
            ifstream input_file(filename, ifstream::in);
    	
    	    if( !input_file.is_open() ){ //if the file can't be opened
    		    error("Error reading file...\n");
    	    }
    	    else{
    	        // Load the file into the main bank object
                if( input_file >> bank )
                {
                    //flag as good file read
                    good_read = true;
                }
    	    }
        }

        if( good_read == false ) // Instantiate a NEW Bank to defaults
        {
            // Initialize bank money. Bank always stores money in USD.
            bank.setDefaultSymbol( static_cast<Symbol>(i) );
            Money m( Symbol::USD, 100000.00*xRateFromTo( static_cast<Symbol>(i), Symbol::USD ));
            bank.setMoney( m );
        }

        windows[i-1]->bank = bank;
        Money* m = bank.getMoney();
        double amount = m->getAmount();
        
        windows[i-1]->usd_out.put(to_string( amount*xRateFromTo( Symbol::USD, Symbol::USD )));
        windows[i-1]->gbp_out.put(to_string( amount*xRateFromTo( Symbol::USD, Symbol::GBP )));
        windows[i-1]->eur_out.put(to_string( amount*xRateFromTo( Symbol::USD, Symbol::EUR )));
        windows[i-1]->jpy_out.put(to_string( amount*xRateFromTo( Symbol::USD, Symbol::JPY )));
        windows[i-1]->rub_out.put(to_string( amount*xRateFromTo( Symbol::USD, Symbol::RUB )));
        
        windows[i-1]->all_out.put(to_string( amount*xRateFromTo( Symbol::USD, static_cast<Symbol>(i) )));
    } //end for
    
    return gui_main();  // inherited from Window; calls FLTK's run
    
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