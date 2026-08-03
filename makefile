SRCS = $(wildcard src/*c)

run:
	@gcc $(SRCS) && ./a.out 

run_tests:
	@gcc $(SRCS) tests/tests.c && ./a.out
