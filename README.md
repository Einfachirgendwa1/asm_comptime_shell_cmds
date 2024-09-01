Executes shell commands and embeds the output into the file.

# Disclaimer

I wrote this in like 1 hour and it's currently super bad, I'm working on it.

# Example

Embeds the first 100 primes into an assembly file:

example.asm:

```asm
%define primes_literal;;; `./example.py 100`
```

Running

```bash
make example
```

Then creates a file called \_example.asm which contains the output of `./example.py 100` instead of the comment:

```asm
%define primes_literal "First 100 primes: 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547"
```

That's it.

# Installation

```bash
make install
```

# Usage

Running

```bash
asm_comptime_shell_cmds [file]
```

creates \_\[file\] which you can then compile.
