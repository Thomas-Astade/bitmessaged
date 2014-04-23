
# installation path
prefix	?= ~

# include path
INCLUDE	:= -I../manual -I../auto

TARGET ?= bitmessaged

# compiler settings
CXXFLAGS:= $(INCLUDE) -Wall
LDFLAGS	:= -lpthread -ldl -Wl,--export-dynamic

ifdef DEBUG
CXXFLAGS+= -g
else
LDFLAGS	+= -Wl,-s
endif

# find sources and headers
SOURCES	:= $(wildcard ../auto/*.c ../auto/*.cpp ../manual/*.cpp)
HEADERS	:= $(wildcard ../auto/*.h ../manual/*.h)

# objects go into current directory
OBJSTMP	:= $(notdir $(SOURCES:.cpp=.o))
OBJS	:= $(notdir $(OBJSTMP:.c=.o))

%.o:	../auto/%.c
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

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
	./$(TARGET) -p ../../Component_debug_plugin/Config_Linux/debug_plugin -p ../../Component_example_plugin/Config_Linux/example_plugin

doxygen:
	doxygen

jenkins: build doxygen

$(TARGET):	.depend $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

.depend:	Makefile $(SOURCES) $(HEADERS)
	$(CXX) -MM $(CPPFLAGS) $(CXXFLAGS) $(SOURCES) >$@

-include .depend
