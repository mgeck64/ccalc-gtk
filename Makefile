#
# Compiler flags
#
CCXX   = g++
CC     = gcc
CXXFLAGS = `pkg-config gtkmm-4.0 --cflags` -Wall -Werror -Wextra -std=gnu++20
CFLAGS   = -Wall -Werror -Wextra
GTKLIBS = `pkg-config gtkmm-4.0 --libs`

#
# Project files
#
CPPSRCS = $(wildcard *.cpp)
CSRCS = $(wildcard *.c)
OBJS = $(CPPSRCS:.cpp=.o) $(CSRCS:.c=.o)
EXE = gcalc

#
# Debug build settings
#
DBGDIR = debug
DBGEXE = $(DBGDIR)/$(EXE)
DBGOBJS = $(addprefix $(DBGDIR)/, $(OBJS))
DBGDEPS = $(DBGOBJS:%.o=%.d)
DBGFLAGS = -g -O0 -DDEBUG

#
# Release build settings
#
RELDIR = release
RELEXE = $(RELDIR)/$(EXE)
RELOBJS = $(addprefix $(RELDIR)/, $(OBJS))
RELDEPS = $(RELOBJS:%.o=%.d)
RELFLAGS = -Os -DNDEBUG

.PHONY: all clean debug release remake

# Default build
all: release

#
# Debug rules
#
debug: make_dbgdir $(DBGEXE)

$(DBGEXE): $(DBGOBJS)
		$(CCXX) -o $(DBGEXE) $^ -lccalc-dbg $(GTKLIBS)

-include $(DBGDEPS)

$(DBGDIR)/%.o: %.cpp
		$(CCXX) -c $(CXXFLAGS) $(DBGFLAGS) -MMD -o $@ $<

$(DBGDIR)/%.o: %.c
		$(CC) -c $(CFLAGS) $(DBGFLAGS) -MMD -o $@ $<

#
# Release rules
#
release: make_reldir $(RELEXE)

$(RELEXE): $(RELOBJS)
		$(CCXX) -o $(RELEXE) $^ -lccalc-rel $(GTKLIBS)

-include $(RELDEPS)

$(RELDIR)/%.o: %.cpp
		$(CCXX) -c $(CXXFLAGS) $(RELFLAGS) -MMD -o $@ $<

$(RELDIR)/%.o: %.c
		$(CC) -c $(CFLAGS) $(RELFLAGS) -MMD -o $@ $<

#
# Other rules
#
make_dbgdir:
		@mkdir -p $(DBGDIR)

make_reldir:
		@mkdir -p $(RELDIR)

remake: clean all


clean:
		@rm -r -f $(RELDIR) $(DBGDIR)

