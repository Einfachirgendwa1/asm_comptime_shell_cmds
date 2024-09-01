default:
	@clang inserter.c -o inserter -fsanitize=address -g -Wall -Wextra -march=native -pipe
	@./inserter main.asm
	@nasm -f elf64 _main.asm -o main.o -g
	@ld main.o -o main
	@rm main.o
	@./main

no_sanitizer:
	@clang inserter.c -o inserter -g -Wall -Wextra -march=native -pipe

clean:
	@rm -f ./main ./inserter ./_main.asm ./core ./vgcore.* ./.gdb_history
