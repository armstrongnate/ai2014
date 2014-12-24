include ../../Makefile.top

PROJECT_LIST  := PL_Test PL_Shell PL_Dragons PL_Dragons_2012 PL_Wumpus

all install clean spotless:
	for d in $(PROJECT_LIST); do \
		$(MAKE) -f Makefile.$$d $@ ; \
	done

$(PROJECT_LIST):
	$(MAKE) -f Makefile.$@

include ../../Makefile.dep
