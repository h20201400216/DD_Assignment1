#Userspace Application File name
USERFILE = userapp

obj-m := main.o

#Build recepie for kernel and user application
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) modules
	gcc -o $(USERFILE) $(USERFILE).c

#Build recepie for User application
userapp:
	gcc -o $(USERFILE) $(USERFILE).c

#Build recepie for kernel application
kern:
	 make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) modules
