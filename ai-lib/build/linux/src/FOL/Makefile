include ../../Makefile.top

LOCAL_PART    := FOL
LOCAL_SRC_DIR := $(SRC_DIR)/$(LOCAL_PART)
LOCAL_INC_DIR := $(INC_DIR)/$(LOCAL_PART)

PL_SRC := \
	Symbol.cpp \
	Sentence.cpp \
	KnowledgeBase.cpp \
	Parser.cpp

PL_HEADERS := \
	Symbol.h \
	Sentence.h \
	KnowledgeBase.h \
	Parser.h

CXX_HEADERS := \
	${PL_HEADERS:%.h=$(LOCAL_PART)/%.h}\
	ai_fol.h

CXX_SRC  := \
	$(PL_SRC) 

TARGET_HEADERS    := ${CXX_HEADERS:%.h=$(AI_INC_DIR)/%.h}
TARGET_OBJS       := ${CXX_SRC:%.cpp=$(OBJ_BASE)/%.o}
TARGET_LIB        := $(AI_LIB_DIR)/libaifol.a

include ../../Makefile.rules
include ../../Makefile.dep
