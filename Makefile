CFLAGS = -O2 -Wall -Wextra -ansi -pedantic -DNDEBUG
LIBS = -ldnest3 -lgsl -lgslcblas -lboost_thread -lboost_system

default:
	g++ $(CFLAGS) -c *.cpp MassDistributions/*.cpp
	g++ -o main *.o $(LIBS)

clean:
	rm -f *.o
	rm -f main
