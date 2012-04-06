CXXFLAGS=-fPIC -I../../main/src
LDFLAGS=-L$(LIBDIR) -lbeagle
OBJDIR=../obj
LIBDIR=../../main/lib

MKDIR=mkdir -p
RMDIR=rmdir

OBJS=$(addprefix $(OBJDIR)/,led.o)
LIB=$(LIBDIR)/libbeagle.a
BINS=led

all: $(BINS)

$(OBJDIR):
	$(MKDIR) $@

$(OBJDIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $+
     
$(OBJS): | $(OBJDIR)

led: $(OBJDIR)/led.o
	g++ $+ ../../main/lib/libbeagle.a -o led
	echo $(CXX) $(LDFLAGS) -o $@ $+

clean:
	$(RM) $(OBJS) $(BINS)
	$(RMDIR) $(OBJDIR)
