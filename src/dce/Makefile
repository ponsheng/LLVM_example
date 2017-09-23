SHELL = /bin/bash
PWD = `pwd`
BUILD = $(shell echo $(PWD) | sed 's/\/src.*$$/\/build&/')
LIB= $(BUILD)/llvm_dce.so

all: $(LIB)

load: $(LIB)
	opt -load $(LIB) --My_DCE  test/hello.ll -o test/hello_changed.ll

$(LIB): My_DCE.cpp
	make -C $(BUILD)
