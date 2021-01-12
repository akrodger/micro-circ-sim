################################################################################
##                                                                            ##
##                         makefile Template                                  ##
##                       Written by Bram Rodgers                              ##
##                  Initial draft written May 13, 2020                        ##
##                                                                            ##
################################################################################

#A default compiler. (DC = Default Compiler)
DC=gcc
#Program compilation flags (CFLAGS = Compiler Flags)
CFLAGS=-g -Wall #-Werror
#Some default common linked libraries (CLINX = Common Linkages)
CLINX=-lm
#A default OpenMP compilation flag. Set blank for serial code.
OMP=#-fopenmp

#An archiving software for making static libraries
AR=ar
#Flags for the archiving software
ARFLAGS=-rcs

#The file type extension of the source code used. (SRC_T = source type)
SRC_T=c
#A default file extension for executable files (EXE_T = executable type)
EXE_T=x

#A listing of source code. Automatically detects all in this folder
SRC_FILES=$(wildcard *.$(SRC_T))
#Dependencies listing for the source files
DEP_FILES=$(subst .$(SRC_T),.d,$(SRC_FILES))

#A name for an archive file for MicroCircSim
ARCH_FILE=libmcs.a
#A default name of an executable
EXE_NM=exec.$(EXE_T)

#Subdirectories filled with various modules
CE=circuit_elements
EH=error_handling
NP=netlist_parser
#List these objects together on the OBJ_FILES list.
OBJ_FILES=$(CE)/$(CE).o $(EH)/$(EH).o $(NP)/$(NP).o

#Begin Makefile recipes template
#.PHONY means that this recipe does not make a file which has the
#same name as this recipe. Example: the ``clean'' routine does not make
#a file called ``clean'' , instead it removes files.

#Default recipe of makefile.
.PHONY: default
default: exec
	@echo "Default recipe of makefile."

#A recipe for renaming the file extension type of choice with .o files
#This is not ``.PHONY'' because it makes actual files with those names.
%.o : %.$(SRC_T)
	$(DC) $(CFLAGS) $(OMP) -c $< -o $@
	
#Object file make recipe. Just calls all the %.o make rules.
.PHONY: objs
objs: $(OBJ_FILES)

#Including the dependent files. forces makefile to run deps every time.
#-include deps

#Dependent files make recipe. Makes a .d file listing the includes of sources.
%.d: %.$(SRC_T)
	$(DC) $< -MM -MT $(@:.d=.o) > $@

#Object file make recipe. Just calls all the %.d make rules.
.PHONY: deps
deps: $(DEP_FILES)

#Creates an executable based on the EXE_NM variable listed above.
.PHONY: exec
exec: $(EXE_NM)

#Creates an executable binary file with the name stored in $(EXE_NM)
$(EXE_NM): $(OBJ_FILES)
	$(DC) $(CLINX) $^ -o $(EXE_NM)

#Creates an archived static library using the object files in this directory.
.PHONY: arch
arch: $(ARCH_FILE)

#Rule for creating an archive file with name $(ARCH_FILE)
$(ARCH_FILE): $(OBJ_FILES)
	$(AR) $(ARFLAGS) $@ $^

#Go into subdirectory $(SUBDIR) and call the makefile contained there.
.PHONY: libsubdir
libsubdir:
	$(MAKE) -C $(SUBDIR)

#$(CE)/$(CE).o:
#	$(MAKE) -C $(CE) objs

#$(EH)/$(EH).o:
#	$(MAKE) -C $(EH) objs

#$(NP)/$(NP).o:
#	$(MAKE) -C $(NP) objs

#A basic recipe for cleaning up object files and executables.
.PHONY: clean
clean: cleansubdir
	@if rm *.o ; then echo "Removed object files."; fi
	@if rm *.a ; then echo "Removed archive files."; fi
	@if rm *.d ; then echo "Removed dependency files."; fi
	@if rm *.$(EXE_T) ; then echo "Removed executable files."; fi

#Calls the clean recipe of the subdirectory $(SUBDIR)
#Small projects do no need this. Simply uncomment to enable this.
.PHONY: cleansubdir
cleansubdir: 
	$(MAKE) -C $(CE) clean
	$(MAKE) -C $(EH) clean
	$(MAKE) -C $(NP) clean
