include ../Makefile.top

PROJECT_LIST  := Agent Search LocalSearch PL FOL CSP

all install clean spotless:
	for d in $(PROJECT_LIST); do \
		(cd $$d; $(MAKE) $@) \
	done

include ../Makefile.dep
