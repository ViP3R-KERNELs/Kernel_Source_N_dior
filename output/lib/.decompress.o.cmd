cmd_lib/decompress.o := /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/scripts/gcc-wrapper.py ccache /home/DECODER/Downloads/Kernel/arm-eabi-4.8/bin/arm-eabi-gcc -Wp,-MD,lib/.decompress.o.d -nostdinc -isystem /home/DECODER/Downloads/Kernel/arm-eabi-4.8/bin/../lib/gcc/arm-eabi/4.8/include -I/home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include -Iarch/arm/include/generated -Iinclude  -I/home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include -include /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/kconfig.h  -I/home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/lib -Ilib -D__KERNEL__ -mlittle-endian   -I/home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/mach-msm/include -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -mtune=cortex-a7 -mfpu=neon -Wno-array-bounds -Wno-maybe-uninitialized -fno-peel-loops -Wno-array-bounds -Wno-maybe-uninitialized --param=allow-store-data-races=0 -Os -marm -fno-dwarf2-cfi-asm -fstack-protector -fno-ipa-sra -mabi=aapcs-linux -mno-thumb-interwork -funwind-tables -D__LINUX_ARM_ARCH__=7 -mcpu=cortex-a7 -msoft-float -Uarm -Wframe-larger-than=1024 -Wno-unused-but-set-variable -fomit-frame-pointer -fno-var-tracking-assignments -fno-inline-functions-called-once -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow --param=allow-store-data-races=0 -fconserve-stack -DCC_HAVE_ASM_GOTO    -D"KBUILD_STR(s)=#s" -D"KBUILD_BASENAME=KBUILD_STR(decompress)"  -D"KBUILD_MODNAME=KBUILD_STR(decompress)" -c -o lib/.tmp_decompress.o /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/lib/decompress.c

source_lib/decompress.o := /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/lib/decompress.c

deps_lib/decompress.o := \
    $(wildcard include/config/decompress/gzip.h) \
    $(wildcard include/config/decompress/bzip2.h) \
    $(wildcard include/config/decompress/lzma.h) \
    $(wildcard include/config/decompress/xz.h) \
    $(wildcard include/config/decompress/lzo.h) \
    $(wildcard include/config/decompress/lz4.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/decompress/generic.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/decompress/bunzip2.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/decompress/unlzma.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/decompress/unxz.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/decompress/inflate.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/decompress/unlzo.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/decompress/unlz4.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/types.h \
    $(wildcard include/config/uid16.h) \
    $(wildcard include/config/lbdaf.h) \
    $(wildcard include/config/arch/dma/addr/t/64bit.h) \
    $(wildcard include/config/phys/addr/t/64bit.h) \
    $(wildcard include/config/64bit.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/types.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/asm-generic/int-ll64.h \
  arch/arm/include/generated/asm/bitsperlong.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/asm-generic/bitsperlong.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/posix_types.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/stddef.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/compiler.h \
    $(wildcard include/config/sparse/rcu/pointer.h) \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/compiler-gcc.h \
    $(wildcard include/config/arch/supports/optimized/inlining.h) \
    $(wildcard include/config/optimize/inlining.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/compiler-gcc4.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/posix_types.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/asm-generic/posix_types.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/string.h \
    $(wildcard include/config/binary/printf.h) \
  /home/DECODER/Downloads/Kernel/arm-eabi-4.8/lib/gcc/arm-eabi/4.8/include/stdarg.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/string.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/init.h \
    $(wildcard include/config/modules.h) \
    $(wildcard include/config/hotplug.h) \

lib/decompress.o: $(deps_lib/decompress.o)

$(deps_lib/decompress.o):
