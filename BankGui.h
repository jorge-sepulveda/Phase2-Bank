// HW8-PR1: Write a new program (hw8-pr1) meeting at least the following minimum requirements:
// 1. Use the FLTK Graphics Interface Library (Graph.h&cpp GUI.h&cpp Simple_window.h&cpp 
//    Window.h&cpp contained in PPP.tar.gz from Piazza), and create a new struct called DLL
//    (Doubly Linked List) derived from the base Shape class.  This new struct should 
//    graphically present a DLL representation as follows:
//      - As each new point is added to the DLL points vector (inherited from Shape) that 
//        new point will be connected to the previous point (if it exists) by a line (using
//        the current DLL line style and color, both also inherited from Shape), and then a
//        rectangle (width=50 and height=26) will be drawn at the new point (the rectangle
//        lower-left corner is anchored to the new point).  The x,y coordinates of the
//        previous point (if it exists) will be displayed in the top half of the rectangle,
//        and the x,y coordinates of the new point will be written into the bottom half of
//        the rectangle attached to the previous point (if it exists).  NOTE!! The bottom
//        half of the rectangle attached to the new point will remain empty, until it is
//        updated when the next new point is added.  NOTE!! The rectangle attached to the
//        first DLL point will always have an empty upper half, and the rectangle attached
//        to the last DLL point will always have an empty lower half.
//      - You will need to overload Shape’s draw_lines() virtual member function in DLL to
//        draw the lines between points, and to add the rectangles (and the Last/Next X,Y
//        coordinates text inside) at each point in the DLL (NOTE!! You likely will need to
//        “borrow” code from the Text draw_lines() function in Graph.cpp to display the text
//        in the rectangle).  
// 2. In the main() portion of hw8-pr1 declare a Simple_window object called win, and then
//    declare a DLL object called dll, and do the following to the dll object:
//      - Add a point at 50,100
//      - Add a point at 100,150
//      - Add a point at 150,200
//      - Add a point at 200,250
//      - Add a point at 250,300
//      - Add a point at 300,250
//      - Add a point at 350,200
//      - Add a point at 400,150
//      - Add a point at 450,100
//      - Change the DLL color to red
//      - Attach the DLL to the Simple_window
//      - Redraw the Simple_window (wait_for_button)
// 3. Use the following command on build.tamu.edu to compile your program:
// g++ hw8-pr1.cpp Graph.cpp GUI.cpp Simple_window.cpp Window.cpp -lfltk -lfltk_images -o hw8-pr1

#include "std_lib_facilities_4.h"
#include "Simple_window.h"
#include "Graph.h"


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




int main()
try {
  if(H112 != 201401L)error("Error: incorrect std_lib_facilities_4.h version ",
		  	   H112);
  // Window
  Simple_window win(
		    Point(100,100),    // coordinates of top left corner
		    600,400,           // width and height of window
		    "HW8-PR1");        // title

  // DLL Doubly Linked List
  DLL dll;
  // add points to DLL
  dll.add(Point(50,100));
  dll.add(Point(100,150));
  dll.add(Point(150,200));
  dll.add(Point(200,250));
  dll.add(Point(250,300));
  dll.add(Point(300,250));
  dll.add(Point(350,200));
  dll.add(Point(400,150));
  dll.add(Point(450,100));
  dll.set_color(Color::red);  // make the DLL red
  win.attach(dll);        // attach DLL to window

  win.wait_for_button();

  return 0;
}
catch(exception& e) {
	cerr << "exception: " << e.what() << '\n';
	return 1;
}
catch (...) {
	cerr << "Some exception\n";
	return 2;
}