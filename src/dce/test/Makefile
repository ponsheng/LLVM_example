CLANG_FLAG = -emit-llvm
BC=hello.bc
LL=hello_changed.ll
LL_ORIGIN=hello.ll

all: bc ll_o

ll_o: hello.c
	clang $(CLANG_FLAG) hello.c -S -o $(LL_ORIGIN)

bc:  hello.c
	clang $(CLANG_FLAG)  hello.c -c -o $(BC)

bc2ll:$(BC)
	llvm-dis $(BC)

diff: $(LL) $(LL_ORIGIN)
	colordiff $^

clean:
	rm -f *.bc *.ll
