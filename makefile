# UNAME_S := $(shell uname -s)
# TOP := $(shell pwd)
# ifeq ($(UNAME_S),Linux)
#     FLAGS += $(TOP)/chilkat/lib/libchilkat-9.5.0.so
# endif
# ifeq ($(UNAME_S),Darwin)
#     FLAGS += chilkat/lib/libchilkat.a
# endif
# FLAGS += -lresolv -lpthread

reader: main.o environment.o moviment.o
	g++ -std=c++11 main.o environment.o moviment.o -o reader

main.o: main.cpp include/environment.h include/moviment.h
	g++ -std=c++11 -c main.cpp

environment.o: cpp/environment.cpp include/environment.h
	g++ -std=c++11 -c cpp/environment.cpp

moviment.o: cpp/moviment.cpp include/moviment.h include/environment.h
	g++ -std=c++11 -c cpp/moviment.cpp

clean:
	rm *.o reader