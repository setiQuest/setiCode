SONATADIR ?= undefined

all: dataDisplays sonataInfoDisplay

dataDisplays:
	cd sse-pkg/dataDisplays; make;

sonataInfoDisplay:
	cd sse-pkg/util/sonataInfoDisplay; make;

clean:	
	cd sse-pkg/dataDisplays; make clean;
	cd sse-pkg/util/sonataInfoDisplay; make clean;

install: all
ifeq "$(SONATADIR)" "undefined"
	@echo ""
	@echo "INSTALL FAILURE"
	@echo "You need to define the environment variable SONATADIR"
	@echo "which points to the OpenSonATA binary release directory"
	@echo "where the sonata_install and sonata_archive directories"
	@echo "reside. Please set this variable in your environment"
	@echo "and try again."
	@echo ""
else
	cp -rv ../sonata_install/bin/* $(SONATADIR)/sonata_install/bin/
	cp -rv ../sonata_install/lib/* $(SONATADIR)/sonata_install/lib 
	cp -rv ../data/* $(SONATADIR)/data
	@echo ""
	@echo "INSTALL COMPLETE"
	@echo ""
endif
