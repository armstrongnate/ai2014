include Makefile.top

all: configure progs

progs:
	(cd prog; $(MAKE) install)

configure:
	@echo configuring the location of your directory tree
	@(x=`pwd`; x=`dirname $$x`; x=`dirname $$x`; \
	 sed 's?^PREFIX_DIR *:=.*$$?PREFIX_DIR := '$$x'?' Makefile.top > Makefile.top.tmp; \
	 mv Makefile.top.tmp Makefile.top)
	@(x=`pwd`; x=`dirname $$x`; x=`dirname $$x`; x=`dirname $$x`; \
	 sed 's?^AI_PREFIX_DIR *:=.*$$?AI_PREFIX_DIR := '$$x'/ai?' Makefile.top > Makefile.top.tmp; \
	 mv Makefile.top.tmp Makefile.top)
	@echo checking your installed development packages
	@(x=`dpkg --list $(UBUNTU_PACKAGES) | egrep ^ii | wc -l`; if [ "$$x" != "$(UBUNTU_PACKAGE_COUNT)" ]; then echo "*** You must: apt-get install $(UBUNTU_PACKAGES)"; fi)


PROJECT_LIST  := prog

clean spotless:
	for d in $(PROJECT_LIST); do \
		(cd $$d; $(MAKE) $@) \
	done

include Makefile.dep
