build:
	@clang main.c -o main -march=native -pipe -O2

install: build
	@cp main /usr/bin/asm_comptime_shell_cmds

example: build
	@./main example.asm
	@nasm -f elf64 _example.asm -o example.o
	@ld example.o -o example
	@rm example.o
	@./example

clean:
	@rm -f main example _example.asm core vgcore.* .gdb_history
