include Makefile.top

all: configure thirds libs

thirds:
	(cd third; $(MAKE) install)
libs:
	(cd src; $(MAKE) install)

configure:
	(x=`pwd`; x=`dirname $$x`; x=`dirname $$x`; \
	 sed 's?^PREFIX_DIR *:=.*$$?PREFIX_DIR := '$$x'?' Makefile.top > Makefile.top.tmp; \
	 mv Makefile.top.tmp Makefile.top)
	(x=`pwd`; x=`dirname $$x`; x=`dirname $$x`; x=`dirname $$x`; \
	 sed 's?^AI_PREFIX_DIR *:=.*$$?AI_PREFIX_DIR := '$$x'/ai?' Makefile.top > Makefile.top.tmp; \
	 mv Makefile.top.tmp Makefile.top)

PROJECT_LIST  := src third

clean spotless:
	for d in $(PROJECT_LIST); do \
		(cd $$d; $(MAKE) $@) \
	done

include Makefile.dep
