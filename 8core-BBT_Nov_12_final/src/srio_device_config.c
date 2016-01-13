/* SRIO Driver Includes. */
#include <ti/drv/srio/srio_types.h>
#include <ti/drv/srio/include/listlib.h>
#include <ti/drv/srio/srio_drv.h>

/* CSL SRIO Functional Layer */
#include <ti/csl/csl_srio.h>
#include <ti/csl/csl_srioAux.h>
#include <ti/csl/csl_srioAuxPhyLayer.h>

/* CSL BootCfg Module */
#include <ti/csl/csl_bootcfg.h>
#include <ti/csl/csl_bootcfgAux.h>

/* CSL Chip Functional Layer */
#include <ti/csl/csl_chip.h>

/* CSL PSC Module */
#include <ti/csl/csl_pscAux.h>

/* QMSS Include */
#include <ti/drv/qmss/qmss_drv.h>

#include"srioloopback.h"

/**********************************************************************
 ************************* LOCAL Definitions **************************
 **********************************************************************/

/* These are the GARBAGE queues which are used by the TXU to dump the
 * descriptor if there is an error instead of recycling the descriptor
 * to the free queue. */
#define GARBAGE_LEN_QUEUE		    905
#define GARBAGE_TOUT_QUEUE		    906
#define GARBAGE_RETRY_QUEUE		    907
#define GARBAGE_TRANS_ERR_QUEUE	    908
#define GARBAGE_PROG_QUEUE		    909
#define GARBAGE_SSIZE_QUEUE		    910

/* SRIO Device Information
 * - 16 bit Device Identifier.
 * - 8 bit Device Identifier.
 * - Vendor Identifier.
 * - Device Revision. */
#define DEVICE_VENDOR_ID            0x30
#define DEVICE_REVISION             0x0

/* SRIO Assembly Information
 * - Assembly Identifier
 * - Assembly Vendor Identifier.
 * - Assembly Device Revision.
 * - Assembly Extension Features */
#define DEVICE_ASSEMBLY_ID          0x0
#define DEVICE_ASSEMBLY_VENDOR_ID   0x30
#define DEVICE_ASSEMBLY_REVISION    0x0
#define DEVICE_ASSEMBLY_INFO        0x0100

/**********************************************************************
 ************************* Extern Definitions *************************
 **********************************************************************/

extern const uint32_t DEVICE_ID1_16BIT;
extern const uint32_t DEVICE_ID1_8BIT;
extern const uint32_t DEVICE_ID2_16BIT;
extern const uint32_t DEVICE_ID2_8BIT;
extern const uint32_t DEVICE_ID3_16BIT;
extern const uint32_t DEVICE_ID3_8BIT_ID;
extern const uint32_t DEVICE_ID4_16BIT;
extern const uint32_t DEVICE_ID4_8BIT_ID;

/**********************************************************************
 *********************** DEVICE SRIO FUNCTIONS ***********************
 **********************************************************************/

/** @addtogroup SRIO_DEVICE_API
 @{ */

/**
 *  @b Description
 *  @n
 *      The function provides the initialization sequence for the SRIO IP
 *      block. This can be modified by customers for their application and
 *      configuration.
 *
 *  @retval
 *      Success     -   0
 *  @retval
 *      Error       -   <0
 */
#pragma CODE_SECTION(SrioDevice_init, ".text:SrioDevice_init");
int32_t SrioDevice_init (uint8_t PortNo,uint8_t datarate)
{
    CSL_SrioHandle      hSrio;
	int32_t             i;
    SRIO_PE_FEATURES    peFeatures;
    SRIO_OP_CAR         opCar;
    Qmss_QueueHnd       queueHnd;
    uint8_t             isAllocated;
    uint32_t            gargbageQueue[] = { GARBAGE_LEN_QUEUE,  GARBAGE_TOUT_QUEUE,
                                            GARBAGE_RETRY_QUEUE,GARBAGE_TRANS_ERR_QUEUE,
                                            GARBAGE_PROG_QUEUE, GARBAGE_SSIZE_QUEUE };

    /* Get the CSL SRIO Handle. */
    hSrio = CSL_SRIO_Open (0);
    if (hSrio == NULL)
        return -1;

    /* Code to disable SRIO reset isolation */
    if (CSL_PSC_isModuleResetIsolationEnabled(CSL_PSC_LPSC_SRIO))
        CSL_PSC_disableModuleResetIsolation(CSL_PSC_LPSC_SRIO);

    /* Disable the SRIO Global block */
   	CSL_SRIO_GlobalDisable (hSrio);

   	/* Disable each of the individual SRIO blocks. */
   	for(i = 0; i <= 9; i++)
   		CSL_SRIO_DisableBlock(hSrio, i);

    /* Set boot complete to be 0; we are not done with the initialization. */
	CSL_SRIO_SetBootComplete(hSrio, 0);

    /* Now enable the SRIO block and all the individual blocks also. */
    CSL_SRIO_GlobalEnable (hSrio);
    for(i = 0; i <= 9; i++)
        CSL_SRIO_EnableBlock(hSrio,i);

    /* Configure SRIO ports to operate in loopback mode. */
    CSL_SRIO_SetNormalMode(hSrio, 0);
    CSL_SRIO_SetNormalMode(hSrio, 1);
    CSL_SRIO_SetNormalMode(hSrio, 2);
    CSL_SRIO_SetNormalMode(hSrio, 3);

	/* Enable Automatic Priority Promotion of response packets. */
	CSL_SRIO_EnableAutomaticPriorityPromotion(hSrio);

	/* Set the SRIO Prescalar select to operate in the range of 44.7 to 89.5 */
	CSL_SRIO_SetPrescalarSelect (hSrio, 0);

    /* Unlock the Boot Configuration Kicker */
    CSL_BootCfgUnlockKicker ();

    /* Assuming the link rate is 3125; program the PLL accordingly. *///A:quater rate  (2.5gbps) 9: half(5gbps) B:eighth rate (1.25gbps)
    switch(datarate)
    {
    	case SRIO_DATARATE_1250:

			    CSL_BootCfgSetSRIOSERDESConfigPLL (0x241); //8x         		//0x229 -5x half rate
    			/* Configure the SRIO SERDES Receive Configuration. */
    		    CSL_BootCfgSetSRIOSERDESRxConfig (0, 0x004404B5);
    		   	CSL_BootCfgSetSRIOSERDESRxConfig (1, 0x004404B5);
    		    CSL_BootCfgSetSRIOSERDESRxConfig (2, 0x004404B5);
    		    CSL_BootCfgSetSRIOSERDESRxConfig (3, 0x004404B5);

    		    /* Configure the SRIO SERDES Transmit Configuration. */
    		    CSL_BootCfgSetSRIOSERDESTxConfig (0, 0x001807B5);
    		    CSL_BootCfgSetSRIOSERDESTxConfig (1, 0x001807B5);
    		    CSL_BootCfgSetSRIOSERDESTxConfig (2, 0x001807B5);
    		    CSL_BootCfgSetSRIOSERDESTxConfig (3, 0x001807B5);

    	break;
    	case SRIO_DATARATE_2500:

    	    	CSL_BootCfgSetSRIOSERDESConfigPLL (0x241);
    	    	/* Configure the SRIO SERDES Receive Configuration. */
    	    	CSL_BootCfgSetSRIOSERDESRxConfig (0, 0x004404A5);
    	    	CSL_BootCfgSetSRIOSERDESRxConfig (1, 0x004404A5);
    	    	CSL_BootCfgSetSRIOSERDESRxConfig (2, 0x004404A5);
    	    	CSL_BootCfgSetSRIOSERDESRxConfig (3, 0x004404A5);

    	    	/* Configure the SRIO SERDES Transmit Configuration. */
    	    	CSL_BootCfgSetSRIOSERDESTxConfig (0, 0x001807A5);
    	    	CSL_BootCfgSetSRIOSERDESTxConfig (1, 0x001807A5);
    	    	CSL_BootCfgSetSRIOSERDESTxConfig (2, 0x001807A5);
    	    	CSL_BootCfgSetSRIOSERDESTxConfig (3, 0x001807A5);

    	break;
    	case SRIO_DATARATE_3125:

    	      	CSL_BootCfgSetSRIOSERDESConfigPLL (0x229);
    	      	/* Configure the SRIO SERDES Receive Configuration. */
    	      	CSL_BootCfgSetSRIOSERDESRxConfig (0, 0x00440495);
    	      	CSL_BootCfgSetSRIOSERDESRxConfig (1, 0x00440495);
    	      	CSL_BootCfgSetSRIOSERDESRxConfig (2, 0x00440495);
    	      	CSL_BootCfgSetSRIOSERDESRxConfig (3, 0x00440495);

    	      	/* Configure the SRIO SERDES Transmit Configuration. */
    	      	CSL_BootCfgSetSRIOSERDESTxConfig (0, 0x00180795);
    	      	CSL_BootCfgSetSRIOSERDESTxConfig (1, 0x00180795);
    	      	CSL_BootCfgSetSRIOSERDESTxConfig (2, 0x00180795);
    	      	CSL_BootCfgSetSRIOSERDESTxConfig (3, 0x00180795);

    	break;
    	case SRIO_DATARATE_5000:

    			CSL_BootCfgSetSRIOSERDESConfigPLL (0x241);
    			/* Configure the SRIO SERDES Receive Configuration. */
    			CSL_BootCfgSetSRIOSERDESRxConfig (0, 0x00440495);
    			CSL_BootCfgSetSRIOSERDESRxConfig (1, 0x00440495);
    			CSL_BootCfgSetSRIOSERDESRxConfig (2, 0x00440495);
    			CSL_BootCfgSetSRIOSERDESRxConfig (3, 0x00440495);

    			/* Configure the SRIO SERDES Transmit Configuration. */
    			CSL_BootCfgSetSRIOSERDESTxConfig (0, 0x00180795);
    			CSL_BootCfgSetSRIOSERDESTxConfig (1, 0x00180795);
    			CSL_BootCfgSetSRIOSERDESTxConfig (2, 0x00180795);
    			CSL_BootCfgSetSRIOSERDESTxConfig (3, 0x00180795);

    	break;
    }

#ifndef SIMULATOR_SUPPORT
    /* Loop around till the SERDES PLL is not locked. */
    while (1)
    {
        uint32_t    status;
        /* Get the SRIO SERDES Status */
        CSL_BootCfgGetSRIOSERDESStatus(&status);
        if (status & 0x1)
            break;
    }
    #endif

    /* Clear the LSU pending interrupts. */
    CSL_SRIO_ClearLSUPendingInterrupt (hSrio, 0xFFFFFFFF, 0xFFFFFFFF);

    /* Set the Device Information */
    CSL_SRIO_SetDeviceInfo (hSrio, DEVICE_ID1_16BIT, DEVICE_VENDOR_ID, DEVICE_REVISION);

    /* Set the Assembly Information */
    CSL_SRIO_SetAssemblyInfo(hSrio, DEVICE_ASSEMBLY_ID, DEVICE_ASSEMBLY_VENDOR_ID,
                             DEVICE_ASSEMBLY_REVISION, DEVICE_ASSEMBLY_INFO);

    /* TODO: Configure the processing element features
     *  The SRIO RL file is missing the Re-transmit Suppression Support (Bit6) field definition */
    peFeatures.isBridge                          = 0;
    peFeatures.isEndpoint                        = 0;
    peFeatures.isProcessor                       = 1;
    peFeatures.isSwitch                          = 0;
    peFeatures.isMultiport                       = 0;
    peFeatures.isFlowArbiterationSupported       = 0;
    peFeatures.isMulticastSupported              = 0;
    peFeatures.isExtendedRouteConfigSupported    = 0;
    peFeatures.isStandardRouteConfigSupported    = 1;
    peFeatures.isFlowControlSupported            = 1;
    peFeatures.isCRFSupported                    = 0;
    peFeatures.isCTLSSupported                   = 1;
    peFeatures.isExtendedFeaturePtrValid         = 1;
    peFeatures.numAddressBitSupported            = 1;
    CSL_SRIO_SetProcessingElementFeatures (hSrio, &peFeatures);

    /* Configure the source operation CAR */
    memset ((void *) &opCar, 0, sizeof (opCar));
    opCar.portWriteOperationSupport = 1;
    opCar.atomicClearSupport        = 1;
    opCar.atomicSetSupport          = 1;
    opCar.atomicDecSupport          = 1;
    opCar.atomicIncSupport          = 1;
    opCar.atomicTestSwapSupport     = 1;
    opCar.doorbellSupport           = 1;
    opCar.dataMessageSupport        = 1;
    opCar.writeResponseSupport      = 1;
    opCar.streamWriteSupport        = 1;
    opCar.writeSupport              = 1;
    opCar.readSupport               = 1;
    opCar.dataStreamingSupport      = 1;
    CSL_SRIO_SetSourceOperationCAR (hSrio, &opCar);

    /* Configure the destination operation CAR */
	memset ((void *) &opCar, 0, sizeof (opCar));
    opCar.portWriteOperationSupport  = 1;
    opCar.doorbellSupport            = 1;
    opCar.dataMessageSupport         = 1;
    opCar.writeResponseSupport       = 1;
    opCar.streamWriteSupport         = 1;
    opCar.writeSupport               = 1;
    opCar.readSupport                = 1;
    CSL_SRIO_SetDestOperationCAR (hSrio, &opCar);

    /* Set the 16 bit and 8 bit identifier for the SRIO Device. */
    CSL_SRIO_SetDeviceIDCSR (hSrio, DEVICE_ID1_8BIT,DEVICE_ID1_16BIT);   // DEVICE_ID1_16BIT

    /* Enable TLM Base Routing Information for Maintainance Requests & ensure that
     * the BRR's can be used by all the ports. */
    CSL_SRIO_SetTLMPortBaseRoutingInfo(hSrio, PortNo, 1, 1, 1, 0);
    CSL_SRIO_SetTLMPortBaseRoutingInfo(hSrio, PortNo, 2, 1, 1, 0);
    CSL_SRIO_SetTLMPortBaseRoutingInfo(hSrio, PortNo, 3, 1, 1, 0);
    CSL_SRIO_SetTLMPortBaseRoutingInfo(hSrio, PortNo, 0, 1, 1, 0);

    /* Configure the Base Routing Register to ensure that all packets matching the
     * Device Identifier & the Secondary Device Id are admitted. */
    CSL_SRIO_SetTLMPortBaseRoutingPatternMatch(hSrio, PortNo, 1, DEVICE_ID2_16BIT, 0xFFFF);
    CSL_SRIO_SetTLMPortBaseRoutingPatternMatch(hSrio, PortNo, 2, DEVICE_ID3_16BIT, 0xFFFF);
    CSL_SRIO_SetTLMPortBaseRoutingPatternMatch(hSrio, PortNo, 3, DEVICE_ID4_16BIT, 0xFFFF);
    CSL_SRIO_SetTLMPortBaseRoutingPatternMatch(hSrio, PortNo, 0, DEVICE_ID2_8BIT,  0xFF);

    /* We need to open the Garbage collection queues in the QMSS. This is done to ensure that
     * these queues are not opened by another system entity. */
    for (i = 0; i < 6; i++)
    {
        /* Open the Garabage queues */
        queueHnd = Qmss_queueOpen (Qmss_QueueType_GENERAL_PURPOSE_QUEUE, gargbageQueue[i], &isAllocated);
        if (queueHnd < 0)
            return -1;

        /* Make sure the queue has not been opened already; we dont the queues to be shared by some other
         * entity in the system. */
        if (isAllocated > 1)
            return -1;
    }

    /* Set the Transmit Garbage Collection Information. */
    CSL_SRIO_SetTxGarbageCollectionInfo (hSrio, GARBAGE_LEN_QUEUE, GARBAGE_TOUT_QUEUE,
                                         GARBAGE_RETRY_QUEUE, GARBAGE_TRANS_ERR_QUEUE,
                                         GARBAGE_PROG_QUEUE, GARBAGE_SSIZE_QUEUE);

    /* Set the Host Device Identifier. */
    CSL_SRIO_SetHostDeviceID (hSrio, DEVICE_ID1_16BIT);

    /* Configure the component tag CSR */
    CSL_SRIO_SetCompTagCSR (hSrio, 0x00000000);

    /* Configure the PLM for all the ports. */
	for (i = 0; i < 4; i++)
	{
	    /* Set the PLM Port Silence Timer. */
        CSL_SRIO_SetPLMPortSilenceTimer (hSrio, i, 0x2);

        /* TODO: We need to ensure that the Port 0 is configured to support both
         * the 2x and 4x modes. The Port Width field is read only. So here we simply
         * ensure that the Input and Output ports are enabled. */
        CSL_SRIO_EnableInputPort (hSrio, i);
        CSL_SRIO_EnableOutputPort (hSrio, i);

        /* Set the PLM Port Discovery Timer. */
        CSL_SRIO_SetPLMPortDiscoveryTimer (hSrio, i, 0x2);

        /* Reset the Port Write Reception capture. */
        CSL_SRIO_SetPortWriteReceptionCapture(hSrio, i, 0x0);
    }

    /* Set the Port link timeout CSR */
    CSL_SRIO_SetPortLinkTimeoutCSR (hSrio, 0x000FFF);

    /* Set the Port General CSR: Only executing as Master Enable */
    CSL_SRIO_SetPortGeneralCSR (hSrio, 0, 1, 0);

    /* Clear the sticky register bits. */
    CSL_SRIO_SetLLMResetControl (hSrio, 1);

    /* Set the device id to be 0 for the Maintenance Port-Write operation
     * to report errors to a system host. */
    CSL_SRIO_SetPortWriteDeviceId (hSrio, 0x0, 0x0, 0x0);

    /* Set the Data Streaming MTU */
    CSL_SRIO_SetDataStreamingMTU (hSrio, 64);

    /* Configure the path mode for the ports. */
    for(i = 0; i < 4; i++)
        CSL_SRIO_SetPLMPortPathControlMode (hSrio,i, 0);

    /* Set the LLM Port IP Prescalar. */
    CSL_SRIO_SetLLMPortIPPrescalar (hSrio, 0x21);

    /* Enable the peripheral. */
    CSL_SRIO_EnablePeripheral(hSrio);

    /* Configuration has been completed. */
    CSL_SRIO_SetBootComplete(hSrio, 1);

#ifndef SIMULATOR_SUPPORT
    /* This code checks if the ports are operational or not. The functionality is not supported
     * on the simulator. */
	//for(i = 0; i < 4; i++)
    platform_delay(1000000);
    platform_write("Status of the port %d is 0x%X\n ",PortNo,hSrio->RIO_SP[PortNo].RIO_SP_ERR_STAT);
    while (CSL_SRIO_IsPortOk (hSrio, PortNo) != TRUE);
#endif

    /* Set all the queues 0 to operate at the same priority level and to send packets onto Port 0 */
    for (i =0 ; i < 16; i++)
        CSL_SRIO_SetTxQueueSchedInfo(hSrio, i,PortNo, 0);

    /* Set the Doorbell route to determine which routing table is to be used
     * This configuration implies that the Interrupt Routing Table is configured as
     * follows:-
     *  Interrupt Destination 0 - INTDST 16
     *  (0- value in ICRx in doorbelln_ICRR & doorbelln_ICRR2)
     *  Interrupt Destination 1 - INTDST 17
     *  Interrupt Destination 2 - INTDST 18
     *  Interrupt Destination 3 - INTDST 19
     */
    CSL_SRIO_SetDoorbellRoute(hSrio, 0); //dedicated doorbell interrupts

    /* Route the Doorbell interrupts.
     *  Doorbell Register 0 - All 16 Doorbits are routed to Interrupt Destination 0.
     *  Doorbell Register 1 - All 16 Doorbits are routed to Interrupt Destination 1.
     *  Doorbell Register 2 - All 16 Doorbits are routed to Interrupt Destination 2.
     *  Doorbell Register 3 - All 16 Doorbits are routed to Interrupt Destination 3. */
    for (i = 0; i < 16; i++)
    {
        CSL_SRIO_RouteDoorbellInterrupts(hSrio, 0, i, 0);
        CSL_SRIO_RouteDoorbellInterrupts(hSrio, 1, i, 1);
        CSL_SRIO_RouteDoorbellInterrupts(hSrio, 2, i, 2);
        CSL_SRIO_RouteDoorbellInterrupts(hSrio, 3, i, 3);
    }
    platform_write ("Debug(Core %d):SRIO device has initialized in normal mode\n ");
    /* Initialization has been completed. */
    return 0;
}

/**
@}
*/







