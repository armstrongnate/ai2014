include ../../Makefile.top

LOCAL_PART    := Search
LOCAL_SRC_DIR := $(SRC_DIR)/$(LOCAL_PART)
LOCAL_INC_DIR := $(INC_DIR)/$(LOCAL_PART)

SEARCH_SRC := \
	Action.cpp \
	State.cpp \
	ActionStatePair.cpp \
	Node.cpp \
	Problem.cpp \
	Frontier.cpp \
		Fringe.cpp \
			BFFringe.cpp \
			UCFringe.cpp \
			DFFringe.cpp \
			DLFringe.cpp \
			GreedyFringe.cpp \
			AStarFringe.cpp \
	Solution.cpp \
	Algorithm.cpp \
		Tree.cpp \
		Graph.cpp \
			ClosedList.cpp

SEARCH_HEADERS := \
	Action.h \
	State.h \
	ActionStatePair.h \
	Node.h \
	Problem.h \
	Frontier.h \
		Fringe.h \
			BFFringe.h \
			UCFringe.h \
			DFFringe.h \
			DLFringe.h \
			GreedyFringe.h \
			AStarFringe.h \
	Solution.h \
	Algorithm.h \
		Tree.h \
		Graph.h \
			ClosedList.h


CXX_HEADERS := \
	${SEARCH_HEADERS:%.h=$(LOCAL_PART)/%.h}\
	ai_search.h

CXX_SRC  := \
	$(SEARCH_SRC) 

TARGET_HEADERS    := ${CXX_HEADERS:%.h=$(AI_INC_DIR)/%.h}
TARGET_OBJS       := ${CXX_SRC:%.cpp=$(OBJ_BASE)/%.o}
TARGET_LIB        := $(AI_LIB_DIR)/libaisearch.a

include ../../Makefile.rules
include ../../Makefile.dep
