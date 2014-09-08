include ../../Makefile.top

LOCAL_PART    := CSP
LOCAL_SRC_DIR := $(SRC_DIR)/$(LOCAL_PART)
LOCAL_INC_DIR := $(INC_DIR)/$(LOCAL_PART)

SEARCH_SRC := \
	Constraint.cpp \
	Domain.cpp \
	Relation.cpp \
	Scope.cpp \
	Value.cpp \
	Variable.cpp

SEARCH_HEADERS := \
	Constraint.h \
	Domain.h \
	Relation.h \
	Problem.h \
	Scope.h \
	Value.h \
	Variable.h

CXX_HEADERS := \
	${SEARCH_HEADERS:%.h=$(LOCAL_PART)/%.h}\
	ai_csp.h

CXX_SRC  := \
	$(SEARCH_SRC) 

TARGET_HEADERS    := ${CXX_HEADERS:%.h=$(AI_INC_DIR)/%.h}
TARGET_OBJS       := ${CXX_SRC:%.cpp=$(OBJ_BASE)/%.o}
TARGET_LIB        := $(AI_LIB_DIR)/libaicsp.a

include ../../Makefile.rules
include ../../Makefile.dep
