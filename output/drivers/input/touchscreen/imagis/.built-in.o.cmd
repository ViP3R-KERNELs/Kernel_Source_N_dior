cmd_drivers/input/touchscreen/imagis/built-in.o :=  /home/DECODER/Downloads/Kernel/arm-eabi-4.8/bin/arm-eabi-ld -EL   -r -o drivers/input/touchscreen/imagis/built-in.o drivers/input/touchscreen/imagis/ist30xx.o drivers/input/touchscreen/imagis/ist30xx_misc.o drivers/input/touchscreen/imagis/ist30xx_sys.o drivers/input/touchscreen/imagis/ist30xx_tracking.o drivers/input/touchscreen/imagis/ist30xx_update.o drivers/input/touchscreen/imagis/ist30xx_cmcs.o ; scripts/mod/modpost drivers/input/touchscreen/imagis/built-in.o