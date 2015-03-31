/*----------------------------------------------------------------------------- 
* This file is part of the Colony.Core Project.  The Colony.Core Project is an   
* open source project with a BSD type of licensing agreement.  See the license  
* agreement (license.txt) in the top/ directory or on the Internet at           
* http://integerfox.com/colony.core/license.txt
*                                                                               
* Copyright (c) 2014, 2015  John T. Taylor                                        
*                                                                               
* Redistributions of the source code must retain the above copyright notice.    
*----------------------------------------------------------------------------*/ 

#include "Bsp/Api.h"


/* Busy Wait interval/delay */     
#define _WAIT_INTERVAL      10000
   

/////////////////////////////////////
uint8_t BSP_uartInit( uint8_t sciPortID, uint8_t pinSelect, uint8_t irqPriority, uint8_t baudrate, uint8_t baudrateDivider, uint8_t frameConfig )
    {
    // Clear the Control registers 
    BSP_SCI_INDEX_TO_INSTANCE(sciPortID).SCR.BYTE      = 0;
    BSP_SCI_INDEX_TO_INSTANCE(sciPortID).SCMR.BIT.SMIF = 0;
    BSP_SCI_INDEX_TO_INSTANCE(sciPortID).SEMR.BIT.ABCS = 0;

    // Config the RX Input pin (is microcontoller package specific)
    BSP_uartInitPin_( sciPortID, pinSelect ); 
    
        
    // Enable the SCI Module and set IRQ priority
    switch( sciPortID )
        {
        // This is an error! 
        default:
            return 0;
            // this is NOT a fall through case!

        case 0:
	        MSTP( SCI0 )     = 0;             // Enable the Channel
	        IPR( SCI0,RXI0 ) = irqPriority;   // Set IRQ priority (all interrupts for a SCI port have the same IRQ priority);
            break;

        case 1:
	        MSTP( SCI1 )     = 0;             // Enable the Channel
	        IPR( SCI1,RXI1 ) = irqPriority;   // Set IRQ priority (all interrupts for a SCI port have the same IRQ priority);
            break;

        case 2:
	        MSTP( SCI2 )     = 0;             // Enable the Channel
	        IPR( SCI2,RXI2 ) = irqPriority;   // Set IRQ priority (all interrupts for a SCI port have the same IRQ priority);
            break;

        case 3:
	        MSTP( SCI3 )     = 0;             // Enable the Channel
	        IPR( SCI3,RXI3 ) = irqPriority;   // Set IRQ priority (all interrupts for a SCI port have the same IRQ priority);
            break;


        case 5:
	        MSTP( SCI5 )     = 0;             // Enable the Channel
	        IPR( SCI5,RXI5 ) = irqPriority;   // Set IRQ priority (all interrupts for a SCI port have the same IRQ priority);
            break;

        case 6:
	        MSTP( SCI6 )     = 0;             // Enable the Channel
	        IPR( SCI6,RXI6 ) = irqPriority;   // Set IRQ priority (all interrupts for a SCI port have the same IRQ priority);
            break;              
        }

    // Set Baudrate and frame
    BSP_SCI_INDEX_TO_INSTANCE(sciPortID).SMR.BYTE = frameConfig + baudrateDivider;
    BSP_SCI_INDEX_TO_INSTANCE(sciPortID).BRR      = baudrate;

    // Need to wait at least 1 bit interval (per the data sheet)
    Bsp_uartBusyWait( OPTION_BSP_UARTS_WAIT_INTERVAL );
    return 1;
    }

void Bsp_uartBusyWait( unsigned long delay )
    {
    unsigned long wait;

    for(wait=delay; wait; wait--)
        Bsp_Api_nop();
    }


uint8_t BSP_uartClrReceivedFlag( uint8_t sciPortID )
    {
    switch( sciPortID )
        {
        // This is an error! 
        default:
            return 0;
            // this is NOT a fall through case!

        case 0:
	        IR( SCI0, RXI0 ) = 0; 
            break;

        case 1:
	        IR( SCI1, RXI1 ) = 0; 
            break;

        case 2:
	        IR( SCI2, RXI2 ) = 0; 
            break;

        case 3:
	        IR( SCI3, RXI3 ) = 0; 
            break;

        case 5:
	        IR( SCI5, RXI5 ) = 0; 
            break;

        case 6:
	        IR( SCI6, RXI6 ) = 0; 
            break;
        }

    return 1;
    }



uint8_t BSP_uartClrTxDataEmptyFlag( uint8_t sciPortID )
    {
    switch( sciPortID )
        {
        // This is an error! 
        default:
            return 0;
            // this is NOT a fall through case!

        case 0:
	        IR( SCI0, TXI0 ) = 0; 
            break;

        case 1:
	        IR( SCI1, TXI1 ) = 0; 
            break;

        case 2:
	        IR( SCI2, TXI2 ) = 0; 
            break;

        case 3:
	        IR( SCI3, TXI3 ) = 0; 
            break;

        case 5:
	        IR( SCI5, TXI5 ) = 0; 
            break;

        case 6:
	        IR( SCI6, TXI6 ) = 0; 
            break;
        }

    return 1;
    }

