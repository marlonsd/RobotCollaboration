# UNAME_S := $(shell uname -s)
# TOP := $(shell pwd)
# ifeq ($(UNAME_S),Linux)
#     FLAGS += $(TOP)/chilkat/lib/libchilkat-9.5.0.so
# endif
# ifeq ($(UNAME_S),Darwin)
#     FLAGS += chilkat/lib/libchilkat.a
# endif
# FLAGS += -lresolv -lpthread

reader: main.o environment.o
	g++ -std=c++11 main.o environment.o -o reader

main.o: main.cpp environment.h
	g++ -std=c++11 -c main.cpp

environment.o: environment.cpp environment.h
	g++ -std=c++11 -c environment.cpp

clean:
	rm *.o reader