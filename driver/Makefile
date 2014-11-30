# Invoke the kernel build system.
ifeq (${KERNELRELEASE},)
	UNAME := $(shell uname -r)
	KERNEL_SOURCE := /usr/src/linux-headers-${UNAME}
	PWD := $(shell pwd)
default:
	${MAKE} -C ${KERNEL_SOURCE} SUBDIRS=${PWD} modules
 
clean:
	${MAKE} -C ${KERNEL_SOURCE} SUBDIRS=${PWD} clean
else
	    obj-m := first_driver.o
endif
