main: main.c command tokenizer
	gcc main.c ./build/command.o ./build/tokenizer.o -o build/main.out

command: command.c command.h
	mkdir -p build # Make if not present
	gcc -c command.c -o build/command.o

tokenizer: tokenizer.c tokenizer.h
	mkdir -p build # Make if not present
	gcc -c tokenizer.c -o build/tokenizer.o

clean:
	rm -rf build
