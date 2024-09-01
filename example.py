#!/usr/bin/env python
from sys import argv

x = 2


def is_prime() -> bool:
    y = 2
    while y * y <= x:
        if x % y == 0:
            return False
        y += 1
    return True


def next_prime() -> int:
    global x
    x += 1

    while not is_prime():
        x += 1
    else:
        return x


primes = [str(next_prime()) for _ in range(int(argv[1]))]
print(f' "First {argv[1]} primes: {", ".join(primes)}"')
