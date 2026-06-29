CXX = aarch64-elf-g++
AS  = aarch64-elf-gcc
LD  = aarch64-elf-ld

CXXFLAGS = -ffreestanding -nostdlib -nostartfiles \
           -Iinclude \
           -O2 \
           -Wall \
           -std=c++20

# Updated path to tools/linker.ld based on your initial commit structure
LDFLAGS = -T tools/linker.ld -nostdlib

OBJ = \
    boot/boot.o \
    kernel/main.o \
    kernel/kernel.o \
    drivers/screen.o \
    drivers/uart.o

all: AthKernel.elf

boot/boot.o: boot/boot.S
	$(AS) -c boot/boot.S -o boot/boot.o

kernel/main.o: kernel/main.cpp
	$(CXX) $(CXXFLAGS) -c kernel/main.cpp -o kernel/main.o

kernel/kernel.o: kernel/kernel.cpp
	$(CXX) $(CXXFLAGS) -c kernel/kernel.cpp -o kernel/kernel.o

drivers/screen.o: drivers/screen.cpp
	$(CXX) $(CXXFLAGS) -c drivers/screen.cpp -o drivers/screen.o

drivers/uart.o: drivers/uart.cpp
	$(CXX) $(CXXFLAGS) -c drivers/uart.cpp -o drivers/uart.o

AthKernel.elf: $(OBJ)
	$(LD) $(LDFLAGS) $(OBJ) -o AthKernel.elf

clean:
	rm -f $(OBJ) AthKernel.elf