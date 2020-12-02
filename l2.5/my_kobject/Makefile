MODULE = solution
obj-m += $(MODULE).o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

load:
	sudo insmod $(MODULE).ko
	sudo dmesg -c

unload:
	sudo rmmod $(MODULE).ko
	sudo dmesg -c
