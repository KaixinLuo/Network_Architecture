# makefile for the students

#  This Makefile to make lab1_exec using dlc_layer.c from current directory, 
#  and default object files from $(CLASSDIR)
#  Using this makefile will leave the files dlc_layer.o, libcomp.a and 
#  lab1_exec in the current directory

#Root of Directory Tree which contains reference sources/object files etc
  HOSTTYPE  = linux
  CLASSDIR	= /class/cis677/new_linux/Lab2/defaults
  OBJDIR	= $(CLASSDIR)/$(HOSTTYPE).obj

# Directory containing the simulator core sources.
  COMPSRCDIR	= $(CLASSDIR)/components.src
  SIMSRCDIR 	= $(CLASSDIR)/sim.src
  SIMLIBS	= -lsim -lcomp1 -lmem
# library for GUI
  XLIBDIR	= /usr/lib 
  TKLIBDIR	= /usr/local/tcl-tk-8.0.5/lib

  SIMINCLUDES	= -I$(SIMSRCDIR) -I$(COMPSRCDIR)  -I/usr/include -I/usr/local/tcl-tk-8.0.5/include

# the lab to be done
  STUDENTSRC	= dlc_layer.c
  STUDENTOBJ	= dlc_layer.o


# what to undefine to pull main out of libsim.a.  Will be _main for some
# operating systems.
  MAIN = main

# If using GCC:
  DEFINES	= -DMEMPOOL
  OFLAG		= -O -g
  CC		= gcc
  CXX		= g++

  CFLAGS	= $(OFLAG) $(DEFINES) $(SIMINCLUDES)
  LDFLAGS	= -L$(OBJDIR) -L$(TKLIBDIR) -L$(XLIBDIR) 
  LIBS		= $(SIMLIBS) $(TKLIBDIR)/libtcl8.0.so $(TKLIBDIR)/libtk8.0.so -lX11 -lm -lstdc++
  #LIBS		= $(SIMLIBS) /usr/local/tcl-tk-8.0.5/lib/libtcl8.0.so /usr/local/tcl-tk-8.0.5/lib/libtk8.0.so -lX11 -lm -lstdc++


.c.o:
	@rm -f $@
	@echo "	$(CC) $(OFLAG) $<"
	@$(CC) $(CFLAGS) -c $<


all: lab2_exec

# Make a simulator with only the default components:
lab2_exec: $(STUDENTOBJ)
	@echo "	$(CC) -o $@ $(STUDENTOBJ) -u $(MAIN) $(LIBS)"
	@$(CC) -o $@ $(STUDENTOBJ) -u $(MAIN) $(LDFLAGS) $(LIBS)
