cmd_drivers/thermal/built-in.o :=  /home/DECODER/Downloads/Kernel/arm-eabi-4.8/bin/arm-eabi-ld -EL   -r -o drivers/thermal/built-in.o drivers/thermal/thermal_sys.o drivers/thermal/msm_thermal.o drivers/thermal/msm_thermal-dev.o drivers/thermal/msm8974-tsens.o drivers/thermal/qpnp-temp-alarm.o drivers/thermal/qpnp-adc-tm.o ; scripts/mod/modpost drivers/thermal/built-in.o
