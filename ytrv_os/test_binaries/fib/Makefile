all: fib.bin fib.S fib.elf


%.S: %.c
	$(RVCC) -S $^ -o $@

%.o: %.S
	$(RVCC) -c $^ -o $@

%.elf: %.o
	$(RVCC) -Wl,-Ttext=0x0 -nodefaultlibs -nolibc -nostdlib -mno-relax $^ -o $@

%.bin: %.elf
	riscv64-unknown-elf-objcopy -I elf64-littleriscv -O binary $^ $@

clean:
	rm -fr *.S *.o *.bin *.elf

