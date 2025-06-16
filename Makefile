# ==== Configuration ====
LIMINE_DIR   := limine
KERNEL_DIR   := kernel
LIBC_DIR     := libc
BUILD_DIR    := bin
KERNEL_OUT   := $(BUILD_DIR)/kernel/kernel
LIBC_OUT     := $(BUILD_DIR)/libc/libc.a
OUTPUT_DIR   := iso_root
TARGET_ISO   := Lumora.iso

XORRISO_ARGS := -as mkisofs -R -r -J \
	-b boot/limine/limine-bios-cd.bin -no-emul-boot -boot-load-size 4 -boot-info-table \
	-hfsplus -apm-block-size 2048 \
	--efi-boot boot/limine/limine-uefi-cd.bin \
	-efi-boot-part --efi-boot-image --protective-msdos-label \
	$(OUTPUT_DIR) -o $(TARGET_ISO)

QEMU_FLAGS := -cdrom $(TARGET_ISO)

# ==== Default Target ====
all: $(TARGET_ISO)

# ==== ISO Generation Workflow ====
$(TARGET_ISO): prepare_dirs build_all copy_files iso_image

prepare_dirs:
	rm -f $(TARGET_ISO)
	mkdir -p $(BUILD_DIR) \
		$(BUILD_DIR)/libc \
		$(OUTPUT_DIR) 

build_all:
	$(MAKE) -C $(LIMINE_DIR)
	$(MAKE) -C $(LIBC_DIR)
	$(MAKE) -C $(KERNEL_DIR)

copy_files:
	# Copy kernel
	mkdir -p $(OUTPUT_DIR)/boot
	cp -v $(KERNEL_OUT) $(OUTPUT_DIR)/boot/

	# Copy Limine bootloader files
	mkdir -p $(OUTPUT_DIR)/boot/limine
	cp -v $(LIMINE_DIR)/limine.conf \
	      $(LIMINE_DIR)/limine-bios.sys \
	      $(LIMINE_DIR)/limine-bios-cd.bin \
	      $(LIMINE_DIR)/limine-uefi-cd.bin \
	      $(OUTPUT_DIR)/boot/limine

	# EFI Boot Tree
	mkdir -p $(OUTPUT_DIR)/EFI/BOOT
	cp -v $(LIMINE_DIR)/BOOTX64.EFI $(OUTPUT_DIR)/EFI/BOOT
	cp -v $(LIMINE_DIR)/BOOTIA32.EFI $(OUTPUT_DIR)/EFI/BOOT

iso_image:
	xorriso $(XORRISO_ARGS)
	./$(LIMINE_DIR)/limine bios-install $(TARGET_ISO)

# ==== Run with QEMU ====
run: $(TARGET_ISO)
	qemu-system-x86_64 $(QEMU_FLAGS)

# ==== Clean Everything ====
clean:
	rm -rf $(OUTPUT_DIR) $(BUILD_DIR) $(TARGET_ISO) .vscode

.PHONY: all prepare_dirs build_all copy_files iso_image run clean
