LIB=../../../build/lib/LLVMFunctionPass.so

all: $(LIB)

load: $(LIB)
	opt -load $(LIB) --PrintBB < ../../../../hello/hello.bc > /dev/null

$(LIB): FunctionPass.cpp
	make -C /home/pschen/llvm/llvm/build/
