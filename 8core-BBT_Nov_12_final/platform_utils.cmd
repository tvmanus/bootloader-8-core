/******************************************************************************
 * Copyright (c) 2010-2011 Texas Instruments Incorporated - http://www.ti.com
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the   
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 *****************************************************************************/
/*
 *  Linker command file
 *
 */

-c
-heap  0x20000000	//0x41000
-stack 0xa000

/* Memory Map 1 - the default */
/*MEMORY
{
    L1PSRAM (RWX)  : org = 0x0E00000, len = 0x7FFF
    L1DSRAM (RWX)  : org = 0x0F00000, len = 0x7FFF 

    L2SRAM (RWX)   : org = 0x0800000, len = 0x080000
    MSMCSRAM (RWX) : org = 0xc000000, len = 0x400000
    DDR3 (RWX)     : org = 0x80000000,len = 0x10000000
}
*/
SECTIONS
{
    .csl_vect   >       DDR3
    .text       >       DDR3
    GROUP (NEAR_DP)
    {
    .neardata
    .rodata 
    .bss
    } load > DDR3
    .stack      >       DDR3
    .cinit      >       DDR3
    .cio        >       DDR3
    .const      >       DDR3
    .data       >       DDR3
    .switch     >       DDR3
    .sysmem     >       DDR3
    .far        >       DDR3
    .testMem    >       DDR3
    .fardata    >       DDR3
    platform_lib > 		MSMCSRAM
}
SECTIONS
{
    .init_array:    load >> DDR3
    .srioSharedMem: load >> DDR3
    .qmss:          load >> DDR3
    .cppi:          load >> DDR3
    srio_mem        load >> DDR3
    sriomem_entry	load >> DDR3
    //.csl_vect:		load >> L2SRAM
    //platform_lib	load >> L2SRAM
}


