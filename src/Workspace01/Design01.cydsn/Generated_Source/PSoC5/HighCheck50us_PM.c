/*******************************************************************************
* File Name: HighCheck50us_PM.c  
* Version 3.0
*
*  Description:
*    This file provides the power management source code to API for the
*    Counter.  
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

static HighCheck50us_backupStruct HighCheck50us_backup;


/*******************************************************************************
* Function Name: HighCheck50us_SaveConfig
********************************************************************************
* Summary:
*     Save the current user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  HighCheck50us_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void HighCheck50us_SaveConfig(void) 
{
    #if (!HighCheck50us_UsingFixedFunction)

        HighCheck50us_backup.CounterUdb = HighCheck50us_ReadCounter();

        #if(!HighCheck50us_ControlRegRemoved)
            HighCheck50us_backup.CounterControlRegister = HighCheck50us_ReadControlRegister();
        #endif /* (!HighCheck50us_ControlRegRemoved) */

    #endif /* (!HighCheck50us_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: HighCheck50us_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  HighCheck50us_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void HighCheck50us_RestoreConfig(void) 
{      
    #if (!HighCheck50us_UsingFixedFunction)

       HighCheck50us_WriteCounter(HighCheck50us_backup.CounterUdb);

        #if(!HighCheck50us_ControlRegRemoved)
            HighCheck50us_WriteControlRegister(HighCheck50us_backup.CounterControlRegister);
        #endif /* (!HighCheck50us_ControlRegRemoved) */

    #endif /* (!HighCheck50us_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: HighCheck50us_Sleep
********************************************************************************
* Summary:
*     Stop and Save the user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  HighCheck50us_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void HighCheck50us_Sleep(void) 
{
    #if(!HighCheck50us_ControlRegRemoved)
        /* Save Counter's enable state */
        if(HighCheck50us_CTRL_ENABLE == (HighCheck50us_CONTROL & HighCheck50us_CTRL_ENABLE))
        {
            /* Counter is enabled */
            HighCheck50us_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            HighCheck50us_backup.CounterEnableState = 0u;
        }
    #else
        HighCheck50us_backup.CounterEnableState = 1u;
        if(HighCheck50us_backup.CounterEnableState != 0u)
        {
            HighCheck50us_backup.CounterEnableState = 0u;
        }
    #endif /* (!HighCheck50us_ControlRegRemoved) */
    
    HighCheck50us_Stop();
    HighCheck50us_SaveConfig();
}


/*******************************************************************************
* Function Name: HighCheck50us_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  HighCheck50us_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void HighCheck50us_Wakeup(void) 
{
    HighCheck50us_RestoreConfig();
    #if(!HighCheck50us_ControlRegRemoved)
        if(HighCheck50us_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            HighCheck50us_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!HighCheck50us_ControlRegRemoved) */
    
}


/* [] END OF FILE */
