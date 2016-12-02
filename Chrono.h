
//
// This is example code from Chapter 9.8 "The Date class" of 
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#ifndef CHRONO_H

#include "std_lib_facilities_4.h"
// include the following to get current Date and Time
#include <iomanip>
#include <ctime>

//------------------------------------------------------------------------------

namespace Chrono {

//------------------------------------------------------------------------------

class Date {
public:
	enum Month {
		jan=1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
	};

	class Invalid { };              // to throw as exception

	Date(int y, Month m, int d);	// check for valid date and initialize
	Date(Month m, int d, int y);    // check for valid date and initialize
	Date();                            // default constructor
	// the default copy operations are fine

	// non-modifying operations:
	int   day()   const { return d; }
	Month month() const { return m; }
	int   year()  const { return y; }

	// modifying operations:
	void add_day(int n);
	void add_month(int n);
	void add_year(int n);
private:
	int   y;
	Month m;
	int   d;
};

//------------------------------------------------------------------------------

bool is_date(int y, Date::Month m, int d); // true for valid date

//------------------------------------------------------------------------------

bool leapyear(int y);                  // true if y is a leap year

//------------------------------------------------------------------------------

// displays years,months,days of current Date from 911 
void calc911(int y, Date::Month m, int d); 

//------------------------------------------------------------------------------

bool operator==(const Date& a, const Date& b);
bool operator!=(const Date& a, const Date& b);

//------------------------------------------------------------------------------

ostream& operator<<(ostream& os, const Date& d);
istream& operator>>(istream& is, Date& dd);

//------------------------------------------------------------------------------

class Time {
public:
	enum AmPm { am=1, pm };

	class Invalid { };                      // to throw as exception

	Time(int h, int m, int s);              // check for valid 24 hr time and initialize
	Time(int h, int m, int s, AmPm a);      // check for valid 12 hr time and initialize
	Time();                                 // default constructor
	// the default copy operations are fine

	// non-modifying operations:
	int  hour()   const { return h; }
	int  minute() const { return m; }
	int  second() const { return s; }
	AmPm am_pm()  const { return a; }

	// modifying operations:
	void set_am_pm();  // fixes am_pm setting after 24 hr format is used to set Time        

private:
	int   h;
	int   m;
	int   s;
	AmPm  a;
};

//------------------------------------------------------------------------------

bool is_time_24(int h, int m, int s); // true for valid 24 hr time

//------------------------------------------------------------------------------

bool is_time_12(int h, int m, int s, Time::AmPm a); // true for valid 12 hr time

//------------------------------------------------------------------------------

bool operator==(const Time& a, const Time& b);
bool operator!=(const Time& a, const Time& b);

//------------------------------------------------------------------------------

ostream& operator<<(ostream& os, const Time& d);
istream& operator>>(istream& is, Time& dd);

//------------------------------------------------------------------------------

} // Chrono

#endif //CHRONO_H
