GPPPARAMS = -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore
ASPARAMS = --32
LDPARAMS = -melf_i386

objects = gen/loader.o gen/console.o gen/gdt.o gen/port.o gen/interrupts.o gen/interruptstubs.o gen/kernel.o
pathDir = gen

$(pathDir):
	mkdir $(pathDir)

$(pathDir)/%.o: src/%.cpp | $(pathDir)
	g++ $(GPPPARAMS) -o $@ -c $<

$(pathDir)/%.o: common/%.s | $(pathDir)
	as $(ASPARAMS) -o $@ $<

mykernel.bin: common/linker.ld $(objects)
	ld $(LDPARAMS) -T $< -o $@ $(objects)

mykernel.iso: mykernel.bin
	mkdir -p iso/boot/grub
	cp mykernel.bin iso/boot/
	echo 'set timeout=0' > iso/boot/grub/grub.cfg
	echo 'set default=0' >> iso/boot/grub/grub.cfg
	echo '' >> iso/boot/grub/grub.cfg
	echo 'menuentry "My Operating System" {' >> iso/boot/grub/grub.cfg
	echo '	multiboot /boot/mykernel.bin' >> iso/boot/grub/grub.cfg
	echo '	boot' >> iso/boot/grub/grub.cfg
	echo '}' >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=mykernel.iso iso
	rm -rf iso

run: mykernel.iso
	(/mnt/c/Windows/System32/taskkill.exe /F /IM VirtualBoxVM.exe) || true
	/mnt/d/Games/VirtualBox/VirtualBoxVM.exe --startvm "My OS" &

.PHONY: clean
clean:
	rm -rf $(objects) mykernel.bin mykernel.iso gen
