cmd_firmware/mxT336SC21.fw.gen.o := /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/scripts/gcc-wrapper.py ccache /home/DECODER/Downloads/Kernel/arm-eabi-4.8/bin/arm-eabi-gcc -Wp,-MD,firmware/.mxT336SC21.fw.gen.o.d -nostdinc -isystem /home/DECODER/Downloads/Kernel/arm-eabi-4.8/bin/../lib/gcc/arm-eabi/4.8/include -I/home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include -Iarch/arm/include/generated -Iinclude  -I/home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include -include /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/kconfig.h -D__KERNEL__ -mlittle-endian   -I/home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/mach-msm/include -D__ASSEMBLY__ -mabi=aapcs-linux -mno-thumb-interwork -funwind-tables -D__LINUX_ARM_ARCH__=7 -mcpu=cortex-a7 -include asm/unified.h -msoft-float   -c -o firmware/mxT336SC21.fw.gen.o firmware/mxT336SC21.fw.gen.S

source_firmware/mxT336SC21.fw.gen.o := firmware/mxT336SC21.fw.gen.S

deps_firmware/mxT336SC21.fw.gen.o := \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/unified.h \
    $(wildcard include/config/arm/asm/unified.h) \
    $(wildcard include/config/thumb2/kernel.h) \

firmware/mxT336SC21.fw.gen.o: $(deps_firmware/mxT336SC21.fw.gen.o)

$(deps_firmware/mxT336SC21.fw.gen.o):
