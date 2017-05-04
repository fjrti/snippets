LINUX := linux-3.10.105
BUSYBOX := busybox-1.26.2

TOP_DIR = $(shell pwd)

all: kernel.img rootfs.img

run: kernel.img rootfs.img
	qemu-system-x86_64 --enable-kvm \
		-kernel ./linux-3.10.105/arch/x86_64/boot/bzImage \
		-initrd rootfs.img \
		-append "root=/dev/ram rdinit=/sbin/init" \
		-net nic,model=virtio,macaddr=00:22:33:65:43:21 \
		-net user,hostfwd=::2323-:23 -vnc :51

debug: kernel.img rootfs.img
	qemu-system-x86_64 -kernel kernel.img \
		-append "root=/dev/ram rdinit=/sbin/init kgdboc=ttyS0,115200 kgdbwait" \
		-initrd rootfs.img \
		-net nic,model=virtio,macaddr=00:22:33:65:43:21 \
		-net user,hostfwd=::2323-:23 \
		-daemonize -S -s -vnc :51
	gdb -q  -ex "add-auto-load-safe-path $(pwd)" \
		-ex "file $(LINUX)/vmlinux" \
		-ex 'set arch i386:x86-64:intel' \
		-ex 'target remote localhost:1234' \
		-ex 'break start_kernel' \
		-ex 'continue' \
		-ex 'disconnect' \
		-ex 'set arch i386:x86-64' \
		-ex 'target remote :1234'	   

clean:
	rm -f kernel.img rootfs.img

distclean:
	rm -f kernel.img rootfs.img
	rm -rf $(LINUX)*
	rm -rf $(BUSYBOX)* 

update: $(LINUX)/.config $(BUSYBOX)/.config
	yes "" | make -C $(LINUX) oldconfig
	yes "" | make -C $(BUSYBOX) oldconfig

kernel.img: $(LINUX)/.config
	make -C $(LINUX) bzImage -j4
	cp $(LINUX)/arch/x86/boot/bzImage $@

rootfs.img: $(BUSYBOX)/.config
	make -C $(BUSYBOX) install -j4
	$(TOP_DIR)/genramfs $@

install $(LINUX)/.config $(BUSYBOX)/.config:
	$(TOP_DIR)/build

.PHONY: all run debug clean distclean update install
