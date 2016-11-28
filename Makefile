all: Main, Bank, Patron, Chrono

%: %.cpp
	g++ -std=c++11 $< -o $@