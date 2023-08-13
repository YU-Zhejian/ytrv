
MAKEFLAGS += --no-builtin-rules

.SUFFIXES:

export RVCC := riscv64-unknown-elf-gcc -march=rv64g \
	-Wall -Wextra -Wpedantic

.PHONY: all
all: exit fib

.PHONY: exit
exit:
	$(MAKE) -C exit

.PHONY: fib
fib:
	$(MAKE) -C fib

.PHONY: clean
clean:
	$(MAKE) -C exit clean
	$(MAKE) -C fib clean
