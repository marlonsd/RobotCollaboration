# UNAME_S := $(shell uname -s)
# TOP := $(shell pwd)
# ifeq ($(UNAME_S),Linux)
#     FLAGS += $(TOP)/chilkat/lib/libchilkat-9.5.0.so
# endif
# ifeq ($(UNAME_S),Darwin)
#     FLAGS += chilkat/lib/libchilkat.a
# endif
# FLAGS += -lresolv -lpthread

all: tp1-problema1 tp1-problema2 tp1-problema3

#### Problems 1 and 2

tp1-problema1: main_tp1.o environment.o moviment.o
	g++ -std=c++11 -O3 main_tp1.o environment.o moviment.o -o tp1-problema1

main_tp1.o: main_tp1.cpp include/p1/environment.h include/p1/moviment.h
	g++ -std=c++11 -O3 -c main_tp1.cpp

tp1-problema2: main_tp2.o environment.o moviment.o
	g++ -std=c++11 -O3 main_tp2.o environment.o moviment.o -o tp1-problema2

main_tp2.o: main_tp2.cpp include/p1/environment.h include/p1/moviment.h
	g++ -std=c++11 -O3 -c main_tp2.cpp

# Includes

environment.o: cpp/p1/environment.cpp include/p1/environment.h
	g++ -std=c++11 -O3 -c cpp/p1/environment.cpp

moviment.o: cpp/p1/moviment.cpp include/p1/environment.h include/p1/moviment.h
	g++ -std=c++11 -O3 -c cpp/p1/moviment.cpp



#### Problem 3

tp1-problema3: main_tp3.o environment.o environment_bridge.o
	g++ -std=c++11 -O3 main_tp3.o environment.o environment_bridge.o -o tp1-problema3

main_tp3.o: main_tp3.cpp include/p2/environment_bridge.h include/p1/environment.h
	g++ -std=c++11 -O3 -c main_tp3.cpp

# Includes

environment_bridge.o: cpp/p2/environment_bridge.cpp include/p2/environment_bridge.h include/p1/environment.h
	g++ -std=c++11 -O3 -c cpp/p2/environment_bridge.cpp

clean:
	rm *.o tp1-problema1 tp1-problema2 tp1-problema3