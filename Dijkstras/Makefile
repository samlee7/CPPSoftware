 #
 # Course: CS 100 Summer Session 2 2012
 #
 # First Name: Sam
 # Last Name: Lee
 # Username: slee103
 # email address: slee103@ucr.edu
 #
 #
 # Assignment: assn5
 # Filename : Makefile
 #
 # I hereby certify that the contents of this file represent
 # my own original individual work. Nowhere herein is there 
 # code from any outside resources such as another individual,
 # a website, or publishings unless specifically designated as
 # permissible by the instructor or TA.
 #/ 
CXX=g++
CXXFLAGS=-g -w -Wall -Werror
OBJECTS=main.o

all:
	$(CXX) $(CXXFLAGS) priority_queue.H main.cc

clean:
	rm -f *~ *.gch a.out main.o assn5.gz

tar:
	tar -czvf assn5.gz main.cc priority_queue.H Makefile dictionary.txt
