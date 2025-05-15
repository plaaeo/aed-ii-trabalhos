build:
	mkdir -p out
	gcc src/*.c src/*/*.c -Wall -Wextra -Werror -o out/trab2.o -I src/ -g -lm -std=c99
