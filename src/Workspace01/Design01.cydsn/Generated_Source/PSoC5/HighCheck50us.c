/*******************************************************************************
* File Name: HighCheck50us.c  
* Version 3.0
*
*  Description:
*     The Counter component consists of a 8, 16, 24 or 32-bit counter with
*     a selectable period between 2 and 2^Width - 1.  
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "HighCheck50us.h"

uint8 HighCheck50us_initVar = 0u;


/*******************************************************************************
* Function Name: HighCheck50us_Init
********************************************************************************
* Summary:
*     Initialize to the schematic state
* 
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void HighCheck50us_Init(void) 
{
        #if (!HighCheck50us_UsingFixedFunction && !HighCheck50us_ControlRegRemoved)
            uint8 ctrl;
        #endif /* (!HighCheck50us_UsingFixedFunction && !HighCheck50us_ControlRegRemoved) */
        
        #if(!HighCheck50us_UsingFixedFunction) 
            /* Interrupt State Backup for Critical Region*/
            uint8 HighCheck50us_interruptState;
        #endif /* (!HighCheck50us_UsingFixedFunction) */
        
        #if (HighCheck50us_UsingFixedFunction)
            /* Clear all bits but the enable bit (if it's already set for Timer operation */
            HighCheck50us_CONTROL &= HighCheck50us_CTRL_ENABLE;
            
            /* Clear the mode bits for continuous run mode */
            #if (CY_PSOC5A)
                HighCheck50us_CONTROL2 &= ((uint8)(~HighCheck50us_CTRL_MODE_MASK));
            #endif /* (CY_PSOC5A) */
            #if (CY_PSOC3 || CY_PSOC5LP)
                HighCheck50us_CONTROL3 &= ((uint8)(~HighCheck50us_CTRL_MODE_MASK));                
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
            /* Check if One Shot mode is enabled i.e. RunMode !=0*/
            #if (HighCheck50us_RunModeUsed != 0x0u)
                /* Set 3rd bit of Control register to enable one shot mode */
                HighCheck50us_CONTROL |= HighCheck50us_ONESHOT;
            #endif /* (HighCheck50us_RunModeUsed != 0x0u) */
            
            /* Set the IRQ to use the status register interrupts */
            HighCheck50us_CONTROL2 |= HighCheck50us_CTRL2_IRQ_SEL;
            
            /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
            HighCheck50us_RT1 &= ((uint8)(~HighCheck50us_RT1_MASK));
            HighCheck50us_RT1 |= HighCheck50us_SYNC;     
                    
            /*Enable DSI Sync all all inputs of the Timer*/
            HighCheck50us_RT1 &= ((uint8)(~HighCheck50us_SYNCDSI_MASK));
            HighCheck50us_RT1 |= HighCheck50us_SYNCDSI_EN;

        #else
            #if(!HighCheck50us_ControlRegRemoved)
            /* Set the default compare mode defined in the parameter */
            ctrl = HighCheck50us_CONTROL & ((uint8)(~HighCheck50us_CTRL_CMPMODE_MASK));
            HighCheck50us_CONTROL = ctrl | HighCheck50us_DEFAULT_COMPARE_MODE;
            
            /* Set the default capture mode defined in the parameter */
            ctrl = HighCheck50us_CONTROL & ((uint8)(~HighCheck50us_CTRL_CAPMODE_MASK));
            
            #if( 0 != HighCheck50us_CAPTURE_MODE_CONF)
                HighCheck50us_CONTROL = ctrl | HighCheck50us_DEFAULT_CAPTURE_MODE;
            #else
                HighCheck50us_CONTROL = ctrl;
            #endif /* 0 != HighCheck50us_CAPTURE_MODE */ 
            
            #endif /* (!HighCheck50us_ControlRegRemoved) */
        #endif /* (HighCheck50us_UsingFixedFunction) */
        
        /* Clear all data in the FIFO's */
        #if (!HighCheck50us_UsingFixedFunction)
            HighCheck50us_ClearFIFO();
        #endif /* (!HighCheck50us_UsingFixedFunction) */
        
        /* Set Initial values from Configuration */
        HighCheck50us_WritePeriod(HighCheck50us_INIT_PERIOD_VALUE);
        #if (!(HighCheck50us_UsingFixedFunction && (CY_PSOC5A)))
            HighCheck50us_WriteCounter(HighCheck50us_INIT_COUNTER_VALUE);
        #endif /* (!(HighCheck50us_UsingFixedFunction && (CY_PSOC5A))) */
        HighCheck50us_SetInterruptMode(HighCheck50us_INIT_INTERRUPTS_MASK);
        
        #if (!HighCheck50us_UsingFixedFunction)
            /* Read the status register to clear the unwanted interrupts */
            (void)HighCheck50us_ReadStatusRegister();
            /* Set the compare value (only available to non-fixed function implementation */
            HighCheck50us_WriteCompare(HighCheck50us_INIT_COMPARE_VALUE);
            /* Use the interrupt output of the status register for IRQ output */
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            HighCheck50us_interruptState = CyEnterCriticalSection();
            
            HighCheck50us_STATUS_AUX_CTRL |= HighCheck50us_STATUS_ACTL_INT_EN_MASK;
            
            /* Exit Critical Region*/
            CyExitCriticalSection(HighCheck50us_interruptState);
            
        #endif /* (!HighCheck50us_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: HighCheck50us_Enable
********************************************************************************
* Summary:
*     Enable the Counter
* 
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects: 
*   If the Enable mode is set to Hardware only then this function has no effect 
*   on the operation of the counter.
*
*******************************************************************************/
void HighCheck50us_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (HighCheck50us_UsingFixedFunction)
        HighCheck50us_GLOBAL_ENABLE |= HighCheck50us_BLOCK_EN_MASK;
        HighCheck50us_GLOBAL_STBY_ENABLE |= HighCheck50us_BLOCK_STBY_EN_MASK;
    #endif /* (HighCheck50us_UsingFixedFunction) */  
        
    /* Enable the counter from the control register  */
    /* If Fixed Function then make sure Mode is set correctly */
    /* else make sure reset is clear */
    #if(!HighCheck50us_ControlRegRemoved || HighCheck50us_UsingFixedFunction)
        HighCheck50us_CONTROL |= HighCheck50us_CTRL_ENABLE;                
    #endif /* (!HighCheck50us_ControlRegRemoved || HighCheck50us_UsingFixedFunction) */
    
}


/*******************************************************************************
* Function Name: HighCheck50us_Start
********************************************************************************
* Summary:
*  Enables the counter for operation 
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Global variables:
*  HighCheck50us_initVar: Is modified when this function is called for the  
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void HighCheck50us_Start(void) 
{
    if(HighCheck50us_initVar == 0u)
    {
        HighCheck50us_Init();
        
        HighCheck50us_initVar = 1u; /* Clear this bit for Initialization */        
    }
    
    /* Enable the Counter */
    HighCheck50us_Enable();        
}


/*******************************************************************************
* Function Name: HighCheck50us_Stop
********************************************************************************
* Summary:
* Halts the counter, but does not change any modes or disable interrupts.
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects: If the Enable mode is set to Hardware only then this function
*               has no effect on the operation of the counter.
*
*******************************************************************************/
void HighCheck50us_Stop(void) 
{
    /* Disable Counter */
    #if(!HighCheck50us_ControlRegRemoved || HighCheck50us_UsingFixedFunction)
        HighCheck50us_CONTROL &= ((uint8)(~HighCheck50us_CTRL_ENABLE));        
    #endif /* (!HighCheck50us_ControlRegRemoved || HighCheck50us_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (HighCheck50us_UsingFixedFunction)
        HighCheck50us_GLOBAL_ENABLE &= ((uint8)(~HighCheck50us_BLOCK_EN_MASK));
        HighCheck50us_GLOBAL_STBY_ENABLE &= ((uint8)(~HighCheck50us_BLOCK_STBY_EN_MASK));
    #endif /* (HighCheck50us_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: HighCheck50us_SetInterruptMode
********************************************************************************
* Summary:
* Configures which interrupt sources are enabled to generate the final interrupt
*
* Parameters:  
*  InterruptsMask: This parameter is an or'd collection of the status bits
*                   which will be allowed to generate the counters interrupt.   
*
* Return: 
*  void
*
*******************************************************************************/
void HighCheck50us_SetInterruptMode(uint8 interruptsMask) 
{
    HighCheck50us_STATUS_MASK = interruptsMask;
}


/*******************************************************************************
* Function Name: HighCheck50us_ReadStatusRegister
********************************************************************************
* Summary:
*   Reads the status register and returns it's state. This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the status register
*
* Side Effects:
*   Status register bits may be clear on read. 
*
*******************************************************************************/
uint8   HighCheck50us_ReadStatusRegister(void) 
{
    return HighCheck50us_STATUS;
}


#if(!HighCheck50us_ControlRegRemoved)
/*******************************************************************************
* Function Name: HighCheck50us_ReadControlRegister
********************************************************************************
* Summary:
*   Reads the control register and returns it's state. This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the control register
*
*******************************************************************************/
uint8   HighCheck50us_ReadControlRegister(void) 
{
    return HighCheck50us_CONTROL;
}


/*******************************************************************************
* Function Name: HighCheck50us_WriteControlRegister
********************************************************************************
* Summary:
*   Sets the bit-field of the control register.  This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the control register
*
*******************************************************************************/
void    HighCheck50us_WriteControlRegister(uint8 control) 
{
    HighCheck50us_CONTROL = control;
}

#endif  /* (!HighCheck50us_ControlRegRemoved) */


#if (!(HighCheck50us_UsingFixedFunction && (CY_PSOC5A)))
/*******************************************************************************
* Function Name: HighCheck50us_WriteCounter
********************************************************************************
* Summary:
*   This funtion is used to set the counter to a specific value
*
* Parameters:  
*  counter:  New counter value. 
*
* Return: 
*  void 
*
*******************************************************************************/
void HighCheck50us_WriteCounter(uint16 counter) \
                                   
{
    #if(HighCheck50us_UsingFixedFunction)
        /* assert if block is already enabled */
        CYASSERT (0u == (HighCheck50us_GLOBAL_ENABLE & HighCheck50us_BLOCK_EN_MASK));
        /* If block is disabled, enable it and then write the counter */
        HighCheck50us_GLOBAL_ENABLE |= HighCheck50us_BLOCK_EN_MASK;
        CY_SET_REG16(HighCheck50us_COUNTER_LSB_PTR, (uint16)counter);
        HighCheck50us_GLOBAL_ENABLE &= ((uint8)(~HighCheck50us_BLOCK_EN_MASK));
    #else
        CY_SET_REG16(HighCheck50us_COUNTER_LSB_PTR, counter);
    #endif /* (HighCheck50us_UsingFixedFunction) */
}
#endif /* (!(HighCheck50us_UsingFixedFunction && (CY_PSOC5A))) */


/*******************************************************************************
* Function Name: HighCheck50us_ReadCounter
********************************************************************************
* Summary:
* Returns the current value of the counter.  It doesn't matter
* if the counter is enabled or running.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint16) The present value of the counter.
*
*******************************************************************************/
uint16 HighCheck50us_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    #if(HighCheck50us_UsingFixedFunction)
		(void)CY_GET_REG16(HighCheck50us_COUNTER_LSB_PTR);
	#else
		(void)CY_GET_REG8(HighCheck50us_COUNTER_LSB_PTR_8BIT);
	#endif/* (HighCheck50us_UsingFixedFunction) */
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    #if(HighCheck50us_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(HighCheck50us_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG16(HighCheck50us_STATICCOUNT_LSB_PTR));
    #endif /* (HighCheck50us_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: HighCheck50us_ReadCapture
********************************************************************************
* Summary:
*   This function returns the last value captured.
*
* Parameters:  
*  void
*
* Return: 
*  (uint16) Present Capture value.
*
*******************************************************************************/
uint16 HighCheck50us_ReadCapture(void) 
{
    #if(HighCheck50us_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(HighCheck50us_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG16(HighCheck50us_STATICCOUNT_LSB_PTR));
    #endif /* (HighCheck50us_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: HighCheck50us_WritePeriod
********************************************************************************
* Summary:
* Changes the period of the counter.  The new period 
* will be loaded the next time terminal count is detected.
*
* Parameters:  
*  period: (uint16) A value of 0 will result in
*         the counter remaining at zero.  
*
* Return: 
*  void
*
*******************************************************************************/
void HighCheck50us_WritePeriod(uint16 period) 
{
    #if(HighCheck50us_UsingFixedFunction)
        CY_SET_REG16(HighCheck50us_PERIOD_LSB_PTR,(uint16)period);
    #else
        CY_SET_REG16(HighCheck50us_PERIOD_LSB_PTR, period);
    #endif /* (HighCheck50us_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: HighCheck50us_ReadPeriod
********************************************************************************
* Summary:
* Reads the current period value without affecting counter operation.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint16) Present period value.
*
*******************************************************************************/
uint16 HighCheck50us_ReadPeriod(void) 
{
    #if(HighCheck50us_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(HighCheck50us_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG16(HighCheck50us_PERIOD_LSB_PTR));
    #endif /* (HighCheck50us_UsingFixedFunction) */
}


#if (!HighCheck50us_UsingFixedFunction)
/*******************************************************************************
* Function Name: HighCheck50us_WriteCompare
********************************************************************************
* Summary:
* Changes the compare value.  The compare output will 
* reflect the new value on the next UDB clock.  The compare output will be 
* driven high when the present counter value compares true based on the 
* configured compare mode setting. 
*
* Parameters:  
*  Compare:  New compare value. 
*
* Return: 
*  void
*
*******************************************************************************/
void HighCheck50us_WriteCompare(uint16 compare) \
                                   
{
    #if(HighCheck50us_UsingFixedFunction)
        CY_SET_REG16(HighCheck50us_COMPARE_LSB_PTR, (uint16)compare);
    #else
        CY_SET_REG16(HighCheck50us_COMPARE_LSB_PTR, compare);
    #endif /* (HighCheck50us_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: HighCheck50us_ReadCompare
********************************************************************************
* Summary:
* Returns the compare value.
*
* Parameters:  
*  void:
*
* Return: 
*  (uint16) Present compare value.
*
*******************************************************************************/
uint16 HighCheck50us_ReadCompare(void) 
{
    return (CY_GET_REG16(HighCheck50us_COMPARE_LSB_PTR));
}


#if (HighCheck50us_COMPARE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: HighCheck50us_SetCompareMode
********************************************************************************
* Summary:
*  Sets the software controlled Compare Mode.
*
* Parameters:
*  compareMode:  Compare Mode Enumerated Type.
*
* Return:
*  void
*
*******************************************************************************/
void HighCheck50us_SetCompareMode(uint8 compareMode) 
{
    /* Clear the compare mode bits in the control register */
    HighCheck50us_CONTROL &= ((uint8)(~HighCheck50us_CTRL_CMPMODE_MASK));
    
    /* Write the new setting */
    HighCheck50us_CONTROL |= compareMode;
}
#endif  /* (HighCheck50us_COMPARE_MODE_SOFTWARE) */


#if (HighCheck50us_CAPTURE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: HighCheck50us_SetCaptureMode
********************************************************************************
* Summary:
*  Sets the software controlled Capture Mode.
*
* Parameters:
*  captureMode:  Capture Mode Enumerated Type.
*
* Return:
*  void
*
*******************************************************************************/
void HighCheck50us_SetCaptureMode(uint8 captureMode) 
{
    /* Clear the capture mode bits in the control register */
    HighCheck50us_CONTROL &= ((uint8)(~HighCheck50us_CTRL_CAPMODE_MASK));
    
    /* Write the new setting */
    HighCheck50us_CONTROL |= ((uint8)((uint8)captureMode << HighCheck50us_CTRL_CAPMODE0_SHIFT));
}
#endif  /* (HighCheck50us_CAPTURE_MODE_SOFTWARE) */


/*******************************************************************************
* Function Name: HighCheck50us_ClearFIFO
********************************************************************************
* Summary:
*   This function clears all capture data from the capture FIFO
*
* Parameters:  
*  void:
*
* Return: 
*  None
*
*******************************************************************************/
void HighCheck50us_ClearFIFO(void) 
{

    while(0u != (HighCheck50us_ReadStatusRegister() & HighCheck50us_STATUS_FIFONEMP))
    {
        (void)HighCheck50us_ReadCapture();
    }

}
#endif  /* (!HighCheck50us_UsingFixedFunction) */


/* [] END OF FILE */

