 #
 # Course: CS 100 Summer Session 2 2012
 #
 # First Name: Sam
 # Last Name: Lee
 # Username: slee103
 # email address: slee103@ucr.edu
 #
 #
 # Assignment: assn3
 # Filename : Makefile
 #
 # I hereby certify that the contents of this file represent
 # my own original individual work. Nowhere herein is there 
 # code from any outside resources such as another individual,
 # a website, or publishings unless specifically designated as
 # permissible by the instructor or TA.
 #/ 

CXX=g++
CXXFLAGS=-g -W -Wall -Werror
OBJECTS=myshell.cc

all:
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o myshell

clean:
	rm -f *~ myshell *.gch assn3.gz

tar:
	tar -czvf assn3.gz myshell.cc Makefile design.txt README
