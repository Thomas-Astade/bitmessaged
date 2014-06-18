
# installation path
prefix	?= ~

# include path
INCLUDE	:= -I../manual -I../auto -I../../Component_bitmessaged/auto

TARGET ?= mongoose_plugin

# compiler settings
CXXFLAGS:= $(INCLUDE) -Wall -fPIC
LDFLAGS	:= 

ifdef DEBUG
CXXFLAGS+= -g
else
LDFLAGS	+= -Wl,-s
endif

# find sources and headers
SOURCES	:= $(wildcard ../auto/*.cpp ../manual/*.cpp ../manual/*.c)
HEADERS	:= $(wildcard ../auto/*.h ../manual/*.h)

# objects go into current directory
OBJSTMP	:= $(notdir $(SOURCES:.cpp=.o))
OBJS	:= $(notdir $(OBJSTMP:.c=.o))

%.o:	../manual/%.c
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(if $(findstring $(notdir $@),$(TRACE_LIST)),-D_TRACE_ -include Trace2UML.h,) -c -o $@ $<

%.o:	../auto/%.c
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(if $(findstring $(notdir $@),$(TRACE_LIST)),-D_TRACE_ -include Trace2UML.h,) -c -o $@ $<

%.o:	../auto/%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

%.o:	../manual/%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

%.o:	../manual/%.c
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

build:	$(TARGET)

install:	build
	install -s $(TARGET) $(prefix)/bin

clean:
	rm -f $(TARGET) *.o .depend

rebuild:	clean build

$(TARGET):	.depend $(OBJS)
	$(CXX) -shared -o $@ $(OBJS) $(LDFLAGS)

.depend:	Makefile $(SOURCES) $(HEADERS)
	$(CXX) -MM $(CPPFLAGS) $(CXXFLAGS) $(SOURCES) >$@

-include .depend
