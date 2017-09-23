BUILD = /home/pschen/llvm/llvm/build/lib

LIB= $(BUILD)/My_DCE.so

all: $(LIB)

load: $(LIB)
	opt -load $(LIB) --My_DCE  test/hello.ll -o test/hello_changed.ll
	llvm-dis test/hello_changed.bc 

$(LIB): My_DCE.cpp
	make -C $(BUILD)/Transforms/My_DCE
