cmd_drivers/net/wireless/wcnss/built-in.o :=  /home/DECODER/Downloads/Kernel/arm-eabi-4.8/bin/arm-eabi-ld -EL   -r -o drivers/net/wireless/wcnss/built-in.o drivers/net/wireless/wcnss/wcnsscore.o drivers/net/wireless/wcnss/wcnss_prealloc.o ; scripts/mod/modpost drivers/net/wireless/wcnss/built-in.o