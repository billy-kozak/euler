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

CFLAGS += -Wall -std=c99
LDFLAGS += -Wall

PROJECT := euler
###############################################################################
#                                 BUILD DIRS                                  #
###############################################################################
BUILD_DIR := obj
EXE_DIR   := bin

INC_DIRS += src/inc
SRC_DIRS += src
###############################################################################
#                                 BUILD FILES                                 #
###############################################################################
C_PATHS   += $(foreach dir, $(SRC_DIRS),$(wildcard $(dir)/*.c))

C_FILES   += $(foreach f, $(C_PATHS),$(notdir $(f)))
OBJ_FILES += $(foreach f,$(C_FILES),$(BUILD_DIR)/$(patsubst %.c,%.o,$(f)))
DEP_FILES += $(foreach f,$(C_FILES),$(BUILD_DIR)/$(patsubst %.c,%.d,$(f)))

BINARY := $(EXE_DIR)/$(PROJECT)

INCLUDES += $(foreach f,$(INC_DIRS),-I$(f))

CFLAGS += $(INCLUDES)

vpath %.c $(SRC_DIRS)
###############################################################################
#                                   TARGETS                                   #
###############################################################################
all: optomized

debug: CFLAGS += -DDEBUG=1
debug: $(BINARY)

optomized: CFLAGS += -march=native -Os -flto
optomized: LDFLAGS += -march=native -Os -flto
optomized: $(BINARY)

directories: $(BUILD_DIR)/.dir_dummy $(EXE_DIR)/.dir_dummy

%.dir_dummy:
	mkdir -p $(dir $(@))
	@touch $(@)
	
$(BUILD_DIR)/%.d: %.c
	$(CC) $(CFLAGS) -M -MT "$(patsubst %.d,%.o,$@) $@" $< > $@
	
$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)/.dir_dummy
	$(CC) $(CFLAGS) -c $< -o $@

$(BINARY): $(OBJ_FILES) | $(EXE_DIR)/.dir_dummy
	$(LD) $(LDFLAGS) $^ -o $@

clean: C_DIRS = $(SRC_DIRS) $(INC_DIRS)                     
clean: CORE_FILES += $(foreach dir,$(C_DIRS),$(wildcard $(dir)/*~))
clean: CORE_FILES += $(foreach dir,$(C_DIRS),$(wildcard $(dir)/*#))
clean:
	rm -f $(BUILD_DIR)/* $(EXE_DIR)/* $(CORE_FILES)
	
-include $(DEP_FILES)
