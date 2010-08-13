all: dataDisplays sonataInfoDisplay

dataDisplays:
	cd docs; cp *.html ../../docs; cp *.png ../../docs;
	cd sse-pkg/dataDisplays; make; cp waterfallDisplay-nonjar ../../../sonata_install/bin; cp baselineDisplay-nonjar ../../../sonata_install/bin; doxygen;

sonataInfoDisplay:
	cd docs; cp *.html ../../docs; cp *.png ../../docs;
	cd sse-pkg/util/sonataInfoDisplay; make; doxygen;
	

clean:	
	cd sse-pkg/dataDisplays; make clean;
	cd sse-pkg/util/sonataInfoDisplay; make clean;
