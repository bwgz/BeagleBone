CXXFLAGS=-fPIC -I../../main/src
LDFLAGS=-L$(LIBDIR) -lbeagle -lpthread
LIBDIR=../../main/lib

MKDIR=mkdir -p
RMDIR=rmdir

OBJS=rotary.o
LIBA=$(LIBDIR)/libbeagle.a
BINS=rotary

all: $(BINS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $+
     
rotary: rotary.o
	g++ -lpthread $+ $(LIBA) -o rotary
# use this if you want a version using the shared library
#	$(CXX) $(LDFLAGS) -o $@ $+

clean:
	$(RM) $(OBJS) $(BINS)
	$(RMDIR) $(OBJDIR)
