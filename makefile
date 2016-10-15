# UNAME_S := $(shell uname -s)
# TOP := $(shell pwd)
# ifeq ($(UNAME_S),Linux)
#     FLAGS += $(TOP)/chilkat/lib/libchilkat-9.5.0.so
# endif
# ifeq ($(UNAME_S),Darwin)
#     FLAGS += chilkat/lib/libchilkat.a
# endif
# FLAGS += -lresolv -lpthread

all: tp1-problema1 tp1-problema2

tp1-problema1: main_tp1.o environment.o moviment.o
	g++ -std=c++11 -O3 main_tp1.o environment.o moviment.o -o tp1-problema1

tp1-problema2: main_tp2.o environment.o moviment.o
	g++ -std=c++11 -O3 main_tp2.o environment.o moviment.o -o tp1-problema2

main_tp1.o: main_tp1.cpp include/p1/environment.h include/p1/moviment.h
	g++ -std=c++11 -O3 -c main_tp1.cpp

main_tp2.o: main_tp2.cpp include/p1/environment.h include/p1/moviment.h
	g++ -std=c++11 -O3 -c main_tp2.cpp

environment.o: cpp/p1/environment.cpp include/p1/environment.h
	g++ -std=c++11 -O3 -c cpp/p1/environment.cpp

moviment.o: cpp/p1/moviment.cpp include/p1/environment.h include/p1/moviment.h
	g++ -std=c++11 -O3 -c cpp/p1/moviment.cpp

clean:
	rm *.o tp1-problema1 tp1-problema2