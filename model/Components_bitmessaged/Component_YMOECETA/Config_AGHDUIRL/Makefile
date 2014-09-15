
# installation path
prefix	?= ~

# include path
INCLUDE	:= -I../manual -I../auto -Iopenssl-1.0.1c_static_w32_mingw/include

TARGET ?= genPOW

CXX = i586-mingw32msvc-g++

# compiler settings
CXXFLAGS:= $(INCLUDE) -Wall -O3 -std=c++0x 
LDFLAGS	:= -Lopenssl-1.0.1c_static_w32_mingw -lssl -lcrypto

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

build:	$(TARGET).exe

install:	build
	install -s $(TARGET) $(prefix)/bin

clean:
	rm -f $(TARGET) *.o .depend

rebuild:	clean build

run:	build
	wine ./$(TARGET).exe -r MAIN_12 -m qwertz

$(TARGET).exe:	.depend $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

.depend:	Makefile $(SOURCES) $(HEADERS)
	$(CXX) -MM $(CPPFLAGS) $(CXXFLAGS) $(SOURCES) >$@

-include .depend
