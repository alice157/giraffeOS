ISO = giraffeOS.iso
ISO_STAGING = dist
KERNEL = src/kernel

.PHONY: clean all kernel kernel-clean tags

all: $(ISO)

clean: kernel-clean
	rm -fv $(ISO)

kernel-clean:
	$(MAKE) -C $(KERNEL) clean

kernel $(KERNEL)/build/giraffeOS.bin:
	$(MAKE) -C $(KERNEL)

$(ISO): kernel
	cp -vf $(KERNEL)/build/giraffeOS.bin $(ISO_STAGING)/boot/
	grub-mkrescue -o $(ISO) $(ISO_STAGING)

tags:
	ctags -R .
