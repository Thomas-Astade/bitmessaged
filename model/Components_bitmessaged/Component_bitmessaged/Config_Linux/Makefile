
# installation path
prefix	?= ~

# include path
INCLUDE	:= -I../manual -I../auto 

TARGET ?= bitmessaged

# compiler settings
CXXFLAGS:= $(INCLUDE) -Wall
LDFLAGS	:= -ljson_spirit -lpthread -ldl -lssl -lcrypto -Wl,--export-dynamic

TRACE_LIST :=$(addsuffix .o,$(TRACECLASSES))

DEBUG=1

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
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(if $(findstring $(notdir $@),$(TRACE_LIST)),-D_TRACE_ -include Trace2UML.h,) -c -o $@ $<

%.o:	../auto/%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(if $(findstring $(notdir $@),$(TRACE_LIST)),-D_TRACE_ -include Trace2UML.h,) -c -o $@ $<

%.o:	../manual/%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(if $(findstring $(notdir $@),$(TRACE_LIST)),-D_TRACE_ -include Trace2UML.h,) -c -o $@ $<

build:	$(TARGET)

install:	build
	install -s $(TARGET) $(prefix)/bin

clean:
	rm -f $(TARGET) *.o .depend

rebuild:	clean build

run:	build
	./$(TARGET) -d -i 127.0.0.1:8444

doxygen:
	doxygen

jenkins: build doxygen

$(TARGET):	.depend $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

.depend:	Makefile $(SOURCES) $(HEADERS)
	$(CXX) -MM $(CPPFLAGS) $(CXXFLAGS) $(SOURCES) >$@

-include .depend
