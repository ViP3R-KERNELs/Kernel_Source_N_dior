cmd_drivers/power/power_supply.o := /home/DECODER/Downloads/Kernel/arm-eabi-4.8/bin/arm-eabi-ld -EL   -r -o drivers/power/power_supply.o drivers/power/power_supply_core.o drivers/power/power_supply_sysfs.o drivers/power/power_supply_leds.o ; scripts/mod/modpost drivers/power/power_supply.o