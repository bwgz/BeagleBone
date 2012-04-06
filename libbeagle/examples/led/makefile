CXXFLAGS=-fPIC -I../../main/src
LDFLAGS=-L$(LIBDIR) -lbeagle
LIBDIR=../../main/lib

MKDIR=mkdir -p
RMDIR=rmdir

OBJS=led.o
LIBA=$(LIBDIR)/libbeagle.a
BINS=led

all: $(BINS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $+
     
led: led.o
	g++ $+ $(LIBA) -o led
# use this if you want a version using the shared library
#	$(CXX) $(LDFLAGS) -o $@ $+

clean:
	$(RM) $(OBJS) $(BINS)
	$(RMDIR) $(OBJDIR)
