obj-m += solution.o

export KROOT=/lib/modules/$(shell uname -r)/build

all:
	make -C $(KROOT) M=$(PWD) modules -k 2>&1 | tee build.log

clean:
	make -C $(KROOT) M=$(PWD) clean

load:
	sudo insmod solution.ko
	sudo dmesg -c

unload:
	sudo rmmod solution.ko
	sudo dmesg -c
