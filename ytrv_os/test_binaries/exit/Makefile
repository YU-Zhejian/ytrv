all: exit.bin exit.elf exit.S


%.S: %.c
	$(RVCC) -O2 -S $^ -o $@

%.o: %.S
	$(RVCC) -c $^ -o $@

%.elf: %.o
	$(RVCC) -Wl,-Ttext=0x0 -nodefaultlibs -nolibc -nostdlib -mno-relax $^ -o $@

%.bin: %.elf
	riscv64-unknown-elf-objcopy -I elf64-littleriscv -O binary $^ $@

clean:
	rm -fr *.S *.o *.bin *.elf
