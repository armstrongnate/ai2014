include ../Makefile.top

UBUNTU_PACKAGES := libglu1-mesa-dev mesa-common-dev libxext-dev g++ libxxf86vm-dev libxi-dev libboost-serialization-dev freeglut3-dev
UBUNTU_PACKAGE_COUNT := 8

#FREEGLUT_BASE  := freeglut-2.2.0
#FREEGLUT_BASE  := freeglut-2.4.0
FREEGLUT_BASE  := freeglut-2.6.0
FREEGLUT_LIB_FILES := \
	$(AI_LIB_DIR)/libfreeglut.a \
	$(AI_LIB_DIR)/libfreeglut.la \
	$(AI_LIB_DIR)/libfreeglut.so
FREEGLUT_INC_FILES := \
	$(AI_INC_DIR)/GL/freeglut.h \
	$(AI_INC_DIR)/GL/freeglut_ext.h \
	$(AI_INC_DIR)/GL/freeglut_std.h
FREEGLUT_FILES := \
	$(FREEGLUT_LIB_FILES) \
	$(FREEGLUT_INC_FILES)

BOOST_BASE  := boost_1_44_0
BOOST_LIB_FILES := \
	$(AI_LIB_DIR)/libboost_serialization-mt.a \
	$(AI_LIB_DIR)/libboost_serialization-mt.so \
	$(AI_LIB_DIR)/libboost_wserialization-mt.a \
	$(AI_LIB_DIR)/libboost_wserialization-mt.so
BOOST_INC_FILES := \
	$(AI_INC_DIR)/boost/
BOOST_FILES := \
	$(BOOST_LIB_FILES) \
	$(BOOST_INC_FILES)

SPARSEHASH_BASE  := sparsehash-1.11
SPARSEHASH_LIB_FILES :=
SPARSEHASH_INC_FILES := \
	$(AI_INC_DIR)/google/sparse_hash_map \
	$(AI_INC_DIR)/google/dense_hash_map
SPARSEHASH_FILES := \
	$(SPARSEHASH_LIB_FILES) \
	$(SPARSEHASH_INC_FILES)

all install: sparsehash 

freeglut: $(FREEGLUT_FILES)
boost: $(BOOST_FILES)
sparsehash: $(SPARSEHASH_FILES)

$(FREEGLUT_FILES): $(THIRD_DIR)/$(FREEGLUT_BASE).tar.gz
	x=`dpkg --list $(UBUNTU_PACKAGES) | egrep ^ii | wc -l`; if [ "$$x" != "$(UBUNTU_PACKAGE_COUNT)" ]; then echo "*** You must: apt-get install $(UBUNTU_PACKAGES)"; fi; \
	[ "$$x" = "$(UBUNTU_PACKAGE_COUNT)" ] && \
	(tar zxf $(THIRD_DIR)/$(FREEGLUT_BASE).tar.gz; \
	cd $(FREEGLUT_BASE); \
	CC=$(CC) CXX=$(CXX) LDFLAGS=-L/usr/X11R6/lib ./configure --prefix=$(AI_PREFIX_DIR) --libdir=$(AI_LIB_DIR) --disable-replace-glut; \
	make; \
	make install; \
	make clean; \
	cd ..; \
	rm -rf $(FREEGLUT_BASE))

#$(BOOST_FILES): $(THIRD_DIR)/$(BOOST_BASE).tar.gz
#	x=`dpkg --list $(UBUNTU_PACKAGES) | egrep ^ii | wc -l`; if [ "$$x" != "$(UBUNTU_PACKAGE_COUNT)" ]; then echo "*** You must: apt-get install $(UBUNTU_PACKAGES)"; fi; \
#	[ "$$x" = "$(UBUNTU_PACKAGE_COUNT)" ] && \
#	(tar zxf $(THIRD_DIR)/$(BOOST_BASE).tar.gz; \
#	cd $(BOOST_BASE); \
#	CC=$(CC) CXX=$(CXX) ./configure --prefix=$(AI_PREFIX_DIR) --includedir=$(AI_INC_DIR) --libdir=$(AI_LIB_DIR); \
#	make install; \
#	make clean; \
#	cd ..; \
#	rm -rf $(BOOST_BASE))

$(BOOST_FILES): $(THIRD_DIR)/$(BOOST_BASE).tar.bz2
	x=`dpkg --list $(UBUNTU_PACKAGES) | egrep ^ii | wc -l`; if [ "$$x" != "$(UBUNTU_PACKAGE_COUNT)" ]; then echo "*** You must: apt-get install $(UBUNTU_PACKAGES)"; fi; \
	[ "$$x" = "$(UBUNTU_PACKAGE_COUNT)" ] && \
	(tar jxf $(THIRD_DIR)/$(BOOST_BASE).tar.bz2; \
	cd $(BOOST_BASE); \
	echo 'bootstrap of boost'; \
	CC=$(CC) CXX=$(CXX) ./bootstrap.sh --prefix=$(AI_PREFIX_DIR) --includedir=$(AI_INC_DIR) --libdir=$(AI_LIB_DIR) --with-libraries='serialization'; \
	echo 'bjam boost'; \
	CC=$(CC) CXX=$(CXX) ./bjam --build-type=complete --layout=tagged install; \
	cd ..; \
	rm -rf $(BOOST_BASE))


$(SPARSEHASH_FILES): $(THIRD_DIR)/$(SPARSEHASH_BASE).tar.gz
	(tar zxf $(THIRD_DIR)/$(SPARSEHASH_BASE).tar.gz; \
	cd $(SPARSEHASH_BASE); \
	CC=$(CC) CXX=$(CXX) ./configure --prefix=$(AI_PREFIX_DIR) --libdir=$(AI_LIB_DIR) ; \
	make; \
	make install; \
	make clean; \
	cd ..; \
	rm -rf $(SPARSEHASH_BASE))

clean:
	-rm -rf $(FREEGLUT_BASE) $(BOOST_BASE) $(SPARSEHASH_BASE)

spotless: clean
	-rm -rf $(FREEGLUT_LIB_FILES) $(AI_LIB_DIR)/libfreeglut.so.* $(BOOST_FILES) $(SPARSEHASH_FILES)
	-rm -f $(AI_LIB_DIR)/libboost*.a*
	-rm -f $(AI_LIB_DIR)/libboost*.so*

include ../Makefile.dep
