#include "std_lib_facilities_4.h"
#include "Graph.h"     // next 3 are for graphics library
#include "GUI.h"
#include "Window.h"

using namespace Graph_lib;


//-----------------------------------------------------------
// define a struct that is a window in which a DLL Curve can
// be entered via a GUI

struct Bank_window : Graph_lib::Window {       // inherits from Window

  // constructor
  Bank_window(Point xy,             // top lefthand corner
         int w,                // width
         int h,                // height
         const string& title); // label

private:
  // data members

  // widgets:
  Button next_button;                // button indicating next DLL point is ready
  Button quit_button;                // end program
  Menu bank_menu;                   // menu of color choices for the DLL
  Button menu_button;                // button to display the color menu

  //out boxes for top bar of displaying all the monies.
  Out_box usd_out;
  Out_box gbp_out;
  Out_box eur_out;
  Out_box jpy_out;
  Out_box rub_out;
  Out_box all_out;

  //inboxes for input.
  Out_box input_1;
  In_box input_2;
  In_box input_3;
  In_box input_4;
  In_box input_5;
  In_box input_6;

  //output boxes for feedback
  Out_box output_1;
  Out_box output_2;
  Out_box output_3;
  Out_box output_4;
  Out_box output_5;
  Out_box output_6;
  
  Multiline_out_box bigBox;
  // function members

  void change(Color c) {             // change the color of the DLL
    //dll.set_color(c);
  }

  // actions invoked by callbacks:
  void next();   // defined below

  void quit();   // defined below
  
  //----------------------------------------------------------------------------
  // Callback Functions (Actions)
  //----------------------------------------------------------------------------
  
  void addMoney_pressed(){
    cout << "add Money!" << endl;
    output_1.put("add/ cur, amt");
  }
  void remMoney_pressed(){
    cout << "remove Money" << endl;
    output_1.put("rem/ cur, amt");
  }
  void showMoney_pressed(){
    cout << "show me the money" << endl;
  }
  void addPatron_pressed(){
    cout << "add a patron" << endl;
    output_1.put("addP/ name, act, cur, amt");
  }
  void isPatron_pressed(){
    cout << "lookup a patron" << endl;
    output_1.put("lookupP/ actnum");
  }
  void patrons_pressed(){
    cout << "patrons pressed" << endl;
    output_1.put("Patrons");
  }
  void deposit_pressed(){
    cout << "deposit to Patron pressed" <<endl;
    output_1.put("depP/ act, cur, amt");
  }
  void withdraw_pressed(){
    cout << "withdraw from Patron pressed" << endl;
    output_1.put("wtdP/ act, cur, amt");
  }
  void overdrawn_pressed(){
    cout << "overdrawn pressed" << endl;
    output_1.put("deadbeats");
  }
  void transactions_pressed(){
    cout << "transactions pressed" << endl;
    output_1.put("transactions");
  }
  void transfer_pressed(){
    cout << "transfer pressed" << endl;
    output_1.put("transfer/ bnk,cur,amt");
  }

  // callback functions; declared here and defined below.

  static void cb_red(Address, Address);
  static void cb_blue(Address, Address);
  static void cb_black(Address, Address);
  static void cb_next(Address, Address);
  static void cb_quit(Address, Address);
  
  //adding callback voids for menu
  static void cb_addMoney(Address, Address);
  static void cb_remMoney(Address, Address);
  static void cb_showMoney(Address, Address);
  static void cb_addPatron(Address, Address);
  static void cb_isPatron(Address ,Address);
  static void cb_Patrons(Address ,Address);
  static void cb_deposit(Address, Address);
  static void cb_withdraw(Address, Address);
  static void cb_overdrawn(Address, Address);
  static void cb_Transactions(Address, Address);
  static void cb_transfer(Address, Address);
};

// ----------------------------------------------------------
// now define the parts of Bank_window that were only declared
// inside the class

// constructor:

Bank_window::Bank_window(Point xy, int w, int h, const string& title) : 

  // initialization - start by calling constructor of base class 
  Window(xy,w,h,title),    

  // initialize "Next curve" button
  next_button(
        Point(x_max()-150,0),   // location of button
        70, 20,                 // dimensions of button
        "Next",                 // label of button
        cb_next),               // callback function for button
  // initialize quit button
  quit_button(
        Point(x_max()-70,0),    // location of button
        70, 20,                 // dimensions of button 
        "Quit",                 // label of button
        cb_quit),               // callback function for button
  //displaying USD outbox
  usd_out(
        Point(40,0),
        80,20,
        "USD:"),
  //displaying GBP outbox
  gbp_out(
        Point(160,0),
        80,20,
        "GBP:"),
  //displaying EUR outbox
  eur_out(
        Point(280,0),
        80,20,
        "EUR:"),
  //displaying JPY outbox
  jpy_out(
        Point(400,0),
        80,20,
        "JPY:"),
  //displaying RUB outbox
  rub_out(
        Point(520,0),
        80,20,
        "RUB:"),
  //displaying ALL outbox
  all_out(
        Point(640,0),
        80,20,
        "ALL:"),
  //input 1 is a display box which will identify which function to bank is in
  input_1(
        Point(40,30),
        200,20,
        "I1:"),
  //input 2 initialization
  input_2(
        Point(280,30),
        200,20,
        "I2:"),
  //input 3 initialization
  input_3(
        Point(520,30),
        200,20,
        "I3:"),
  //input 4 initialization
  input_4(
        Point(40,60),
        200,20,
        "I4:"),
  //input 5 initialization
  input_5(
        Point(280,60),
        200,20,
        "I5:"),
  //input 6 initialization
  input_6(
        Point(520,60),
        200,20,
        "I6:"),
  //outbox 1
  output_1(
        Point(40,90),
        200,20,
        "O1:"),
  //outbox 2 initialization
  output_2(
        Point(280,90),
        200,20,
        "O2:"),
  //outbox 3 initialization
  output_3(
        Point(520,90),
        200,20,
        "O3:"),
  //outbox 4 initialization
  output_4(
        Point(40,120),
        200,20,
        "O4:"),
  //outbox 5 initialization
  output_5(
        Point(280,120),
        200,20,
        "O5:"),
  //outbox 6 initialization
  output_6(
        Point(520,120),
        200,20,
        "O6:"),
  //big text box initializations.
  bigBox(
        Point(40,150),
        680,350,
        "L:"),
  // initialize the bank menu
  bank_menu(                        
       Point(x_max()-150,30),   // location of menu
       150, 20,                 // dimensions of menu
       Menu::vertical,         // list menu items vertically
       "bank menu"),               // label of menu 
  // initialize the menu button
  menu_button(
        Point(x_max()-150,30),  // location of menu button
        150, 20,                // dimensions of button 
        "menu",                // label of button
        cb_menu)               // callback for button

  // body of constructor follows
{
  // attach buttons and boxes to window
  attach(usd_out);
  attach(gbp_out);
  attach(eur_out);
  attach(jpy_out);
  attach(rub_out);
  attach(all_out);
  //attaching input boxes
  attach(input_1);
  attach(input_2);
  attach(input_3);
  attach(input_4);
  attach(input_5);
  attach(input_6);
  //attaching output boxes
  attach(output_1);
  attach(output_2);
  attach(output_3);
  attach(output_4);
  attach(output_5);
  attach(output_6);
  
  attach(bigBox);
  attach(next_button);
  attach(quit_button);

  // First make 3 buttons for color menu, one for each color, and 
  // attach them to the menu: the attach function of the Menu struct
  // adjusts the size and location of the buttons; note callback functions).
  // Then attach menu to window but hide it (initially, the menu button
  // is displayed, not the actual menu of color choices).

  bank_menu.attach(new Button(Point(0,0),0,0,"Add Money",cb_addMoney)); 
  bank_menu.attach(new Button(Point(0,0),0,0,"Remove Money",cb_remMoney));
  bank_menu.attach(new Button(Point(0,0),0,0,"Add Patron",cb_showMoney));
  bank_menu.attach(new Button(Point(0,0),0,0,"Patron Lookup",cb_isPatron));
  bank_menu.attach(new Button(Point(0,0),0,0,"Patron List",cb_Patrons));
  bank_menu.attach(new Button(Point(0,0),0,0,"Deposit",cb_deposit));
  bank_menu.attach(new Button(Point(0,0),0,0,"Withdraw",cb_withdraw));
  bank_menu.attach(new Button(Point(0,0),0,0,"Overdrawn",cb_overdrawn));
  bank_menu.attach(new Button(Point(0,0),0,0,"Transactions",cb_Transactions));
  bank_menu.attach(new Button(Point(0,0),0,0,"Transfer",cb_transfer));
  attach(bank_menu);
  //bank_menu.hide(); 

  // attach menu button
  attach(menu_button);

  // attach shape that holds the DLL to be displayed
}

// ---------------------------- 
// callback function for quit button - boilerplate: 
// When the button is pressed, the system invokes the
// specified callback function.  First argument is address of the
// button (which we won't use, so we don't bother to name it).  Second
// argument, named pw, is address of the window containing the pressed
// button, i.e., address of our Bank_window object.  reference_to
// converts the address pw into a reference to a Bank_window object,
// so we can call the quit() function.  Objective is to call function
// quit() which does the real work specific to this button.

void Bank_window::cb_quit(Address, Address pw) {
  reference_to<Bank_window>(pw).quit();   // quit is defined next
}

//------------------------------------
// what to do when quit button is pressed

void Bank_window::quit() {
  hide();                   // FLTK idiom for delete window
}

// ----------------------------
// callback function for next button - boilerplate:

void Bank_window::cb_next(Address, Address pw) {
  reference_to<Bank_window>(pw).next();  // next is defined next
}

// -------------------------------
// what to do when "next curve" button is pressed

void Bank_window::next() {
  // get input data from the inboxes - x and y coordinates
  // of next curve

  // update current position & scalar readouts - make strings with the
  // coordinate & scalar info and use the out boxes
  stringstream ssx;
  //ssx << '(' << xx << ',' << yx << ')';
  //xyx_out.put(ssx.str());

  redraw();  // function inherited from Window to redraw the window
}

// ---------------------------------------------------
//callback for when add Money(from the menu) is pressed - boilerplate
void Bank_window::cb_addMoney(Address, Address pw)
{
    reference_to<Bank_window>(pw).addMoney_pressed();
}
//-------------------------------------------------------------------
//callback for when remove Money(from the menu) is pressed - boilerplate
void Bank_window::cb_remMoney(Address, Address pw)
{
    reference_to<Bank_window>(pw).remMoney_pressed();
}
//-------------------------------------------------------------------
//callback for when show Money(from the menu) is pressed - boilerplate
void Bank_window::cb_showMoney(Address, Address pw)
{
    reference_to<Bank_window>(pw).showMoney_pressed();
}
//-------------------------------------------------------------------
//callback for when add Patron(from the menu) is pressed - boilerplate
void Bank_window::cb_addPatron(Address, Address pw)
{
    reference_to<Bank_window>(pw).addPatron_pressed();
}

//-------------------------------------------------------------------
//callback for when is Patron(from the menu) is pressed - boilerplate
void Bank_window::cb_isPatron(Address, Address pw)
{
    reference_to<Bank_window>(pw).isPatron_pressed();
}
//-------------------------------------------------------------------
//callback for when Patrons(from the menu) is pressed - boilerplate
void Bank_window::cb_Patrons(Address, Address pw)
{
    reference_to<Bank_window>(pw).patrons_pressed();
}
//-------------------------------------------------------------------
//callback for when deposit(from the menu) is pressed - boilerplate
void Bank_window::cb_deposit(Address, Address pw)
{
    reference_to<Bank_window>(pw).deposit_pressed();
}
//-------------------------------------------------------------------
//callback for when withdraw(from the menu) is pressed - boilerplate
void Bank_window::cb_withdraw(Address, Address pw)
{
    reference_to<Bank_window>(pw).withdraw_pressed();
}
//-------------------------------------------------------------------
//callback for when overdrawn(from the menu) is pressed - boilerplate
void Bank_window::cb_overdrawn(Address, Address pw)
{
    reference_to<Bank_window>(pw).overdrawn_pressed();
}
//-------------------------------------------------------------------
//callback for when Transactions(from the menu) is pressed - boilerplate
void Bank_window::cb_Transactions(Address, Address pw)
{
    reference_to<Bank_window>(pw).transactions_pressed();
}
//-------------------------------------------------------------------
//callback for when Transfer(from the menu) is pressed - boilerplate
void Bank_window::cb_transfer(Address, Address pw)
{
    reference_to<Bank_window>(pw).transfer_pressed();
}
//-------------------------------------------------------------------
// main - just creates window and invokes gui_main

int main() 
  try {
    // construct the GUI window
    Bank_window win(Point(100,100),900,500,"Bank phase 2 window");
    return gui_main();  // inherited from Window; calls FLTK's run
  }
  catch(exception& e) {
    cerr << "exception: " << e.what() << '\n';
    return 1;
  }
  catch(...) {
    cerr << "some exception\n";
    return 2;
  }