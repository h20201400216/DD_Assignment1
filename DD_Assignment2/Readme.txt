Steps for Building and Executing the Virtual Block Device Driver

1. Extract the Files to a folder
2. From the directory, build the module using make all command
3. Insert the module using mkmod command (Module name: main.ko)
4. To check if the module is inserted, use lsmod command
5. Partition info can be checked using cat /proc/partitions, ls -l /dev/dof* or fdisk -l commands
6. 2 logical devices are present named dof1 and dof2
7. To write to the device, shift to sudo mode using sudo -s
8. To write use the command cat > /dev/dof and to read the data type the command xxd /dev/dof | less
9. After verification, module can be removed using command rmmod
