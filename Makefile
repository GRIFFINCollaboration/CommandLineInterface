.EXPORT_ALL_VARIABLES:

.SUFFIXES:

.PHONY: clean all

SHELL 		= /bin/sh

LIB_DIR 	= $(HOME)/lib
BIN_DIR		= $(HOME)/bin

ROOTCFLAGS   := $(shell root-config --cflags)
ROOTLIBS     := $(shell root-config --libs)
ROOTGLIBS    := $(shell root-config --glibs)
ROOTINC      := -I$(shell root-config --incdir)

INCLUDES        = -I.

LIBRARIES	= 

CC		= gcc
CXX             = g++
CPPFLAGS 	= $(ROOTINC) $(INCLUDES) -fPIC
CXXFLAGS	= -std=c++11 -pedantic -Wall -Wno-long-long -g -O3

LDFLAGS		= -g -fPIC

LDLIBS 		= -L$(LIB_DIR) $(ROOTLIBS) $(addprefix -l,$(LIBRARIES)) -lm

LOADLIBES	= CommandLineInterface.o Utilities.o TextAttributes.o

# -------------------- implicit rules --------------------
# n.o made from n.c by 		$(CC) -c $(CPPFLAGS) $(CFLAGS)
# n.o made from n.cc by 	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS)
# n made from n.o by 		$(CC) $(LDFLAGS) n.o $(LOADLIBES) $(LDLIBS)

# -------------------- rules --------------------

# for library: add $(LIB_DIR)/lib$(NAME).so
all:  libCommandLineInterface.so libUtilities.so libTextAttributes.so
	@echo Done

# -------------------- libraries --------------------

lib%.so: %.o
	$(CXX) $(LDFLAGS) -shared -o $(LIB_DIR)/$@.1.0.1 $< $(LDLIBS) -lc

# -------------------- pattern rules --------------------
# this rule sets the name of the .cc file at the beginning of the line (easier to find)

%.o: %.cc %.hh
	$(CXX) $< -c $(CPPFLAGS) $(CXXFLAGS) -o $@

# -------------------- default rule for executables --------------------

%: %.cc $(LOADLIBES)
	$(CXX) $< $(CXXFLAGS) $(CPPFLAGS) $(LOADLIBES) $(LDLIBS) -o $@


tar:
	@echo "creating zipped tar-ball ... "
	tar -chvzf CommandLineInterface.tar.gz CommandLineInterface.cc CommandLineInterface.hh Makefile test.cc Utilities.cc Utilities.hh TextAttributes.cc TextAttributes.hh

#--------------------------------------------------
clean:
	rm  -f *.o
