all:
	gcc -std=c11 -Wall -Wextra -Werror -pedantic graph.c main.c -o main.exe

run:
	./main.exe