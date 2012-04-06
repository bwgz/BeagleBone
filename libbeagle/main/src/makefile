CXXFLAGS=-I.
OBJDIR=../obj
LIBDIR=../lib

MKDIR=mkdir -p
RMDIR=rmdir

OBJS=$(addprefix $(OBJDIR)/,ain.o gpio.o stepper.o)
LIB=$(LIBDIR)/libbeagle.a

all: $(LIB)

$(OBJDIR):
	$(MKDIR) $@

$(OBJDIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $+
     
$(OBJS): | $(OBJDIR)
     
$(LIBDIR):
	$(MKDIR) $@

$(LIB): $(OBJS)
	$(AR) $(ARFLAGS) $@ $+

$(LIB): | $(LIBDIR)

clean:
	$(RM) $(OBJS) $(LIB)
	$(RMDIR) $(OBJDIR) $(LIBDIR)



