cmd_fs/configfs/configfs.o := /home/DECODER/Downloads/Kernel/arm-eabi-4.8/bin/arm-eabi-ld -EL   -r -o fs/configfs/configfs.o fs/configfs/inode.o fs/configfs/file.o fs/configfs/dir.o fs/configfs/symlink.o fs/configfs/mount.o fs/configfs/item.o ; scripts/mod/modpost fs/configfs/configfs.o
