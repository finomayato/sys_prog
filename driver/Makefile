# Taken article written by Anil Kumar Pugalia on December 1, 2010
# http://www.opensourceforu.com/2010/12/writing-your-first-linux-driver/
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
