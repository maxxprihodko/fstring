# Compile the library itself
LIB_CORE = src/*.c

# Compile the test files
TEST_CORE = ${LIB_CORE}
TEST_SRCS = tests/main.c ${TEST_CORE}

tests: bin
	gcc -o bin/test $(TEST_SRCS) -lm -Wpragmas

	./bin/test

clean:
	rm -rf bin

bin:
	mkdir $@