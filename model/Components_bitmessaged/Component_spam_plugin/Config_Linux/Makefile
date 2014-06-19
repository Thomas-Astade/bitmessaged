
# installation path
prefix	?= ~

# include path
INCLUDE	:= -I../manual -I../auto -I../../Component_bitmessaged/auto

TARGET ?= spam_plugin

# compiler settings
CXXFLAGS:= $(INCLUDE) -Wall -fPIC
LDFLAGS	:=

ifdef DEBUG
CXXFLAGS+= -g
else
LDFLAGS	+= -Wl,-s
endif

# find sources and headers
SOURCES	:= $(wildcard ../auto/*.cpp ../manual/*.cpp)
HEADERS	:= $(wildcard ../auto/*.h ../manual/*.h)

# objects go into current directory
OBJS	:= $(notdir $(SOURCES:.cpp=.o))

%.o:	../auto/%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

%.o:	../manual/%.cpp
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
