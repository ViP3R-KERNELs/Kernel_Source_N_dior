cmd_kernel/trace/built-in.o :=  /home/DECODER/Downloads/Kernel/arm-eabi-4.8/bin/arm-eabi-ld -EL   -r -o kernel/trace/built-in.o kernel/trace/trace_clock.o kernel/trace/ring_buffer.o ; scripts/mod/modpost kernel/trace/built-in.o
