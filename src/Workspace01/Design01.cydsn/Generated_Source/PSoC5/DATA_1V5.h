/*******************************************************************************
* File Name: DATA_1V5.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_DATA_1V5_H) /* Pins DATA_1V5_H */
#define CY_PINS_DATA_1V5_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "DATA_1V5_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 DATA_1V5__PORT == 15 && ((DATA_1V5__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    DATA_1V5_Write(uint8 value);
void    DATA_1V5_SetDriveMode(uint8 mode);
uint8   DATA_1V5_ReadDataReg(void);
uint8   DATA_1V5_Read(void);
void    DATA_1V5_SetInterruptMode(uint16 position, uint16 mode);
uint8   DATA_1V5_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the DATA_1V5_SetDriveMode() function.
     *  @{
     */
        #define DATA_1V5_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define DATA_1V5_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define DATA_1V5_DM_RES_UP          PIN_DM_RES_UP
        #define DATA_1V5_DM_RES_DWN         PIN_DM_RES_DWN
        #define DATA_1V5_DM_OD_LO           PIN_DM_OD_LO
        #define DATA_1V5_DM_OD_HI           PIN_DM_OD_HI
        #define DATA_1V5_DM_STRONG          PIN_DM_STRONG
        #define DATA_1V5_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define DATA_1V5_MASK               DATA_1V5__MASK
#define DATA_1V5_SHIFT              DATA_1V5__SHIFT
#define DATA_1V5_WIDTH              1u

/* Interrupt constants */
#if defined(DATA_1V5__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in DATA_1V5_SetInterruptMode() function.
     *  @{
     */
        #define DATA_1V5_INTR_NONE      (uint16)(0x0000u)
        #define DATA_1V5_INTR_RISING    (uint16)(0x0001u)
        #define DATA_1V5_INTR_FALLING   (uint16)(0x0002u)
        #define DATA_1V5_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define DATA_1V5_INTR_MASK      (0x01u) 
#endif /* (DATA_1V5__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define DATA_1V5_PS                     (* (reg8 *) DATA_1V5__PS)
/* Data Register */
#define DATA_1V5_DR                     (* (reg8 *) DATA_1V5__DR)
/* Port Number */
#define DATA_1V5_PRT_NUM                (* (reg8 *) DATA_1V5__PRT) 
/* Connect to Analog Globals */                                                  
#define DATA_1V5_AG                     (* (reg8 *) DATA_1V5__AG)                       
/* Analog MUX bux enable */
#define DATA_1V5_AMUX                   (* (reg8 *) DATA_1V5__AMUX) 
/* Bidirectional Enable */                                                        
#define DATA_1V5_BIE                    (* (reg8 *) DATA_1V5__BIE)
/* Bit-mask for Aliased Register Access */
#define DATA_1V5_BIT_MASK               (* (reg8 *) DATA_1V5__BIT_MASK)
/* Bypass Enable */
#define DATA_1V5_BYP                    (* (reg8 *) DATA_1V5__BYP)
/* Port wide control signals */                                                   
#define DATA_1V5_CTL                    (* (reg8 *) DATA_1V5__CTL)
/* Drive Modes */
#define DATA_1V5_DM0                    (* (reg8 *) DATA_1V5__DM0) 
#define DATA_1V5_DM1                    (* (reg8 *) DATA_1V5__DM1)
#define DATA_1V5_DM2                    (* (reg8 *) DATA_1V5__DM2) 
/* Input Buffer Disable Override */
#define DATA_1V5_INP_DIS                (* (reg8 *) DATA_1V5__INP_DIS)
/* LCD Common or Segment Drive */
#define DATA_1V5_LCD_COM_SEG            (* (reg8 *) DATA_1V5__LCD_COM_SEG)
/* Enable Segment LCD */
#define DATA_1V5_LCD_EN                 (* (reg8 *) DATA_1V5__LCD_EN)
/* Slew Rate Control */
#define DATA_1V5_SLW                    (* (reg8 *) DATA_1V5__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define DATA_1V5_PRTDSI__CAPS_SEL       (* (reg8 *) DATA_1V5__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define DATA_1V5_PRTDSI__DBL_SYNC_IN    (* (reg8 *) DATA_1V5__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define DATA_1V5_PRTDSI__OE_SEL0        (* (reg8 *) DATA_1V5__PRTDSI__OE_SEL0) 
#define DATA_1V5_PRTDSI__OE_SEL1        (* (reg8 *) DATA_1V5__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define DATA_1V5_PRTDSI__OUT_SEL0       (* (reg8 *) DATA_1V5__PRTDSI__OUT_SEL0) 
#define DATA_1V5_PRTDSI__OUT_SEL1       (* (reg8 *) DATA_1V5__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define DATA_1V5_PRTDSI__SYNC_OUT       (* (reg8 *) DATA_1V5__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(DATA_1V5__SIO_CFG)
    #define DATA_1V5_SIO_HYST_EN        (* (reg8 *) DATA_1V5__SIO_HYST_EN)
    #define DATA_1V5_SIO_REG_HIFREQ     (* (reg8 *) DATA_1V5__SIO_REG_HIFREQ)
    #define DATA_1V5_SIO_CFG            (* (reg8 *) DATA_1V5__SIO_CFG)
    #define DATA_1V5_SIO_DIFF           (* (reg8 *) DATA_1V5__SIO_DIFF)
#endif /* (DATA_1V5__SIO_CFG) */

/* Interrupt Registers */
#if defined(DATA_1V5__INTSTAT)
    #define DATA_1V5_INTSTAT            (* (reg8 *) DATA_1V5__INTSTAT)
    #define DATA_1V5_SNAP               (* (reg8 *) DATA_1V5__SNAP)
    
	#define DATA_1V5_0_INTTYPE_REG 		(* (reg8 *) DATA_1V5__0__INTTYPE)
#endif /* (DATA_1V5__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_DATA_1V5_H */


/* [] END OF FILE */
