DIRECTORY ?= ../
INCLUDE = $(DIRECTORY)/include 
LIBRARY = $(DIRECTORY)/lib

CC=gcc
CXX=g++


CXXFLAGS = -g -std=c++0x -O0 -Wno-deprecated -Wreturn-type  -Wuninitialized -Wunused -Wunused-value -Wunused-variable \
		   -Wunused-function -Wmissing-field-initializers -Winit-self -Wmissing-include-dirs -Warray-bounds \
		   -Wswitch -Wswitch-default -Wno-div-by-zero -Wfloat-equal -Wtype-limits -Werror\
	   	   -I$(INCLUDE)  

LDFLAGS = -L$(LIBRARY) -lbasenet_net -lbasenet_base -lpthread -lrt -lboost_random\
			-lboost_date_time\

all: tserver

clean:
	rm -rf tserver core* *.o

tserver: 
	${CXX} $(CXXFLAGS) -o tserver *.cpp $(LDFLAGS) 

.PHONY: all clean

