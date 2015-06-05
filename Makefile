#!/usr/bin/make -f
###############################################################################
# Makefile for Project Euler Solver Program                                   #
#                                                                             #
# Builds the Project Euler problem solver from source                         #
###############################################################################

###############################################################################
#                                    VARS                                     #
###############################################################################
CC := gcc
LD := gcc

CFLAGS += -Wall -std=gnu99
LDFLAGS += -Wall

PROJECT := euler

NO_DEPS_TARGETS += clean directories
###############################################################################
#                                 BUILD DIRS                                  #
###############################################################################
BUILD_DIR := obj
EXE_DIR   := bin

SRC_TREE += src

INC_DIRS += src/inc src/problems/inc src/common/inc
SRC_DIRS += src src/problems src/common
###############################################################################
#                                 BUILD FILES                                 #
###############################################################################
MAKE_TESTS := tests/MakeTests.include

C_PATHS   += $(foreach dir, $(SRC_DIRS),$(wildcard $(dir)/*.c))

C_FILES   += $(foreach f, $(C_PATHS),$(notdir $(f)))
OBJ_FILES += $(foreach f,$(C_FILES),$(BUILD_DIR)/$(patsubst %.c,%.o,$(f)))
DEP_FILES += $(foreach f,$(C_FILES),$(BUILD_DIR)/$(patsubst %.c,%.d,$(f)))

LIBS = -lrt -lm

BINARY := $(EXE_DIR)/$(PROJECT)

INCLUDES += $(foreach f,$(INC_DIRS),-I$(f))

CFLAGS += $(INCLUDES)

vpath %.c $(SRC_DIRS)

C_DIRS += $(SRC_DIRS) $(INC_DIRS)

CLEAN_FILES += $(foreach dir,$(C_DIRS),$(wildcard $(dir)/*~))
CLEAN_FILES += $(foreach dir,$(C_DIRS),$(wildcard $(dir)/*\#))
CLEAN_FILES += $(wildcard Makefile~)
CLEAN_FILES += $(wildcard $(BUILD_DIR)/*) $(wildcard $(EXE_DIR)/*)
###############################################################################
#                                   TARGETS                                   #
###############################################################################
all: optomized

include $(MAKE_TESTS)

debug: CFLAGS += -DDEBUG=1 -g
debug: $(BINARY)

optomized: CFLAGS += -DNDEBUG=1 -march=native -Os -flto
optomized: LDFLAGS += -march=native -Os -flto
optomized: $(BINARY)

directories: $(BUILD_DIR)/.dir_dummy $(EXE_DIR)/.dir_dummy

%.dir_dummy:
	mkdir -p $(dir $(@))
	@touch $(@)

$(BUILD_DIR)/%.d: %.c
	$(CC) $(CFLAGS) -MF $@ -M -MT "$(patsubst %.d,%.o,$@) $@" $<

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)/.dir_dummy
	$(CC) $(CFLAGS) -c $< -o $@

$(BINARY): $(OBJ_FILES) | $(EXE_DIR)/.dir_dummy
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@

clean:
	rm -f $(CLEAN_FILES)

ifeq (,$(filter $(MAKECMDGOALS), $(NO_DEPS_TARGETS)))

#next two conditonals prevent make from running on dry run or when
#invoked for tab-completion
ifneq (n,$(findstring n,$(firstword $(MAKEFLAGS))))
ifneq (p,$(findstring p,$(firstword $(MAKEFLAGS))))
-include $(DEP_FILES)
endif
endif


endif
