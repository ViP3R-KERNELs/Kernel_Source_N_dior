cmd_drivers/leds/built-in.o :=  /home/DECODER/Downloads/Kernel/arm-eabi-4.8/bin/arm-eabi-ld -EL   -r -o drivers/leds/built-in.o drivers/leds/led-core.o drivers/leds/led-class.o drivers/leds/led-triggers.o drivers/leds/leds-qpnp.o drivers/leds/leds-gpio.o drivers/leds/buttonlight-lm3533.o ; scripts/mod/modpost drivers/leds/built-in.o
