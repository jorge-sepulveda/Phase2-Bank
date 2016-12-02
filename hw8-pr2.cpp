// HW8-PR2: Write a new program (hw8-pr2) meeting at least the following minimum requirements:
// 1. Use the FLTK Graphics Interface Library (Graph.h&cpp GUI.h&cpp Simple_window.h&cpp 
//    Window.h&cpp contained in PPP.tar.gz from Piazza), create a graphics display window
//    to display a DLL object using the DLL struct derived from the Shape base class that
//    was also used in hw8-pr1), with the following GUI widgets (Buttons, In/Out-Boxes, etc):
//      - In-Box’s to specify X and Y coordinates for new points in the Window for the DLL
//      - Out-Box to show the last X,Y coordinates for a new point for the DLL
//      - In-Box’s to specify X and Y coordinates for an existing point to remove from the DLL
//      - Out-Box to show the last X,Y coordinates for removing a point from the DLL
//      - Next Button to redraw the DLL with any new/removed point(s)
//      - Menu Button and Color Menu (red, blue, black) to change the DLL color
//      - Quit Button to exit Window and program
//    RESTRICTION!! must have at least two points to "remove" a point
// 2. When you run your hw8-pr2 program add the same 9 new points as used in hw8-pr1 and then
//    change the DLL color to red to create the same DLL display as in hw8-pr1.  Then remove
//    the point at X=250, Y=300 to produce the new DLL display for hw8-pr2.
// 3. Use the following command on build.tamu.edu to compile your program:
// g++ hw8-pr2.cpp Graph.cpp GUI.cpp Simple_window.cpp Window.cpp -lfltk -lfltk_images -o hw8-pr2

#include "std_lib_facilities_4.h"
#include "Graph.h"     // next 3 are for graphics library
#include "GUI.h"
#include "Window.h"

using namespace Graph_lib;


struct DLL : Shape { // Doubly Linked List
  void add(Point p) { Shape::add(p); }
  void set_point(int i,Point p) { Shape::set_point(i,p); }
  void draw_lines() const;
  Point last_removed_point;
private:
  //vector<Point> lastV;  //vector of Last points
  //vector<Point> nextV;  //vector of next points
};

void DLL::draw_lines() const
{
  // draw the DLL Last/Next rectangle:
  for (int i=0; color().visibility() && (i < number_of_points()); i++) {
    // first draw the rectangle
    fl_line(point(i).x,  // left side of rectangle
            point(i).y,
            point(i).x,
            point(i).y - 24);
    fl_line(point(i).x,  // top side of rectangle
            point(i).y - 24,
            point(i).x + 40,
            point(i).y - 24);
    fl_line(point(i).x + 40,  // right side of rectangle
            point(i).y - 24,
            point(i).x + 40,
            point(i).y);
    fl_line(point(i).x + 40,  // bottom side of rectangle
            point(i).y,
            point(i).x,
            point(i).y);
    if (i > 0) {
      if (point(i-1) != point(i)) { // skip "removed" points
        // draw the line (must have at least two points)
        fl_line(point(i-1).x,
                point(i-1).y,
                point(i).x,
                point(i).y);
        // now add the Next/Last text (must have at least two points)
        int ofnt = fl_font();
        int osz = fl_size();
        // make the Next point Text object
        ostringstream nexts;  // Next point for previous point is this point
        nexts << point(i).x << "," << point(i).y;
        Text nextt(Point(point(i-1).x + 5,
                         point(i-1).y - 2), // lower left corner of baseline
                   nexts.str());  // content
        nextt.set_font(Graph_lib::Font::times_bold);
        nextt.set_font_size(10);  // height in pixels
        // now have FLTK draw the Next point Text
        fl_font(nextt.font().as_int(),nextt.font_size());
        fl_draw(nextt.label().c_str(),nextt.point(0).x,nextt.point(0).y);
        fl_font(ofnt,osz);
        // make the Last point Text object
        ostringstream lasts;  // Last point for this point is previous point
        lasts << point(i-1).x << "," << point(i-1).y;
        Text lastt(Point(point(i).x + 5,
                         point(i).y - 12), // lower left corner of baseline
                   lasts.str());  // content
        lastt.set_font(Graph_lib::Font::times_bold);
        lastt.set_font_size(10);  // height in pixels
        // now have FLTK draw the Last point Text
        fl_font(lastt.font().as_int(),lastt.font_size());
        fl_draw(lastt.label().c_str(),lastt.point(0).x,lastt.point(0).y);
        fl_font(ofnt,osz);
      }
    }
  }
}


//-----------------------------------------------------------
// define a struct that is a window in which a DLL Curve can
// be entered via a GUI

struct DLL_window : Graph_lib::Window {       // inherits from Window

  // constructor
  DLL_window(Point xy,             // top lefthand corner
	       int w,                // width
	       int h,                // height
	       const string& title); // label

private:
  // data members
  DLL dll;                // shape to hold the DLL points

  // widgets:
  Button next_button;                // button indicating next DLL point is ready
  Button quit_button;                // end program
  In_box next_x;                     // box for entering x coord of point to add
  In_box next_y;                     // box for entering y coord of point to add
  Out_box xy_out;                    // box for displaying last points added
  In_box next_xx;                    // box for entering x coord of point to remove
  In_box next_yx;                    // box for entering y coord of point to remove
  Out_box xyx_out;                   // box for displaying last points removed
  Menu color_menu;                   // menu of color choices for the DLL
  Button menu_button;                // button to display the color menu
  
  //Additions for new inboxes and outboxes
  Button bank_menu;
  //out boxes for top bar of displaying all the monies.
  Out_box usd_out;
  Out_box gbp_out;
  Out_box eur_out;
  Out_box jpy_out;
  Out_box rub_out;
  Out_box all_out;
  
  //inboxes below the top bar
  In_box input_1;
  In_box input_2;
  In_box input_3;
  In_box input_4;
  In_box input_5;
  In_box input_6;
  
  //outboxes below the input boxes initializing
  Out_box output_1;
  Out_box output_2;
  Out_box output_3;
  Out_box output_4;
  Out_box output_5;
  Out_box output_6;
  
  // function members

  void change(Color c) {             // change the color of the DLL
    dll.set_color(c);
  }

  void hide_menu() {     
    // hides the color menu and shows the button to display the color menu
    color_menu.hide(); 
    menu_button.show(); 
  }

  // actions invoked by callbacks:

  void red_pressed() {
    change(Color::red);
    hide_menu();        // once a color is chosen from the menu, hide the menu
  }

  void blue_pressed() {
    change(Color::blue);
    hide_menu();
  }

  void black_pressed() {
    change(Color::black);
    hide_menu();
  }

  void menu_pressed() {
    // when menu button is pressed, hide the menu button and show the 
    // actual menu of colors
    menu_button.hide();    
    color_menu.show();
  }

  void next();   // defined below

  void quit();   // defined below

  // callback functions; declared here and defined below.

  static void cb_red(Address, Address);
  static void cb_blue(Address, Address);
  static void cb_black(Address, Address);
  static void cb_menu(Address, Address);
  static void cb_next(Address, Address);
  static void cb_quit(Address, Address);
};

// ----------------------------------------------------------
// now define the parts of DLL_window that were only declared
// inside the class

// constructor:

DLL_window::DLL_window(Point xy, int w, int h, const string& title) : 

  // initialization - start by calling constructor of base class 
  Window(xy,w,h,title),    

  // initialize "Next curve" button
  next_button(
	      Point(x_max()-150,0),   // location of button
	      70, 20,                 // dimensions of button
	      "Next curve",           // label of button
	      cb_next),               // callback function for button
  // initialize quit button
  quit_button(
	      Point(x_max()-70,0),    // location of button
	      70, 20,                 // dimensions of button 
	      "Quit",                 // label of button
	      cb_quit),               // callback function for button
  // initialize the next_x inbox
  next_x(
	 Point(x_max()-330,0),       // location of box
	 50, 20,                     // dimensions of box
	 "coord x:"),                // label of box 
  // initialize the next_y inbox
  next_y(
	 Point(x_max()-210,0),       // location of box
	 50, 20,                     // dimensions of box
	 "coord y:"),                // label of box
  // initialize the outbox
  xy_out(
	 Point(100,0),               // location of box
	 100, 20,                    // dimensions of box
	 "coord (x,y):"),            // label of box
  // initialize the scalar_x inbox
  next_xx(
	 Point(x_max()-330,30),      // location of box
	 50, 20,                     // dimensions of box
	 "remove x:"),               // label of box 
  // initialize the scalar_y inbox
  next_yx(
	 Point(x_max()-210,30),      // location of box
	 50, 20,                     // dimensions of box
	 "remove y:"),               // label of box
  // initialize the outbox
  xyx_out(
	 Point(100,30),              // location of box
	 100, 20,                    // dimensions of box
	 "remove (x,y):"),           // label of box
  // initialize the color menu
  color_menu(                        
	     Point(x_max()-70,30),   // location of menu
	     70, 20,                 // dimensions of menu
	     Menu::vertical,         // list menu items vertically
	     "color"),               // label of menu 
  // initialize the menu button
  menu_button(
	      Point(x_max()-80,30),  // location of menu button
	      80, 20,                // dimensions of button 
	      "color menu",          // label of button
	      cb_menu)               // callback for button

  // body of constructor follows
{
  // attach buttons and boxes to window
  attach(next_button);
  attach(quit_button);
  attach(next_x);
  attach(next_y);
  attach(xy_out);
  xy_out.put("no coord");        // output to out box
  attach(next_xx);
  attach(next_yx);
  attach(xyx_out);
  xyx_out.put("no coord");       // output to out box

  dll.last_removed_point = Point(next_xx.get_int(),next_yx.get_int());

  // First make 3 buttons for color menu, one for each color, and 
  // attach them to the menu: the attach function of the Menu struct
  // adjusts the size and location of the buttons; note callback functions).
  // Then attach menu to window but hide it (initially, the menu button
  // is displayed, not the actual menu of color choices).

  color_menu.attach(new Button(Point(0,0),0,0,"red",cb_red)); 
  color_menu.attach(new Button(Point(0,0),0,0,"blue",cb_blue));
  color_menu.attach(new Button(Point(0,0),0,0,"black",cb_black));
  attach(color_menu);
  color_menu.hide(); 

  // attach menu button
  attach(menu_button);

  // attach shape that holds the DLL to be displayed
  attach(dll);
}

// ---------------------------- 
// callback function for quit button - boilerplate: 
// When the button is pressed, the system invokes the
// specified callback function.  First argument is address of the
// button (which we won't use, so we don't bother to name it).  Second
// argument, named pw, is address of the window containing the pressed
// button, i.e., address of our DLL_window object.  reference_to
// converts the address pw into a reference to a DLL_window object,
// so we can call the quit() function.  Objective is to call function
// quit() which does the real work specific to this button.

void DLL_window::cb_quit(Address, Address pw) {
  reference_to<DLL_window>(pw).quit();   // quit is defined next
}

//------------------------------------
// what to do when quit button is pressed

void DLL_window::quit() {
  hide();                   // FLTK idiom for delete window
}

// ----------------------------
// callback function for next button - boilerplate:

void DLL_window::cb_next(Address, Address pw) {
  reference_to<DLL_window>(pw).next();  // next is defined next
}

// -------------------------------
// what to do when "next curve" button is pressed

void DLL_window::next() {
  // get input data from the inboxes - x and y coordinates
  // of next curve
  int x = next_x.get_int();
  int y = next_y.get_int();
  int xx = next_xx.get_int();
  int yx = next_yx.get_int();

  // add the new point to the DLL object (if a new "add" point was entered)
  if (!dll.number_of_points() || (dll.point(dll.number_of_points()-1) != Point(x,y)))
    dll.add(Point(x,y));

  // "remove" point from the DLL object (if a new "remove" point was entered)
  // RESTRICTION!! must have at least two points to "remove" a point
  if (dll.number_of_points() && (dll.last_removed_point != Point(xx,yx))) {
    for (int i=0; i < dll.number_of_points(); i++) {
      // remove ALL matching points
      if (dll.point(i) == Point(xx,yx)) {
        // since Shape does not support removing a point...
        if (i==0) dll.set_point(i,dll.point(i+1));  // ...if 1st point "remove" it by setting it equal to next point
	else dll.set_point(i,dll.point(i-1));       // ...else "remove" it by setting it equal to previous point
        dll.last_removed_point = Point(xx,yx);
      }
    }
  }

  // update current position & scalar readouts - make strings with the
  // coordinate & scalar info and use the out boxes
  stringstream ss;
  ss << '(' << x << ',' << y << ')';
  xy_out.put(ss.str());
  stringstream ssx;
  ssx << '(' << xx << ',' << yx << ')';
  xyx_out.put(ssx.str());

  redraw();  // function inherited from Window to redraw the window
}

// -------------------------------
// callback for when red button (part of color menu) is pressed - boilerplate

void DLL_window::cb_red(Address, Address pw) {
  reference_to<DLL_window>(pw).red_pressed();  
  // red_pressed defined in DLL_window class as part of declaration
}

// -------------------------------
// callback for when blue button (part of color menu) is pressed - boilerplate

void DLL_window::cb_blue(Address, Address pw) {
  reference_to<DLL_window>(pw).blue_pressed();  
  // blue_pressed defined in DLL_window class as part of declaration
}

// -------------------------------
// callback for when black button (part of color menu) is pressed - boilerplate

void DLL_window::cb_black(Address, Address pw) {
  reference_to<DLL_window>(pw).black_pressed();  
  // black_pressed defined in DLL_window class as part of declaration
}

// -------------------------------
// callback for when menu button is pressed - boilerplate

void DLL_window::cb_menu(Address, Address pw)
{  
    reference_to<DLL_window>(pw).menu_pressed();
    // menu_pressed defined in DLL_window class as part of declaration
} 

// ---------------------------------------------------
// main - just creates window and invokes gui_main

int main() 
  try {
    // construct the GUI window
    DLL_window win(Point(100,100),800,400,"Phase 2 bank");
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