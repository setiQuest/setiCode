LIB_DIR=../../../sonata_install/lib
BIN_DIR=../../../sonata_install/bin
DATA_DIR=../../../data
DOCS_DIR=../../../docs
PACKAGE=opensonata.dataDisplays
PACKAGE_DIR=$(LIB_DIR)/opensonata/dataDisplays
SRC_DIR=.
JVC = javac

JVCFLAGS = -sourcepath $(SRC_DIR) -d . -classpath $(LIB_DIR):$(LIB_DIR)/jtransforms-2.3.jar:$(LIB_DIR)/plot.jar

COMMON_SOURCES = EnvReader.java \
   ReadoutPlot.java \
   ReadoutListener.java

WATERFALLDISPLAY_SOURCES = WaterfallDisplay.java

BASELINEDISPLAY_SOURCES = BaselineDisplay.java

COMMON_CLASSES = $(patsubst %.java,$(PACKAGE_DIR)/%.class,$(COMMON_SOURCES))

WATERFALL_CLASSES = $(patsubst %.java,$(PACKAGE_DIR)/%.class,$(WATERFALLDISPLAY_SOURCES))

BASELINE_CLASSES = $(patsubst %.java,$(PACKAGE_DIR)/%.class,$(BASELINEDISPLAY_SOURCES))

all: waterfall baseline data docs

$(COMMON_CLASSES): $(COMMON_SOURCES)
	$(JVC) $(JVCFLAGS) -d $(LIB_DIR) $(COMMON_SOURCES)

waterfall:  extra_jars $(WATERFALL_CLASSES)

$(WATERFALL_CLASSES): $(COMMON_CLASSES) $(WATERFALLDISPLAY_SOURCES)
	$(JVC) $(JVCFLAGS) -d $(LIB_DIR) $(WATERFALLDISPLAY_SOURCES)
	cp waterfallDisplay-nonjar $(BIN_DIR)/waterfallDisplay

baseline:  extra_jars $(BASELINE_CLASSES)

$(BASELINE_CLASSES): $(COMMON_CLASSES) $(BASELINEDISPLAY_SOURCES) 
	$(JVC) $(JVCFLAGS) -d $(LIB_DIR) $(BASELINEDISPLAY_SOURCES)
	cp baselineDisplay-nonjar $(BIN_DIR)/baselineDisplay

dirs:
	mkdir -p $(BIN_DIR)
	mkdir -p $(DATA_DIR)
	mkdir -p $(LIB_DIR)
	mkdir -p $(LIB_DIR)/opensonata
	mkdir -p $(DOCS_DIR)/src
	mkdir -p $(DOCS_DIR)/src/sse-pkg
	mkdir -p $(DOCS_DIR)/src/sse-pkg/dataDisplays

extra_jars: dirs
	if test ! -s $(LIB_DIR)/plot.jar; \
    then \
      cd $(LIB_DIR); \
      wget http://tiny.cc/sonataDisplayJars; \
      tar -xvzf opensonataDisplayJars_2.1.tar.Z; \
      rm opensonataDisplayJars_2.1.tar.Z; \
    fi

docs: dirs
	doxygen

data: dirs
	if test ! -s $(DATA_DIR)/kepler-baseline.R.baseline; \
    then \
      cd $(DATA_DIR); \
      wget http://tiny.cc/sonataDisplaySampleData; \
      tar -xvzf opensonataBaselineCompampSampleData_2.1.tar.Z; \
      rm opensonataBaselineCompampSampleData_2.1.tar.Z; \
    fi

clean:
	rm -rf $(PACKAGE_DIR)
	rm -f $(DATA_DIR)/*.compamp
	rm -f $(DATA_DIR)/*.baseline
	rm -f $(LIB_DIR)/plot.jar
	rm -f $(LIB_DIR)/jtransforms-2.3.jar
	rm -f $(BIN_DIR)/waterfallDisplay
	rm -f $(BIN_DIR)/baselineDisplay
	rm -rf $(DOCS_DIR)/src/sse-pkg/dataDisplays


