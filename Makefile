CFLAGS = -O2 -Wall -Wextra -ansi -pedantic -DNDEBUG
LIBS = -lgsl -lgslcblas -lboost_thread -lboost_system

default:
	g++ $(CFLAGS) -c *.cpp

clean:
	rm -f *.o


