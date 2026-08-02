SRCS = $(wildcard src/*c)

run:
	gcc $(SRCS) && ./a.out 
