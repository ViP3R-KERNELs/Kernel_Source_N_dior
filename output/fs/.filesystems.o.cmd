cmd_fs/filesystems.o := /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/scripts/gcc-wrapper.py ccache /home/DECODER/Downloads/Kernel/arm-eabi-4.8/bin/arm-eabi-gcc -Wp,-MD,fs/.filesystems.o.d -nostdinc -isystem /home/DECODER/Downloads/Kernel/arm-eabi-4.8/bin/../lib/gcc/arm-eabi/4.8/include -I/home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include -Iarch/arm/include/generated -Iinclude  -I/home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include -include /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/kconfig.h  -I/home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/fs -Ifs -D__KERNEL__ -mlittle-endian   -I/home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/mach-msm/include -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -mtune=cortex-a7 -mfpu=neon -Wno-array-bounds -Wno-maybe-uninitialized -fno-peel-loops -Wno-array-bounds -Wno-maybe-uninitialized --param=allow-store-data-races=0 -Os -marm -fno-dwarf2-cfi-asm -fstack-protector -fno-ipa-sra -mabi=aapcs-linux -mno-thumb-interwork -funwind-tables -D__LINUX_ARM_ARCH__=7 -mcpu=cortex-a7 -msoft-float -Uarm -Wframe-larger-than=1024 -Wno-unused-but-set-variable -fomit-frame-pointer -fno-var-tracking-assignments -fno-inline-functions-called-once -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow --param=allow-store-data-races=0 -fconserve-stack -DCC_HAVE_ASM_GOTO    -D"KBUILD_STR(s)=#s" -D"KBUILD_BASENAME=KBUILD_STR(filesystems)"  -D"KBUILD_MODNAME=KBUILD_STR(filesystems)" -c -o fs/.tmp_filesystems.o /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/fs/filesystems.c

source_fs/filesystems.o := /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/fs/filesystems.c

deps_fs/filesystems.o := \
    $(wildcard include/config/proc/fs.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/syscalls.h \
    $(wildcard include/config/ftrace/syscalls.h) \
    $(wildcard include/config/ppc64.h) \
    $(wildcard include/config/alpha.h) \
    $(wildcard include/config/mips.h) \
    $(wildcard include/config/have/syscall/wrappers.h) \
    $(wildcard include/config/uid16.h) \
    $(wildcard include/config/ia64.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/types.h \
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
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/aio_abi.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/byteorder.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/byteorder/little_endian.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/swab.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/swab.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/byteorder/generic.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/capability.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/list.h \
    $(wildcard include/config/debug/list.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/poison.h \
    $(wildcard include/config/illegal/pointer/value.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/const.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/bug.h \
    $(wildcard include/config/generic/bug.h) \
    $(wildcard include/config/panic/on/data/corruption.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/bug.h \
    $(wildcard include/config/bug.h) \
    $(wildcard include/config/thumb2/kernel.h) \
    $(wildcard include/config/debug/bugverbose.h) \
    $(wildcard include/config/arm/lpae.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/linkage.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/linkage.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/asm-generic/bug.h \
    $(wildcard include/config/generic/bug/relative/pointers.h) \
    $(wildcard include/config/smp.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/sem.h \
    $(wildcard include/config/sysvipc.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/ipc.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/ipcbuf.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/asm-generic/ipcbuf.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/spinlock.h \
    $(wildcard include/config/debug/spinlock.h) \
    $(wildcard include/config/generic/lockbreak.h) \
    $(wildcard include/config/preempt.h) \
    $(wildcard include/config/debug/lock/alloc.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/typecheck.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/preempt.h \
    $(wildcard include/config/debug/preempt.h) \
    $(wildcard include/config/preempt/tracer.h) \
    $(wildcard include/config/preempt/count.h) \
    $(wildcard include/config/preempt/notifiers.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/thread_info.h \
    $(wildcard include/config/compat.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/bitops.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/bitops.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/irqflags.h \
    $(wildcard include/config/trace/irqflags.h) \
    $(wildcard include/config/irqsoff/tracer.h) \
    $(wildcard include/config/trace/irqflags/support.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/irqflags.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/ptrace.h \
    $(wildcard include/config/cpu/endian/be8.h) \
    $(wildcard include/config/arm/thumb.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/hwcap.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/asm-generic/bitops/non-atomic.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/asm-generic/bitops/fls64.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/asm-generic/bitops/sched.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/asm-generic/bitops/hweight.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/asm-generic/bitops/arch_hweight.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/asm-generic/bitops/const_hweight.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/asm-generic/bitops/lock.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/asm-generic/bitops/le.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/asm-generic/bitops/ext2-atomic-setbit.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/thread_info.h \
    $(wildcard include/config/arm/thumbee.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/fpstate.h \
    $(wildcard include/config/vfpv3.h) \
    $(wildcard include/config/iwmmxt.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/domain.h \
    $(wildcard include/config/verify/permission/fault.h) \
    $(wildcard include/config/io/36.h) \
    $(wildcard include/config/cpu/use/domains.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/barrier.h \
    $(wildcard include/config/cpu/32v6k.h) \
    $(wildcard include/config/cpu/xsc3.h) \
    $(wildcard include/config/cpu/fa526.h) \
    $(wildcard include/config/arch/has/barriers.h) \
    $(wildcard include/config/arm/dma/mem/bufferable.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/outercache.h \
    $(wildcard include/config/outer/cache/sync.h) \
    $(wildcard include/config/outer/cache.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/kernel.h \
    $(wildcard include/config/preempt/voluntary.h) \
    $(wildcard include/config/debug/atomic/sleep.h) \
    $(wildcard include/config/prove/locking.h) \
    $(wildcard include/config/ring/buffer.h) \
    $(wildcard include/config/tracing.h) \
    $(wildcard include/config/numa.h) \
    $(wildcard include/config/compaction.h) \
    $(wildcard include/config/ftrace/mcount/record.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/sysinfo.h \
  /home/DECODER/Downloads/Kernel/arm-eabi-4.8/lib/gcc/arm-eabi/4.8/include/stdarg.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/log2.h \
    $(wildcard include/config/arch/has/ilog2/u32.h) \
    $(wildcard include/config/arch/has/ilog2/u64.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/printk.h \
    $(wildcard include/config/printk.h) \
    $(wildcard include/config/dynamic/debug.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/init.h \
    $(wildcard include/config/modules.h) \
    $(wildcard include/config/hotplug.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/dynamic_debug.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/div64.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/compiler.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/stringify.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/bottom_half.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/spinlock_types.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/spinlock_types.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/lockdep.h \
    $(wildcard include/config/lockdep.h) \
    $(wildcard include/config/lock/stat.h) \
    $(wildcard include/config/prove/rcu.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/rwlock_types.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/spinlock.h \
    $(wildcard include/config/msm/krait/wfe/fixup.h) \
    $(wildcard include/config/arm/ticket/locks.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/processor.h \
    $(wildcard include/config/have/hw/breakpoint.h) \
    $(wildcard include/config/mmu.h) \
    $(wildcard include/config/arm/errata/754327.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/hw_breakpoint.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/rwlock.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/spinlock_api_smp.h \
    $(wildcard include/config/inline/spin/lock.h) \
    $(wildcard include/config/inline/spin/lock/bh.h) \
    $(wildcard include/config/inline/spin/lock/irq.h) \
    $(wildcard include/config/inline/spin/lock/irqsave.h) \
    $(wildcard include/config/inline/spin/trylock.h) \
    $(wildcard include/config/inline/spin/trylock/bh.h) \
    $(wildcard include/config/uninline/spin/unlock.h) \
    $(wildcard include/config/inline/spin/unlock/bh.h) \
    $(wildcard include/config/inline/spin/unlock/irq.h) \
    $(wildcard include/config/inline/spin/unlock/irqrestore.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/rwlock_api_smp.h \
    $(wildcard include/config/inline/read/lock.h) \
    $(wildcard include/config/inline/write/lock.h) \
    $(wildcard include/config/inline/read/lock/bh.h) \
    $(wildcard include/config/inline/write/lock/bh.h) \
    $(wildcard include/config/inline/read/lock/irq.h) \
    $(wildcard include/config/inline/write/lock/irq.h) \
    $(wildcard include/config/inline/read/lock/irqsave.h) \
    $(wildcard include/config/inline/write/lock/irqsave.h) \
    $(wildcard include/config/inline/read/trylock.h) \
    $(wildcard include/config/inline/write/trylock.h) \
    $(wildcard include/config/inline/read/unlock.h) \
    $(wildcard include/config/inline/write/unlock.h) \
    $(wildcard include/config/inline/read/unlock/bh.h) \
    $(wildcard include/config/inline/write/unlock/bh.h) \
    $(wildcard include/config/inline/read/unlock/irq.h) \
    $(wildcard include/config/inline/write/unlock/irq.h) \
    $(wildcard include/config/inline/read/unlock/irqrestore.h) \
    $(wildcard include/config/inline/write/unlock/irqrestore.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/atomic.h \
    $(wildcard include/config/arch/has/atomic/or.h) \
    $(wildcard include/config/generic/atomic64.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/atomic.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/cmpxchg.h \
    $(wildcard include/config/cpu/sa1100.h) \
    $(wildcard include/config/cpu/sa110.h) \
    $(wildcard include/config/cpu/v6.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/asm-generic/cmpxchg-local.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/asm-generic/atomic-long.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/sembuf.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/rcupdate.h \
    $(wildcard include/config/rcu/torture/test.h) \
    $(wildcard include/config/tree/rcu.h) \
    $(wildcard include/config/tree/preempt/rcu.h) \
    $(wildcard include/config/rcu/trace.h) \
    $(wildcard include/config/preempt/rcu.h) \
    $(wildcard include/config/tiny/rcu.h) \
    $(wildcard include/config/tiny/preempt/rcu.h) \
    $(wildcard include/config/debug/objects/rcu/head.h) \
    $(wildcard include/config/hotplug/cpu.h) \
    $(wildcard include/config/preempt/rt.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/cache.h \
    $(wildcard include/config/arch/has/cache/line/size.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/cache.h \
    $(wildcard include/config/arm/l1/cache/shift.h) \
    $(wildcard include/config/aeabi.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/threads.h \
    $(wildcard include/config/nr/cpus.h) \
    $(wildcard include/config/base/small.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/cpumask.h \
    $(wildcard include/config/cpumask/offstack.h) \
    $(wildcard include/config/debug/per/cpu/maps.h) \
    $(wildcard include/config/disable/obsolete/cpumask/functions.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/bitmap.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/string.h \
    $(wildcard include/config/binary/printf.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/string.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/seqlock.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/completion.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/wait.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/current.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/debugobjects.h \
    $(wildcard include/config/debug/objects.h) \
    $(wildcard include/config/debug/objects/free.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/rcutree.h \
  arch/arm/include/generated/asm/siginfo.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/asm-generic/siginfo.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/signal.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/asm-generic/signal-defs.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/sigcontext.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/unistd.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/unistd.h \
    $(wildcard include/config/oabi/compat.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/quota.h \
    $(wildcard include/config/quota/netlink/interface.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/errno.h \
  arch/arm/include/generated/asm/errno.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/asm-generic/errno.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/asm-generic/errno-base.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/mutex.h \
    $(wildcard include/config/debug/mutexes.h) \
    $(wildcard include/config/have/arch/mutex/cpu/relax.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/rwsem.h \
    $(wildcard include/config/rwsem/generic/spinlock.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/rwsem-spinlock.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/percpu_counter.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/smp.h \
    $(wildcard include/config/use/generic/smp/helpers.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/smp.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/percpu.h \
    $(wildcard include/config/need/per/cpu/embed/first/chunk.h) \
    $(wildcard include/config/need/per/cpu/page/first/chunk.h) \
    $(wildcard include/config/have/setup/per/cpu/area.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/pfn.h \
  arch/arm/include/generated/asm/percpu.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/asm-generic/percpu.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/percpu-defs.h \
    $(wildcard include/config/debug/force/weak/per/cpu.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/dqblk_xfs.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/dqblk_v1.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/dqblk_v2.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/dqblk_qtree.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/key.h \
    $(wildcard include/config/keys.h) \
    $(wildcard include/config/sysctl.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/rbtree.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/sysctl.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/trace/syscall.h \
    $(wildcard include/config/perf/events.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/tracepoint.h \
    $(wildcard include/config/tracepoints.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/static_key.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/jump_label.h \
    $(wildcard include/config/jump/label.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/workqueue.h \
    $(wildcard include/config/debug/objects/work.h) \
    $(wildcard include/config/freezer.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/timer.h \
    $(wildcard include/config/timer/stats.h) \
    $(wildcard include/config/debug/objects/timers.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/ktime.h \
    $(wildcard include/config/ktime/scalar.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/time.h \
    $(wildcard include/config/arch/uses/gettimeoffset.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/math64.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/jiffies.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/timex.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/param.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/param.h \
    $(wildcard include/config/hz.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/timex.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/mach-msm/include/mach/timex.h \
    $(wildcard include/config/have/arch/has/current/timer.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/ftrace_event.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/ring_buffer.h \
    $(wildcard include/config/ring/buffer/allow/swap.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/kmemcheck.h \
    $(wildcard include/config/kmemcheck.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/mm_types.h \
    $(wildcard include/config/split/ptlock/cpus.h) \
    $(wildcard include/config/have/cmpxchg/double.h) \
    $(wildcard include/config/have/aligned/struct/page.h) \
    $(wildcard include/config/want/page/debug/flags.h) \
    $(wildcard include/config/aio.h) \
    $(wildcard include/config/mm/owner.h) \
    $(wildcard include/config/mmu/notifier.h) \
    $(wildcard include/config/transparent/hugepage.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/auxvec.h \
  arch/arm/include/generated/asm/auxvec.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/asm-generic/auxvec.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/prio_tree.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/page-debug-flags.h \
    $(wildcard include/config/page/poisoning.h) \
    $(wildcard include/config/page/guard.h) \
    $(wildcard include/config/page/debug/something/else.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/page.h \
    $(wildcard include/config/cpu/copy/v3.h) \
    $(wildcard include/config/cpu/copy/v4wt.h) \
    $(wildcard include/config/cpu/copy/v4wb.h) \
    $(wildcard include/config/cpu/copy/feroceon.h) \
    $(wildcard include/config/cpu/copy/fa.h) \
    $(wildcard include/config/cpu/xscale.h) \
    $(wildcard include/config/cpu/copy/v6.h) \
    $(wildcard include/config/kuser/helpers.h) \
    $(wildcard include/config/have/arch/pfn/valid.h) \
    $(wildcard include/config/memory/hotplug/sparse.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/glue.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/pgtable-2level-types.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/memory.h \
    $(wildcard include/config/need/mach/memory/h.h) \
    $(wildcard include/config/page/offset.h) \
    $(wildcard include/config/highmem.h) \
    $(wildcard include/config/dram/size.h) \
    $(wildcard include/config/dram/base.h) \
    $(wildcard include/config/have/tcm.h) \
    $(wildcard include/config/arm/patch/phys/virt.h) \
    $(wildcard include/config/phys/offset.h) \
  arch/arm/include/generated/asm/sizes.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/asm-generic/sizes.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/mach-msm/include/mach/memory.h \
    $(wildcard include/config/arch/msm7x30.h) \
    $(wildcard include/config/sparsemem.h) \
    $(wildcard include/config/vmsplit/3g.h) \
    $(wildcard include/config/arch/msm/arm11.h) \
    $(wildcard include/config/arch/msm/cortex/a5.h) \
    $(wildcard include/config/cache/l2x0.h) \
    $(wildcard include/config/arch/msm8x60.h) \
    $(wildcard include/config/arch/msm8960.h) \
    $(wildcard include/config/dont/map/hole/after/membank0.h) \
    $(wildcard include/config/arch/msm/scorpion.h) \
    $(wildcard include/config/arch/msm/krait.h) \
    $(wildcard include/config/arch/msm7x27.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/asm-generic/memory_model.h \
    $(wildcard include/config/flatmem.h) \
    $(wildcard include/config/discontigmem.h) \
    $(wildcard include/config/sparsemem/vmemmap.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/asm-generic/getorder.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/mmu.h \
    $(wildcard include/config/cpu/has/asid.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/mm.h \
    $(wildcard include/config/fix/movable/zone.h) \
    $(wildcard include/config/have/arch/mmap/rnd/bits.h) \
    $(wildcard include/config/have/arch/mmap/rnd/compat/bits.h) \
    $(wildcard include/config/stack/growsup.h) \
    $(wildcard include/config/ksm.h) \
    $(wildcard include/config/have/memblock/node/map.h) \
    $(wildcard include/config/have/arch/early/pfn/to/nid.h) \
    $(wildcard include/config/debug/pagealloc.h) \
    $(wildcard include/config/hibernation.h) \
    $(wildcard include/config/use/user/accessible/timers.h) \
    $(wildcard include/config/hugetlbfs.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/gfp.h \
    $(wildcard include/config/cma.h) \
    $(wildcard include/config/zone/dma.h) \
    $(wildcard include/config/zone/dma32.h) \
    $(wildcard include/config/pm/sleep.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/mmzone.h \
    $(wildcard include/config/force/max/zoneorder.h) \
    $(wildcard include/config/memory/hotplug.h) \
    $(wildcard include/config/flat/node/mem/map.h) \
    $(wildcard include/config/cgroup/mem/res/ctlr.h) \
    $(wildcard include/config/no/bootmem.h) \
    $(wildcard include/config/have/memory/present.h) \
    $(wildcard include/config/have/memoryless/nodes.h) \
    $(wildcard include/config/need/node/memmap/size.h) \
    $(wildcard include/config/have/memblock/node.h) \
    $(wildcard include/config/need/multiple/nodes.h) \
    $(wildcard include/config/sparsemem/extreme.h) \
    $(wildcard include/config/nodes/span/other/nodes.h) \
    $(wildcard include/config/holes/in/zone.h) \
    $(wildcard include/config/arch/has/holes/memorymodel.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/numa.h \
    $(wildcard include/config/nodes/shift.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/nodemask.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/pageblock-flags.h \
    $(wildcard include/config/hugetlb/page.h) \
    $(wildcard include/config/hugetlb/page/size/variable.h) \
  include/generated/bounds.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/memory_hotplug.h \
    $(wildcard include/config/memory/hotremove.h) \
    $(wildcard include/config/have/arch/nodedata/extension.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/notifier.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/srcu.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/topology.h \
    $(wildcard include/config/sched/smt.h) \
    $(wildcard include/config/sched/mc.h) \
    $(wildcard include/config/sched/book.h) \
    $(wildcard include/config/use/percpu/numa/node/id.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/topology.h \
    $(wildcard include/config/arm/cpu/topology.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/asm-generic/topology.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/mmdebug.h \
    $(wildcard include/config/debug/vm.h) \
    $(wildcard include/config/debug/virtual.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/debug_locks.h \
    $(wildcard include/config/debug/locking/api/selftests.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/range.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/bit_spinlock.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/shrinker.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/pgtable.h \
    $(wildcard include/config/highpte.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/proc-fns.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/glue-proc.h \
    $(wildcard include/config/cpu/arm610.h) \
    $(wildcard include/config/cpu/arm7tdmi.h) \
    $(wildcard include/config/cpu/arm710.h) \
    $(wildcard include/config/cpu/arm720t.h) \
    $(wildcard include/config/cpu/arm740t.h) \
    $(wildcard include/config/cpu/arm9tdmi.h) \
    $(wildcard include/config/cpu/arm920t.h) \
    $(wildcard include/config/cpu/arm922t.h) \
    $(wildcard include/config/cpu/arm925t.h) \
    $(wildcard include/config/cpu/arm926t.h) \
    $(wildcard include/config/cpu/arm940t.h) \
    $(wildcard include/config/cpu/arm946e.h) \
    $(wildcard include/config/cpu/arm1020.h) \
    $(wildcard include/config/cpu/arm1020e.h) \
    $(wildcard include/config/cpu/arm1022.h) \
    $(wildcard include/config/cpu/arm1026.h) \
    $(wildcard include/config/cpu/mohawk.h) \
    $(wildcard include/config/cpu/feroceon.h) \
    $(wildcard include/config/cpu/v6k.h) \
    $(wildcard include/config/cpu/v7.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/asm-generic/pgtable-nopud.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/pgtable-hwdef.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/pgtable-2level-hwdef.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/pgtable-2level.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/asm-generic/pgtable.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/page-flags.h \
    $(wildcard include/config/pageflags/extended.h) \
    $(wildcard include/config/arch/uses/pg/uncached.h) \
    $(wildcard include/config/memory/failure.h) \
    $(wildcard include/config/swap.h) \
    $(wildcard include/config/s390.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/huge_mm.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/vmstat.h \
    $(wildcard include/config/vm/event/counters.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/vm_event_item.h \
    $(wildcard include/config/migration.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/seq_file.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/trace_seq.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/fs.h \
    $(wildcard include/config/sysfs.h) \
    $(wildcard include/config/fs/posix/acl.h) \
    $(wildcard include/config/security.h) \
    $(wildcard include/config/quota.h) \
    $(wildcard include/config/fsnotify.h) \
    $(wildcard include/config/ima.h) \
    $(wildcard include/config/fs/encryption.h) \
    $(wildcard include/config/epoll.h) \
    $(wildcard include/config/debug/writecount.h) \
    $(wildcard include/config/file/locking.h) \
    $(wildcard include/config/auditsyscall.h) \
    $(wildcard include/config/block.h) \
    $(wildcard include/config/fs/xip.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/limits.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/ioctl.h \
  arch/arm/include/generated/asm/ioctl.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/asm-generic/ioctl.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/blk_types.h \
    $(wildcard include/config/blk/dev/integrity.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/kdev_t.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/dcache.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/rculist.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/rculist_bl.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/list_bl.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/path.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/stat.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/stat.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/radix-tree.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/pid.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/semaphore.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/fiemap.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/migrate_mode.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/nfs_fs_i.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/fcntl.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/fcntl.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/asm-generic/fcntl.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/err.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/hardirq.h \
    $(wildcard include/config/generic/hardirqs.h) \
    $(wildcard include/config/virt/cpu/accounting.h) \
    $(wildcard include/config/irq/time/accounting.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/ftrace_irq.h \
    $(wildcard include/config/ftrace/nmi/enter.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/hardirq.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/irq.h \
    $(wildcard include/config/sparse/irq.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/irq_cpustat.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/perf_event.h \
    $(wildcard include/config/cgroup/perf.h) \
    $(wildcard include/config/event/tracing.h) \
    $(wildcard include/config/function/tracer.h) \
    $(wildcard include/config/cpu/sup/intel.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/cgroup.h \
    $(wildcard include/config/cgroups.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/sched.h \
    $(wildcard include/config/sched/debug.h) \
    $(wildcard include/config/no/hz.h) \
    $(wildcard include/config/lockup/detector.h) \
    $(wildcard include/config/detect/hung/task.h) \
    $(wildcard include/config/core/dump/default/elf/headers.h) \
    $(wildcard include/config/sched/autogroup.h) \
    $(wildcard include/config/bsd/process/acct.h) \
    $(wildcard include/config/taskstats.h) \
    $(wildcard include/config/audit.h) \
    $(wildcard include/config/android/lmk/adj/rbtree.h) \
    $(wildcard include/config/inotify/user.h) \
    $(wildcard include/config/fanotify.h) \
    $(wildcard include/config/posix/mqueue.h) \
    $(wildcard include/config/schedstats.h) \
    $(wildcard include/config/task/delay/acct.h) \
    $(wildcard include/config/fair/group/sched.h) \
    $(wildcard include/config/rt/group/sched.h) \
    $(wildcard include/config/cgroup/sched.h) \
    $(wildcard include/config/blk/dev/io/trace.h) \
    $(wildcard include/config/rcu/boost.h) \
    $(wildcard include/config/compat/brk.h) \
    $(wildcard include/config/cc/stackprotector.h) \
    $(wildcard include/config/rt/mutexes.h) \
    $(wildcard include/config/task/xacct.h) \
    $(wildcard include/config/cpusets.h) \
    $(wildcard include/config/futex.h) \
    $(wildcard include/config/fault/injection.h) \
    $(wildcard include/config/latencytop.h) \
    $(wildcard include/config/function/graph/tracer.h) \
    $(wildcard include/config/have/unstable/sched/clock.h) \
    $(wildcard include/config/cfs/bandwidth.h) \
    $(wildcard include/config/debug/stack/usage.h) \
    $(wildcard include/config/android/bg/scan/mem.h) \
  arch/arm/include/generated/asm/cputime.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/asm-generic/cputime.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/signal.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/proportions.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/seccomp.h \
    $(wildcard include/config/seccomp.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/seccomp.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/rtmutex.h \
    $(wildcard include/config/debug/rt/mutexes.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/plist.h \
    $(wildcard include/config/debug/pi/list.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/resource.h \
  arch/arm/include/generated/asm/resource.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/asm-generic/resource.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/hrtimer.h \
    $(wildcard include/config/high/res/timers.h) \
    $(wildcard include/config/timerfd.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/timerqueue.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/task_io_accounting.h \
    $(wildcard include/config/task/io/accounting.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/latencytop.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/cred.h \
    $(wildcard include/config/debug/credentials.h) \
    $(wildcard include/config/user/ns.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/selinux.h \
    $(wildcard include/config/security/selinux.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/llist.h \
    $(wildcard include/config/arch/have/nmi/safe/cmpxchg.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/aio.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/uio.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/cgroupstats.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/taskstats.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/prio_heap.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/idr.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/cgroup_subsys.h \
    $(wildcard include/config/cgroup/debug.h) \
    $(wildcard include/config/cgroup/cpuacct.h) \
    $(wildcard include/config/cgroup/device.h) \
    $(wildcard include/config/cgroup/freezer.h) \
    $(wildcard include/config/net/cls/cgroup.h) \
    $(wildcard include/config/blk/cgroup.h) \
    $(wildcard include/config/netprio/cgroup.h) \
    $(wildcard include/config/cgroup/bfqio.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/perf_event.h \
  arch/arm/include/generated/asm/local64.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/asm-generic/local64.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/pid_namespace.h \
    $(wildcard include/config/pid/ns.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/nsproxy.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/kref.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/ftrace.h \
    $(wildcard include/config/dynamic/ftrace.h) \
    $(wildcard include/config/stack/tracer.h) \
    $(wildcard include/config/frame/pointer.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/trace_clock.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/kallsyms.h \
    $(wildcard include/config/kallsyms.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/ftrace.h \
    $(wildcard include/config/old/mcount.h) \
    $(wildcard include/config/arm/unwind.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/cpu.h \
    $(wildcard include/config/arch/has/cpu/autoprobe.h) \
    $(wildcard include/config/arch/cpu/probe/release.h) \
    $(wildcard include/config/pm/sleep/smp.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/node.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/device.h \
    $(wildcard include/config/debug/devres.h) \
    $(wildcard include/config/pinctrl.h) \
    $(wildcard include/config/devtmpfs.h) \
    $(wildcard include/config/sysfs/deprecated.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/ioport.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/kobject.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/sysfs.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/kobject_ns.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/klist.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/pinctrl/devinfo.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/pm.h \
    $(wildcard include/config/pm.h) \
    $(wildcard include/config/pm/runtime.h) \
    $(wildcard include/config/pm/clk.h) \
    $(wildcard include/config/pm/generic/domains.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/device.h \
    $(wildcard include/config/dmabounce.h) \
    $(wildcard include/config/iommu/api.h) \
    $(wildcard include/config/arm/dma/use/iommu.h) \
    $(wildcard include/config/arch/omap.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/pm_wakeup.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/irq_work.h \
  arch/arm/include/generated/asm/local.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/asm-generic/local.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/proc_fs.h \
    $(wildcard include/config/proc/devicetree.h) \
    $(wildcard include/config/proc/kcore.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/slab.h \
    $(wildcard include/config/slab/debug.h) \
    $(wildcard include/config/failslab.h) \
    $(wildcard include/config/slub.h) \
    $(wildcard include/config/slob.h) \
    $(wildcard include/config/debug/slab.h) \
    $(wildcard include/config/slab.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/slub_def.h \
    $(wildcard include/config/slub/stats.h) \
    $(wildcard include/config/slub/debug.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/kmemleak.h \
    $(wildcard include/config/debug/kmemleak.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/magic.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/kmod.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/module.h \
    $(wildcard include/config/unused/symbols.h) \
    $(wildcard include/config/module/unload.h) \
    $(wildcard include/config/constructors.h) \
    $(wildcard include/config/debug/set/module/ronx.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/elf.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/elf-em.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/elf.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/user.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/moduleparam.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/include/linux/export.h \
    $(wildcard include/config/symbol/prefix.h) \
    $(wildcard include/config/modversions.h) \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/module.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/uaccess.h \
  /home/DECODER/Downloads/Kernel/AGNi_pureMIUI-AGNi_N_dior/arch/arm/include/asm/unified.h \
    $(wildcard include/config/arm/asm/unified.h) \

fs/filesystems.o: $(deps_fs/filesystems.o)

$(deps_fs/filesystems.o):
