cmd_net/wireless/built-in.o :=  /home/DECODER/Downloads/Kernel/arm-eabi-4.8/bin/arm-eabi-ld -EL   -r -o net/wireless/built-in.o net/wireless/cfg80211.o net/wireless/wext-core.o net/wireless/wext-proc.o net/wireless/wext-spy.o net/wireless/wext-priv.o ; scripts/mod/modpost net/wireless/built-in.o