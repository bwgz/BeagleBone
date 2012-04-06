CXXFLAGS=-fPIC -I.
ARFLAGS=rcs
OBJDIR=../obj
LIBDIR=../lib

MKDIR=mkdir -p
RMDIR=rmdir

LIBA=$(LIBDIR)/libbeagle.a
LIBSO=$(LIBDIR)/libbeagle.so

OBJS=$(addprefix $(OBJDIR)/,ain.o gpio.o stepper.o)
LIBS=$(LIBA) $(LIBSO)

all: $(LIBS)

$(OBJDIR):
	$(MKDIR) $@

$(OBJDIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $+
     
$(OBJS): | $(OBJDIR)
     
$(LIBDIR):
	$(MKDIR) $@

$(LIBS): | $(LIBDIR)

$(LIBSO): $(OBJS) 
	$(CXX) -shared -o $@ $+

$(LIBA): $(OBJS) 
	$(AR) $(ARFLAGS) $@ $+

$(LIB): | $(LIBDIR)

clean:
	$(RM) $(OBJS) $(LIBS)
	$(RMDIR) $(OBJDIR) $(LIBDIR)



