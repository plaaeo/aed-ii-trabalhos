build:
	mkdir -p out
	gcc src/*.c src/*/*.c -o out/trab2.o -I src/ -g -lm -std=c99
