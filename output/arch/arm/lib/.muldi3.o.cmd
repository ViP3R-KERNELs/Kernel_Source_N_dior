cmd_arch/arm/lib/muldi3.o := /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/scripts/gcc-wrapper.py ccache /home/DECODER/Downloads/Kernel/arm-eabi-4.8/bin/arm-eabi-gcc -Wp,-MD,arch/arm/lib/.muldi3.o.d -nostdinc -isystem /home/DECODER/Downloads/Kernel/arm-eabi-4.8/bin/../lib/gcc/arm-eabi/4.8/include -I/home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include -Iarch/arm/include/generated -Iinclude  -I/home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include -include /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/kconfig.h -D__KERNEL__ -mlittle-endian   -I/home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/mach-msm/include -D__ASSEMBLY__ -mabi=aapcs-linux -mno-thumb-interwork -funwind-tables -D__LINUX_ARM_ARCH__=7 -mcpu=cortex-a7 -include asm/unified.h -msoft-float   -c -o arch/arm/lib/muldi3.o /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/lib/muldi3.S

source_arch/arm/lib/muldi3.o := /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/lib/muldi3.S

deps_arch/arm/lib/muldi3.o := \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/unified.h \
    $(wildcard include/config/arm/asm/unified.h) \
    $(wildcard include/config/thumb2/kernel.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/linkage.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/compiler.h \
    $(wildcard include/config/sparse/rcu/pointer.h) \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/linkage.h \

arch/arm/lib/muldi3.o: $(deps_arch/arm/lib/muldi3.o)

$(deps_arch/arm/lib/muldi3.o):
