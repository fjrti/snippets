CC        = gcc -g -m32
LD        = ld -melf_i386
OBJCOPY   = objcopy
ENTRY     = __start
LDFILE    = src/bootloader_x86.ld
QUICKLOAD = src/quikload_floppy.s
DEF_SRC   = src/rtc.s
CS630     = http://www.cs.usfca.edu/~cruse/cs630f06/

all: clean boot.img pmboot.img

pmboot.img: boot.bin quickload.bin
	@dd if=quickload.bin of=pmboot.img bs=512 count=1
	@dd if=boot.bin of=pmboot.img seek=1 bs=512 count=2879

boot.img: boot.bin
	@dd if=boot.bin of=boot.img bs=512 count=1
#	@dd if=/dev/zero of=boot.img skip=1 seek=1 bs=512 count=2879

boot.bin:
	@if [ ! -f boot.S ]; then ./configure $(DEF_SRC); fi
	@$(CC) -c boot.S
	@$(LD) boot.o -o boot.elf -T$(LDFILE) #-e $(ENTRY) 
	@$(OBJCOPY) -R .pdr -R .comment -R.note -S -O binary boot.elf boot.bin

quickload.bin:
	@$(CC) -c $(QUICKLOAD) -o boot.o
	@$(LD) boot.o -o boot.elf -T$(LDFILE) #-e $(ENTRY) 
	@$(OBJCOPY) -R .pdr -R .comment -R.note -S -O binary boot.elf quickload.bin

update:
	@wget -c -m -nH -np --cut-dirs=2 -P res/ $(CS630)

boot: clean boot.img
	@bash qemu.sh boot

pmboot: clean pmboot.img
	@bash qemu.sh pmboot

clean:
	@rm -rf quickload.bin boot.o boot.elf boot.bin boot.img pmboot.img

distclean: clean
	@rm -rf boot.S


note:
	@cat NOTE.md

help:
	@echo "--------------------Assembly Course (CS630) Lab---------------------"
	@echo ""
	@echo "    :: Download ::"
	@echo ""
	@echo "    make update                  -- download the latest resources for the course"
	@echo ""
	@echo "    :: Configuration ::"
	@echo ""
	@echo "    ./configure src/helloworld.s -- configure the source want to compile"
	@echo "    ./configure src/rtc.s        -- configure the sources with real mode"
	@echo "    ./configure src/pmrtc.s      -- configure the sources with protected mode"
	@echo ""
	@echo "    :: Compile and Boot ::"
	@echo ""
	@echo "    make boot                    -- For Real mode"
	@echo "    make boot G=0                -- For Real mode, Curses based output, for ssh like console"
	@echo "    make boot D=1                -- For Real mode, for debugging with gdb"
	@echo "    make pmboot                  -- For Protected mode"
	@echo ""
	@echo "    :: Notes ::"
	@echo ""
	@echo "    make note"
	@echo ""
	@echo "--------------------------------------------------------------------"
