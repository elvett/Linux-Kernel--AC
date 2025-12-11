ifneq ($(KERNELRELEASE),)
# kbuild part of makefile
obj-m := hello1.o hello2.o

ccflags-y := -I$(PWD)/inc

else
# normal makefile
KDIR := /home/elvett/repos/linux-stable
PWD := $(shell pwd)

ARCH ?= arm
CROSS_COMPILE ?= arm-linux-gnueabi-

default:
	$(MAKE) -C $(KDIR) M=$(PWD) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE)

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE)
	rm -f *.o *~ core .depend .*.cmd *.ko *.mod.c
	rm -f System.map Module.symvers modules.order
	rm -rf .tmp_versions
endif

