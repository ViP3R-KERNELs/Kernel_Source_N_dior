cmd_sound/soc/codecs/built-in.o :=  /home/DECODER/Downloads/Kernel/arm-eabi-4.8/bin/arm-eabi-ld -EL   -r -o sound/soc/codecs/built-in.o sound/soc/codecs/snd-soc-wcd9306.o sound/soc/codecs/wcd9xxx-resmgr.o sound/soc/codecs/wcd9xxx-mbhc.o sound/soc/codecs/snd-soc-msm-stub.o sound/soc/codecs/sound_control_3_gpl.o ; scripts/mod/modpost sound/soc/codecs/built-in.o