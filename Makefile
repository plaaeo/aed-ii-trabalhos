build:
	mkdir -p out
	gcc src/*.c src/*/*.c -Wall -Wextra -Werror -W -Wno-unused-variable -o out/trab2.o -I src/ -g -lm -std=c99
