cmd_drivers/w1/built-in.o :=  /home/DECODER/Downloads/Kernel/arm-eabi-4.8/bin/arm-eabi-ld -EL   -r -o drivers/w1/built-in.o drivers/w1/wire.o drivers/w1/masters/built-in.o drivers/w1/slaves/built-in.o ; scripts/mod/modpost drivers/w1/built-in.o
