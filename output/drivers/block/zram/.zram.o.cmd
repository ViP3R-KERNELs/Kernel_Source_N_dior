cmd_drivers/block/zram/zram.o := /home/DECODER/Downloads/Kernel/arm-eabi-4.8/bin/arm-eabi-ld -EL   -r -o drivers/block/zram/zram.o drivers/block/zram/zcomp_lzo.o drivers/block/zram/zcomp.o drivers/block/zram/zram_drv.o drivers/block/zram/zcomp_lz4.o ; scripts/mod/modpost drivers/block/zram/zram.o
