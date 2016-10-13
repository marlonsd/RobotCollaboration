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

main_tp1.o: main_tp1.cpp include/environment.h include/moviment.h
	g++ -std=c++11 -O3 -c main_tp1.cpp

environment.o: cpp/environment.cpp include/environment.h
	g++ -std=c++11 -O3 -c cpp/environment.cpp

moviment.o: cpp/moviment.cpp include/environment.h include/moviment.h
	g++ -std=c++11 -O3 -c cpp/moviment.cpp

clean:
	rm *.o tp1-problema1 tp1-problema2