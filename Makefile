ASM = nasm
CPP = i686-linux-gnu-g++
LD = i686-linux-gnu-ld

CPP_FLAGS = -fno-builtin -fno-exceptions -fno-stack-protector -fno-rtti -nostdlib -nodefaultlibs
ASM_FLAGS = -f elf32

ASM_FILE = src/boot.s src/ports.s src/gdt.s
CPP_FILE = src/main.cpp \
	src/kernel_utils/kernel_input.cpp src/kernel_utils/kernel_output.cpp src/kernel_utils/kernel_time.cpp src/kernel_utils/kernel_type.cpp

ASM_OBJECT_FILE = obj/boot.o obj/ports.o obj/gdt.o
CPP_OBJECT_FILE = obj/main.o \
	obj/kernel_utils/kernel_input.o obj/kernel_utils/kernel_output.o obj/kernel_utils/kernel_time.o obj/kernel_utils/kernel_type.o

TARGET = UwU.bin
TARGET_ISO = UwU.iso

all:$(TARGET) $(TARGET_ISO)

$(TARGET): $(ASM_OBJECT_FILE) $(CPP_OBJECT_FILE)
	$(LD) -T linker.ld -o $(TARGET) $(ASM_OBJECT_FILE) $(CPP_OBJECT_FILE)

$(TARGET_ISO): $(TARGET)
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

obj/%.o: src/%.s
	mkdir -p $(dir $@)
	$(ASM) $(ASM_FLAGS) $< -o $@

obj/%.o: src/%.cpp
	mkdir -p $(dir $@)
	$(CPP) $(CPP_FLAGS) -c $< -o $@

run:all
	qemu-system-i386 -cdrom UwU.iso

clean:
	rm -rf $(TARGET) obj iso UwU.iso

re: clean all