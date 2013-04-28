CFLAGS = -O2 -Wall -Wextra -ansi -pedantic -DNDEBUG
LIBS = -ldnest3 -lgsl -lgslcblas -lboost_thread -lboost_system

default:
	g++ $(CFLAGS) -c *.cpp MassDistributions/*.cpp SpatialDistributions/*.cpp
	g++ -o main *.o $(LIBS)
	rm -f *.o

clean:
	rm -f *.o
	rm -f main
