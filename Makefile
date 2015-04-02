.EXPORT_ALL_VARIABLES:

.PHONY: clean all

LIB_DIR = $(HOME)/lib

ROOTCFLAGS   := $(shell root-config --cflags)
ROOTLIBS     := $(shell root-config --libs)
ROOTGLIBS    := $(shell root-config --glibs)
ROOTINC      := -I$(shell root-config --incdir)

ALLIBS  = -lm $(ROOTGLIBS) -L$(HOME)/lib 

CC		= gcc
CPP             = g++
CFLAGS		= -g2 -O3 $(ROOTCFLAGS) -fpic

INCLUDES        = -I./

LFLAGS		= -g -fpic
LIBS 		= $(ALLIBS)

all:  libCommandLineInterface.so libUtilities.so
	@echo Done

test: test.cc CommandLineInterface.o Utilities.o
	$(CPP) $(CFLAGS) $(INCLUDES) $< CommandLineInterface.o Utilities.o $(LIBS) -o $@

lib%.so: %.o
	$(CPP) $(LFLAGS) -shared -o $(LIB_DIR)/$@.1.0.1 $^ $(LIBS) -lc
#	@ !(test -L $(LIB_DIR)/$@) && ln -s $(LIB_DIR)/$@.1.0.1 $(LIB_DIR)/$@

%.o: %.cc %.hh
	$(CPP) $(CFLAGS) $(INCLUDES) -c $< -o $@

tar:
	@echo "creating zipped tar-ball ... "
	tar -chvzf CommandLineInterface.tar.gz CommandLineInterface.cc CommandLineInterface.hh Makefile test.cc Utilities.cc Utilities.hh

#--------------------------------------------------
clean:
	rm  -f *.o
