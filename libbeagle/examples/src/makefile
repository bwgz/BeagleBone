CXXFLAGS=-fPIC -I../../main/src
LDFLAGS=-L$(LIBDIR) -lbeagle
OBJDIR=../obj
LIBDIR=../../main/lib

MKDIR=mkdir -p
RMDIR=rmdir

OBJS=$(addprefix $(OBJDIR)/,led.o)
LIBA=$(LIBDIR)/libbeagle.a
BINS=led

all: $(BINS)

$(OBJDIR):
	$(MKDIR) $@

$(OBJDIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $+
     
$(OBJS): | $(OBJDIR)

led: $(OBJDIR)/led.o
	g++ $+ $(LIBA) -o led
# use this if you want a version using the shared library
#	$(CXX) $(LDFLAGS) -o $@ $+

clean:
	$(RM) $(OBJS) $(BINS)
	$(RMDIR) $(OBJDIR)
