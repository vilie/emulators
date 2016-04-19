all: 8080
8080: 8080.c instructions.c
	$(CC) $^ -o $@
tests: tests.c instructions.c
	$(CC) -DDEBUG $^ -o $@
.PHONY: clean
clean:
	rm -rf 8080 tests
