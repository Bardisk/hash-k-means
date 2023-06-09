WORK_DIR = $(shell pwd)
BUILD_DIR = $(WORK_DIR)/build

$(shell mkdir -p $(BUILD_DIR))

INC_PATH = include
INC_FLAG = $(addprefix -I, $(INC_PATH))

COMMON_FLAGS = $(INC_FLAG) -Wall -O2
CFLAGS = $(COMMON_FLAGS)
CXXFLAGS = $(COMMON_FLAGS)

ifdef DB
	COMMON_FLAGS += -DDB
endif

SRCS = $(shell find -name *.cpp) $(shell find -name *.c)
OBJS = $(subst ./, $(BUILD_DIR)/, $(addsuffix .o, $(basename $(SRCS))))

CC = gcc
CXX = g++
LD = ld
AS = as

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@) && echo + $(CC) $<
	@$(CC) -std=gnu11 $(CFLAGS) -c -o $@ $(realpath $<)

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@) && echo + $(CXX) $<
	@$(CXX) -std=c++17 $(CXXFLAGS) -c -o $@ $(realpath $<)

# test:
# 	@echo $(OBJS)
# 	@echo $(SRCS)

$(BUILD_DIR)/hash-k-means: $(OBJS)
	@$(CXX) -o $(BUILD_DIR)/hash-k-means $(OBJS)

run: $(BUILD_DIR)/hash-k-means
	@$(BUILD_DIR)/hash-k-means -t 5 -c 4096 <hashlist.txt >ans.txt

clean:
	-@rm -r build
