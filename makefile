.SILENT:

CFLAGS := -ffreestanding -fno-stack-protector -fshort-wchar -mno-red-zone -mno-ms-bitfields -I src -I efi -Ofast 
LFLAGS := -nostdlib -Wl,-dll -shared -Wl,--subsystem,10 -e efi_main -Ofast 

.PHONY: build
build:

	mkdir -p _build
	rm -f _build/fat.img _build/test.img
	touch _build/fat.img _build/test.img

	truncate -s 32M _build/fat.img
	truncate -s 1244M _build/test.img
	
	mkfs.fat -v -F 32 -S 512 -s 1 -n "FAT32" _build/fat.img 65535 1>/dev/null 2>/dev/null
	mmd -i _build/fat.img ::/EFI
	mmd -i _build/fat.img ::/EFI/BOOT

	x86_64-w64-mingw32-gcc $(CFLAGS) -c src/boot-main.c -o _build/boot-main.o 
	x86_64-w64-mingw32-gcc $(LFLAGS) -o _build/BOOTX64.EFI _build/boot-main.o 

	mcopy -i _build/fat.img _build/BOOTX64.EFI ::/EFI/BOOT

	dd if=_build/fat.img of=_build/test.img bs=512 count=65535 conv=notrunc status=none 

.PHONY: clean
clean:
	rm -rf _build

.PHONY: run
run: build

	qemu-system-x86_64 \
		-machine type=q35,accel=kvm \
		-cpu host \
		-m 4G \
		-smp 4 \
		-no-reboot \
		-drive file=/usr/share/ovmf/x64/OVMF.fd,format=raw,if=pflash,readonly=on \
		-drive file=_build/test.img,format=raw,if=none,id=drive0 \
		-device ide-hd,drive=drive0,bus=ide.0,unit=0,bootindex=0 \
		-usb \
		-vga std \
		-serial vc 

