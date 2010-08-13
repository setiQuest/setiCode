LIB_DIR=../../../lib
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

all: waterfall baseline

$(COMMON_CLASSES): $(COMMON_SOURCES)
	$(JVC) $(JVCFLAGS) -d $(LIB_DIR) $(COMMON_SOURCES)

waterfall:  $(WATERFALL_CLASSES)

$(WATERFALL_CLASSES): $(COMMON_CLASSES) $(WATERFALLDISPLAY_SOURCES)
	$(JVC) $(JVCFLAGS) -d $(LIB_DIR) $(WATERFALLDISPLAY_SOURCES)

baseline:  $(BASELINE_CLASSES)

$(BASELINE_CLASSES): $(COMMON_CLASSES) $(BASELINEDISPLAY_SOURCES) 
	$(JVC) $(JVCFLAGS) -d $(LIB_DIR) $(BASELINEDISPLAY_SOURCES)

clean:
	rm -f $(PACKAGE_DIR)/*


