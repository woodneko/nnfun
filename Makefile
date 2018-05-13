
VPATH=./src/nntrain:./src/common
OBJDIR=./obj/
BINDIR=./bin

CC=gcc
NVCC=nvcc 
AR=ar
ARFLAGS=rcs
OPTS=-Ofast
LDFLAGS= -lm -pthread 
COMMON= -Isrc/include/ -Isrc/
CFLAGS= -Wall -Wno-unused-result -Wno-unknown-pragmas -Wfatal-errors -fPIC

NN_COMMON_SRC+=$(wildcard src/common/*.c)
NN_TRAIN_SRC+=$(wildcard src/nntrain/*.c)
NN_RUN_SRC+=$(wildcard src/nnrun/*.c)

NN_TRAIN_OBJ+=$(addprefix $(OBJDIR), $(addsuffix .o,$(basename $(notdir $(NN_TRAIN_SRC)))))
NN_COMMON_OBJ+=$(addprefix $(OBJDIR), $(addsuffix .o,$(basename $(notdir $(NN_COMMON_SRC)))))

NN_TRAIN_DEPS = $(addprefix $(OBJDIR), $(addsuffix .d,$(basename $(notdir $(NN_COMMON_SRC) $(NN_TRAIN_SRC)))))

include $(NN_TRAIN_OBJ:.o=.d)
include $(NN_COMMON_OBJ:.o=.d)

all: obj exec

exec: bin nnfun-train 

nnfun-train:$(NN_TRAIN_OBJ) $(NN_COMMON_OBJ)
	$(CC) $(COMMON) $(CFLAGS) $^ -o $(BINDIR)/$@ 

$(OBJDIR)%.o: %.c 
	$(CC) $(COMMON) $(CFLAGS) -c $< -o $@
	$(CC) -MT $(addsuffix .o,$(basename $@)) -MMD -MP -MF $(OBJDIR)$*.d $(COMMON) -c $<

bin:
	mkdir -p bin
obj:
	mkdir -p obj

#obj/%.o: src/nntrain/%.c
#	@echo $@ $^ 

test:
	@echo objs: $(NN_TRAIN_OBJ) $(NN_COMMON_OBJ)
	@echo srcs: $(NN_TRAIN_SRC)
	@echo dep: $(wildcard $(OBJDIR)*.d)

.PHONY: clean

clean:
	rm -rf $(BINDIR)/* $(OBJDIR)*

