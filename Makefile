CFLAGS = -O2 -Wall -Wextra -ansi -pedantic -DNDEBUG
LIBS = -ldnest3 -lgsl -lgslcblas -lboost_thread -lboost_system

default:
	# Compile the .cpp files into .o files
	g++ $(CFLAGS) -c *.cpp
	# Link the RJObject demo binary
	g++ -o RJObject RJObject.o $(LIBS)

clean:
	# Delete the object files
	rm -f *.o
	# Delete the binaries
	rm -f RJObject


