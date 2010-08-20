BUILD_BIN      = ../../../../bin
DATA_DIR      = ../../../../data
DOC_DIR       = ../../../../docs

EXTRA_OBJS =

CXX=g++ -g
CXXFLAGS=-Wall -W -O2 -D_NO_PROTO -D_REENTRANT


SOURCES=main.cpp details.cpp utils.cpp screen.cpp components.cpp
OBJECTS1=$(SOURCES:.cpp=.o)
OBJECTS=$(OBJECTS1:.c=.o)
EXECUTABLE=sonataInfoDisplay
LIBS = -lnsl  -L/usr/lib -lm -lz -lpthread -lrt -lncurses

all: $(SOURCES) $(EXECUTABLE) data docs

$(BUILD_BIN)/$(EXECUTABLE): $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CXX) -o $@ $(OBJECTS) $(EXTRA_OBJS) $(LIBS)
	mv $(EXECUTABLE) $(BUILD_BIN)
	cp ./displayDemo $(BUILD_BIN)

dirs:
	mkdir -p $(DOC_DIR)
	mkdir -p $(DOC_DIR)/src
	mkdir -p $(DOC_DIR)/src/sse-pkg
	mkdir -p $(DOC_DIR)/src/sse-pkg/util
	mkdir -p $(DOC_DIR)/src/sse-pkg/util/sonataInfoDisplay

data:
	if test ! -s $(DATA_DIR)/sse-system-status.txt; \
    then \
      cd $(DATA_DIR); \
      wget http://tiny.cc/sonataSampleStatusLog; \
      tar -xvzf sse-system-status.txt.tar.Z; \
      rm sse-system-status.txt.tar.Z; \
    fi

docs: dirs
	doxygen

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
	rm -f $(BUILD_BIN)/$(EXECUTABLE)
	rm -f $(BUILD_BIN)/displayDemo
	rm -f $(DATA_DIR)/sse-system-status.txt
	rm -rf $(DOC_DIR)/src/sse-pkg/util/sonataInfoDisplay

.cpp.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<

