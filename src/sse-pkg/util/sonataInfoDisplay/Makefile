BUILD_BIN      = ../../../../bin

EXTRA_OBJS =

CXX=g++ -g
CXXFLAGS=-Wall -W -O2 -D_NO_PROTO -D_REENTRANT


SOURCES=main.cpp details.cpp utils.cpp screen.cpp components.cpp
OBJECTS1=$(SOURCES:.cpp=.o)
OBJECTS=$(OBJECTS1:.c=.o)
EXECUTABLE=sonataInfoDisplay
LIBS = -lnsl  -L/usr/lib -lm -lz -lpthread -lrt -lncurses

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS) $(EXTRA_OBJS) $(LIBS)
	mv $(EXECUTABLE) ../../../../sonata_install/bin

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
	rm -f ../../../../sonata_install/bin/$(EXECUTABLE)
	rm -rf html

.cpp.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<

