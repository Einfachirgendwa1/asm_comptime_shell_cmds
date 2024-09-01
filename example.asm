%define primes_literal;;; `./example.py 100`
%strlen strlen primes_literal

section .data
primes  db primes_literal, 10

section .text
global  _start

_start:
	MOV rax, 1
	MOV rdi, 1
	MOV rsi, primes
	MOV rdx, strlen+1
	SYSCALL

	MOV rax, 60
	XOR rdi, rdi
	SYSCALL
