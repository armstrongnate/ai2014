include ../../Makefile.top

LOCAL_PART    := LocalSearch
LOCAL_SRC_DIR := $(SRC_DIR)/$(LOCAL_PART)
LOCAL_INC_DIR := $(INC_DIR)/$(LOCAL_PART)

SEARCH_SRC := \
	State.cpp \
	Problem.cpp \
	Algorithm.cpp \
		HillClimbing.cpp \
		FirstChoice.cpp \
		SimulatedAnnealing.cpp

SEARCH_HEADERS := \
	State.h \
	Problem.h \
	Algorithm.h \
		HillClimbing.h \
		FirstChoice.h \
		SimulatedAnnealing.h

CXX_HEADERS := \
	${SEARCH_HEADERS:%.h=$(LOCAL_PART)/%.h}\
	ai_local_search.h

CXX_SRC  := \
	$(SEARCH_SRC) 

TARGET_HEADERS    := ${CXX_HEADERS:%.h=$(AI_INC_DIR)/%.h}
TARGET_OBJS       := ${CXX_SRC:%.cpp=$(OBJ_BASE)/%.o}
TARGET_LIB        := $(AI_LIB_DIR)/libailocalsearch.a

include ../../Makefile.rules
include ../../Makefile.dep
