ASM = nasm
CPP = i686-linux-gnu-g++
LD = i686-linux-gnu-ld

CPP_FLAGS = -fno-builtin -fno-exceptions -fno-stack-protector -fno-rtti -nostdlib -nodefaultlibs
ASM_FLAGS = -f elf32

ASM_FILE = src/boot.s src/ports.s
CPP_FILE = src/main.cpp src/kernel_utils/kernel_input.cpp src/kernel_utils/kernel_output.cpp

ASM_OBJECT_FILE = obj/boot.o obj/ports.o
CPP_OBJECT_FILE = obj/main.o obj/kernel_utils/kernel_input.o obj/kernel_utils/kernel_output.o

TARGET = UwU.bin

all:$(TARGET)

$(TARGET): $(ASM_OBJECT_FILE) $(CPP_OBJECT_FILE)
	$(LD) -T linker.ld -o $(TARGET) $(ASM_OBJECT_FILE) $(CPP_OBJECT_FILE)

obj/%.o: src/%.s
	mkdir -p $(dir $@)
	$(ASM) $(ASM_FLAGS) $< -o $@

obj/%.o: src/%.cpp
	mkdir -p $(dir $@)
	$(CPP) $(CPP_FLAGS) -c $< -o $@

run:all
	mkdir -p iso/boot/grub
	cp $(TARGET) iso/boot/UwU.bin
	echo "set timeout=0" > iso/boot/grub/grub.cfg
	echo "set default=0" >> iso/boot/grub/grub.cfg
	echo "" >> iso/boot/grub/grub.cfg
	echo "menuentry \"UwU\" {" >> iso/boot/grub/grub.cfg
	echo "    multiboot /boot/UwU.bin" >> iso/boot/grub/grub.cfg
	echo "    boot" >> iso/boot/grub/grub.cfg
	echo "}" >> iso/boot/grub/grub.cfg
	grub-mkrescue -o UwU.iso iso
	qemu-system-i386 -cdrom UwU.iso

clean:
	rm -rf $(TARGET) $(ASM_OBJECT_FILE) $(CPP_OBJECT_FILE) iso UwU.iso

re: clean all