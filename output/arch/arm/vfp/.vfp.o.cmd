cmd_arch/arm/vfp/vfp.o := /home/DECODER/Downloads/Kernel/arm-eabi-4.8/bin/arm-eabi-ld -EL --no-warn-mismatch  -r -o arch/arm/vfp/vfp.o arch/arm/vfp/vfpmodule.o arch/arm/vfp/entry.o arch/arm/vfp/vfphw.o arch/arm/vfp/vfpsingle.o arch/arm/vfp/vfpdouble.o ; scripts/mod/modpost arch/arm/vfp/vfp.o
