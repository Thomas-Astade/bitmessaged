
# installation path
prefix	?= ~

# include path
INCLUDE	:= -I../manual -I../auto

TARGET ?= bitmessaged

# compiler settings
CXXFLAGS:= $(INCLUDE) -Wall
LDFLAGS	:= -lpthread

ifdef DEBUG
CXXFLAGS+= -g -o0
else
LDFLAGS	+= -Wl,-s -o2
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

run:	build
	./$(TARGET) -i 127.0.0.1:8444

doxygen:
	doxygen

jenkins: build doxygen

$(TARGET):	.depend $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

.depend:	Makefile $(SOURCES) $(HEADERS)
	$(CXX) -MM $(CPPFLAGS) $(CXXFLAGS) $(SOURCES) >$@

-include .depend
