/*
 * Do not modify this file; it is automatically generated from the template
 * linkcmd.xdt in the ti.targets.elf package and will be overwritten.
 */

/*
 * put '"'s around paths because, without this, the linker
 * considers '-' as minus operator, not a file name character.
 */


-l"D:\HW_8CORE_BBT\8core-BBT_Nov_12_final\Debug\configPkg\package\cfg\8core-BBT_pe66.oe66"
-l"D:\TInew\ipc_1_24_03_32\packages\ti\sdo\ipc\lib\instrumented_e66\ipc\ipc.lib"
-l"D:\TInew\pdk_C6678_1_1_2_6\packages\ti\drv\srio\lib\ti.drv.srio.ae66"
-l"D:\TInew\pdk_C6678_1_1_2_6\packages\ti\drv\cppi\lib\ti.drv.cppi.ae66"
-l"D:\TInew\pdk_C6678_1_1_2_6\packages\ti\drv\qmss\lib\ti.drv.qmss.ae66"
-l"D:\TInew\pdk_C6678_1_1_2_6\packages\ti\csl\lib\ti.csl.ae66"
-l"D:\TInew\bios_6_33_06_50\packages\ti\sysbios\lib\instrumented_e66\sysbios\sysbios.lib"
-l"D:\TInew\xdctools_3_23_03_53\packages\ti\targets\rts6000\lib\ti.targets.rts6000.ae66"
-l"D:\TInew\xdctools_3_23_03_53\packages\ti\targets\rts6000\lib\boot.ae66"

--retain="*(xdc.meta)"


--args 0x0
-heap  0x0
-stack 0x1000

MEMORY
{
    L2SRAM (RWX) : org = 0x800000, len = 0x80000
    MSMCSRAM (RWX) : org = 0xc000000, len = 0x400000
    DDR3 (RWX) : org = 0x80000000, len = 0x10000000
    SRIOMEM (RWX) : org = 0x90000000, len = 0x100
}

/*
 * Linker command file contributions from all loaded packages:
 */

/* Content from xdc.services.global (null): */

/* Content from xdc (null): */

/* Content from xdc.corevers (null): */

/* Content from xdc.shelf (null): */

/* Content from xdc.services.spec (null): */

/* Content from xdc.services.intern.xsr (null): */

/* Content from xdc.services.intern.gen (null): */

/* Content from xdc.services.intern.cmd (null): */

/* Content from xdc.bld (null): */

/* Content from ti.targets (null): */

/* Content from ti.targets.elf (null): */

/* Content from xdc.rov (null): */

/* Content from xdc.runtime (null): */

/* Content from ti.targets.rts6000 (null): */

/* Content from ti.sysbios.interfaces (null): */

/* Content from ti.sysbios.family (null): */

/* Content from ti.sysbios (null): */

/* Content from xdc.services.getset (null): */

/* Content from ti.sysbios.hal (null): */

/* Content from ti.sysbios.knl (null): */

/* Content from ti.csl (null): */

/* Content from ti.drv.qmss (null): */

/* Content from ti.drv.cppi (null): */

/* Content from ti.drv.srio (null): */

/* Content from ti.sysbios.gates (null): */

/* Content from ti.sysbios.heaps (null): */

/* Content from xdc.runtime.knl (null): */

/* Content from ti.sdo.ipc.interfaces (null): */

/* Content from ti.sysbios.syncs (null): */

/* Content from ti.sdo.ipc.family (null): */

/* Content from ti.sdo.utils (null): */

/* Content from ti.sysbios.family.c66 (null): */

/* Content from ti.sysbios.family.c64p (null): */

/* Content from ti.sysbios.family.c66.tci66xx (null): */

/* Content from ti.sysbios.xdcruntime (null): */

/* Content from ti.sysbios.family.c62 (null): */

/* Content from ti.sysbios.timers.timer64 (null): */

/* Content from ti.sysbios.family.c64p.tci6488 (null): */

/* Content from ti.sysbios.utils (null): */

/* Content from ti.catalog.c6000 (null): */

/* Content from ti.catalog (null): */

/* Content from ti.catalog.peripherals.hdvicp2 (null): */

/* Content from xdc.platform (null): */

/* Content from xdc.cfg (null): */

/* Content from ti.platforms.generic (null): */

/* Content from ti.platforms.evm6678 (null): */

/* Content from ti.sdo.ipc.heaps (null): */

/* Content from ti.sdo.ipc (ti/sdo/ipc/linkcmd.xdt): */

SECTIONS
{
    ti.sdo.ipc.SharedRegion_0:  { . += 0x100000;} run > 0xc010000, type = NOLOAD
}


/* Content from ti.sdo.ipc.family.c647x (null): */

/* Content from ti.sdo.ipc.notifyDrivers (null): */

/* Content from ti.sdo.ipc.transports (null): */

/* Content from ti.sdo.ipc.nsremote (null): */

/* Content from ti.sdo.ipc.gates (null): */

/* Content from configPkg (null): */


/*
 * symbolic aliases for static instance objects
 */
xdc_runtime_Startup__EXECFXN__C = 1;
xdc_runtime_Startup__RESETFXN__C = 1;
TSK_idle = ti_sysbios_knl_Task_Object__table__V + 0;

SECTIONS
{
    .text: load >> L2SRAM
    .ti.decompress: load > L2SRAM
    .stack: load > L2SRAM
    GROUP: load > DDR3
    {
        .bss:
        .neardata:
        .rodata:
    }
    .cinit: load > DDR3
    .pinit: load >> DDR3
    .init_array: load > DDR3
    .const: load >> DDR3
    .data: load >> DDR3
    .fardata: load >> DDR3
    .switch: load >> DDR3
    .sysmem: load > DDR3
    .far: load >> DDR3
    .args: load > DDR3 align = 0x4, fill = 0 {_argsize = 0x0; }
    .cio: load >> DDR3
    .ti.handler_table: load > DDR3
    systemHeap: load >> L2SRAM
    .vecs: load >> L2SRAM
    xdc.meta: load >> DDR3, type = COPY

}
