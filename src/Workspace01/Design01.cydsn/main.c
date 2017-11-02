/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include <stdio.h>
#include <stdlib.h>

#define USBFS_DEVICE    (0u)

uint32 ReadShift;
uint32 flag = 0;

/*******************************************************************************
* Define Interrupt service routine and allocate an vector to the Interrupt
********************************************************************************/
CY_ISR(InterruptHandler)
{
	/* Read Status register in order to clear the sticky Terminal Count (TC) bit 
	 * in the status register. Note that the function is not called, but rather 
	 * the status is read directly.
	 */
    HighCheck50us_STATUS;
    
	/* Increment the Counter to indicate the keep track of the number of 
     * interrupts received */
    ReadShift = ShiftReg_1_ReadRegValue();
    flag = 1;    
}


int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    Comp_1_Start();
    Comp_2_Start();
    ShiftReg_1_Start();
    HighCheck50us_Start();
    isr_1_StartEx(InterruptHandler);
    isr_1_Enable();

    /* Start USBFS operation with 5-V operation. */
    USBUART_1_Start(USBFS_DEVICE, USBUART_1_5V_OPERATION);
    
    for(;;)
    {                                 
       /* Host can send double SET_INTERFACE request. */
        if (0u != USBUART_1_IsConfigurationChanged())
        {
            /* Initialize IN endpoints when device is configured. */
            if (0u != USBUART_1_GetConfiguration())
            {
                /* Enumeration is done, enable OUT endpoint to receive data 
                 * from host. */
                USBUART_1_CDC_Init();
            }
        }

        /* Service USB CDC when device is configured. */
        if (0u != USBUART_1_GetConfiguration())
        {
            /* Check for input data from host. */
            if (0u != USBUART_1_DataIsReady())
            {
                /* Read received data and re-enable OUT endpoint. */
                /*count = USBUART_1_GetAll(buffer);*/
            }

            /* Wait until component is ready to send data to host. */
            if (USBUART_1_CDCIsReady())
            {
                if (flag) 
                {
                    char buf[256];
                    int32 val = ReadShift > 0x100000 ? -(ReadShift - 0x100000) : ReadShift;
                    sprintf(buf,"%ld\r\n",val);
                    USBUART_1_PutData((unsigned char *)buf, strlen(buf));
                    flag = 0;
                }
            }            
        }
    }
}


