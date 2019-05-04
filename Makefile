#!/usr/bin/make -f
#
# Filename:		Makefile
# Date:			5/4/2019
# Author:		Jackson Allen
# Email:		jta170000@utdallas.edu
# Version:		1.0
# Copyright:		2019, All Rights Reserved
#
# Description:
#
#	A moderately complex makefile that takes care of 
#	creating dependencies


# Set up needed values to support make's implicit commands
# for compiling C++ source files.

# The compiler to use
CXX = g++

# C pre-processor flags
CPPFLAGS = -I/scratch/perkins/include

# compiler flags
CXXFLAGS = -Wall

# linker flags
LDFLAGS = -L/scratch/perkins/lib
LDLIBS = -lcdk -lcurses


# Project name.  This is used in building the file name for the backup target
PROJECTNAME = program6


# Enter the names of the C++ source files that you want to compile
# with this project

SRCS = cdkExample.cc

# Enter the name for the executable to be created
EXEC = program6


#
# You normally don't need to change anything below here.
# ======================================================
#
OBJS = $(SRCS:cc=o)

.PHONY: all clean

all: $(EXEC)
clean:
	rm -f $(OBJS) *.d *~ $(EXEC)
cleanish:
	rm -f $(OBJS) *.d *~
tarball: cleanish
	tar cfvz ../program5.tar.gz ../program5


# Pattern for .d files.
%.d:%.cc
	@echo Updating .d Dependency File
	@set -e; rm -f $@; \
	$(CXX) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$


#  This is a rule to link the files.  Pretty standard
$(EXEC): $(OBJS)
	$(CXX) -o $(EXEC) $(LDFLAGS) $(OBJS) $(LDLIBS)

Makefile: $(SRCS:.cc=.d)


# Backup Target
backup:	clean
	@mkdir -p ~/backups; chmod 700 ~/backups
	@$(eval CURDIRNAME := $(shell basename `pwd`))
	@$(eval MKBKUPNAME := ~/backups/$(PROJECTNAME)-$(shell date +'%Y.%m.%d-%H:%M:%S').tar.gz)
	@echo
	@echo Writing Backup file to: $(MKBKUPNAME)
	@echo
	@-tar zcfv $(MKBKUPNAME) ../$(CURDIRNAME)
	@chmod 600 $(MKBKUPNAME)
	@echo
	@echo Done!


# Include the dependency files created by the PreProcessor.  The
# dash in front of the command keeps the system from complaining
# if the files do not exist.

-include $(SRCS:.cc=.d)

