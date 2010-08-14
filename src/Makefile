all: dataDisplays sonataInfoDisplay

dataDisplays:
	cd sse-pkg/dataDisplays; make; cp waterfallDisplay-nonjar ../../../sonata_install/bin; cp baselineDisplay-nonjar ../../../sonata_install/bin; doxygen;

sonataInfoDisplay:
	cd sse-pkg/util/sonataInfoDisplay; make; doxygen;
	

clean:	
	cd sse-pkg/dataDisplays; make clean;
	cd sse-pkg/util/sonataInfoDisplay; make clean;
