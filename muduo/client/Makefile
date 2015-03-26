DIRECTORY ?= ../
INCLUDE = $(DIRECTORY)/include 
LIBRARY = $(DIRECTORY)/lib

CC=gcc
CXX=g++


CXXFLAGS = -g -std=c++0x -O0 -Wno-deprecated -Wreturn-type  -Wuninitialized -Wunused -Wunused-value -Wunused-variable \
		   -Wunused-function -Wmissing-field-initializers -Winit-self -Wmissing-include-dirs -Warray-bounds \
		   -Wswitch -Wswitch-default -Wno-div-by-zero -Wfloat-equal -Wtype-limits -Werror\
	   	   -I$(INCLUDE)  

LDFLAGS = -L$(LIBRARY) -lmuduo_net -lmuduo_base -lpthread -lrt -lboost_date_time\

all: tclient

clean:
	rm -rf tclient core* *.o

tclient: 
	${CXX} $(CXXFLAGS) -o tclient *.cpp $(LDFLAGS) 

.PHONY: all clean

