/*******************************************************************************
* File Name: DATA_5V0.h  
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

#if !defined(CY_PINS_DATA_5V0_H) /* Pins DATA_5V0_H */
#define CY_PINS_DATA_5V0_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "DATA_5V0_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 DATA_5V0__PORT == 15 && ((DATA_5V0__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    DATA_5V0_Write(uint8 value);
void    DATA_5V0_SetDriveMode(uint8 mode);
uint8   DATA_5V0_ReadDataReg(void);
uint8   DATA_5V0_Read(void);
void    DATA_5V0_SetInterruptMode(uint16 position, uint16 mode);
uint8   DATA_5V0_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the DATA_5V0_SetDriveMode() function.
     *  @{
     */
        #define DATA_5V0_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define DATA_5V0_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define DATA_5V0_DM_RES_UP          PIN_DM_RES_UP
        #define DATA_5V0_DM_RES_DWN         PIN_DM_RES_DWN
        #define DATA_5V0_DM_OD_LO           PIN_DM_OD_LO
        #define DATA_5V0_DM_OD_HI           PIN_DM_OD_HI
        #define DATA_5V0_DM_STRONG          PIN_DM_STRONG
        #define DATA_5V0_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define DATA_5V0_MASK               DATA_5V0__MASK
#define DATA_5V0_SHIFT              DATA_5V0__SHIFT
#define DATA_5V0_WIDTH              1u

/* Interrupt constants */
#if defined(DATA_5V0__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in DATA_5V0_SetInterruptMode() function.
     *  @{
     */
        #define DATA_5V0_INTR_NONE      (uint16)(0x0000u)
        #define DATA_5V0_INTR_RISING    (uint16)(0x0001u)
        #define DATA_5V0_INTR_FALLING   (uint16)(0x0002u)
        #define DATA_5V0_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define DATA_5V0_INTR_MASK      (0x01u) 
#endif /* (DATA_5V0__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define DATA_5V0_PS                     (* (reg8 *) DATA_5V0__PS)
/* Data Register */
#define DATA_5V0_DR                     (* (reg8 *) DATA_5V0__DR)
/* Port Number */
#define DATA_5V0_PRT_NUM                (* (reg8 *) DATA_5V0__PRT) 
/* Connect to Analog Globals */                                                  
#define DATA_5V0_AG                     (* (reg8 *) DATA_5V0__AG)                       
/* Analog MUX bux enable */
#define DATA_5V0_AMUX                   (* (reg8 *) DATA_5V0__AMUX) 
/* Bidirectional Enable */                                                        
#define DATA_5V0_BIE                    (* (reg8 *) DATA_5V0__BIE)
/* Bit-mask for Aliased Register Access */
#define DATA_5V0_BIT_MASK               (* (reg8 *) DATA_5V0__BIT_MASK)
/* Bypass Enable */
#define DATA_5V0_BYP                    (* (reg8 *) DATA_5V0__BYP)
/* Port wide control signals */                                                   
#define DATA_5V0_CTL                    (* (reg8 *) DATA_5V0__CTL)
/* Drive Modes */
#define DATA_5V0_DM0                    (* (reg8 *) DATA_5V0__DM0) 
#define DATA_5V0_DM1                    (* (reg8 *) DATA_5V0__DM1)
#define DATA_5V0_DM2                    (* (reg8 *) DATA_5V0__DM2) 
/* Input Buffer Disable Override */
#define DATA_5V0_INP_DIS                (* (reg8 *) DATA_5V0__INP_DIS)
/* LCD Common or Segment Drive */
#define DATA_5V0_LCD_COM_SEG            (* (reg8 *) DATA_5V0__LCD_COM_SEG)
/* Enable Segment LCD */
#define DATA_5V0_LCD_EN                 (* (reg8 *) DATA_5V0__LCD_EN)
/* Slew Rate Control */
#define DATA_5V0_SLW                    (* (reg8 *) DATA_5V0__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define DATA_5V0_PRTDSI__CAPS_SEL       (* (reg8 *) DATA_5V0__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define DATA_5V0_PRTDSI__DBL_SYNC_IN    (* (reg8 *) DATA_5V0__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define DATA_5V0_PRTDSI__OE_SEL0        (* (reg8 *) DATA_5V0__PRTDSI__OE_SEL0) 
#define DATA_5V0_PRTDSI__OE_SEL1        (* (reg8 *) DATA_5V0__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define DATA_5V0_PRTDSI__OUT_SEL0       (* (reg8 *) DATA_5V0__PRTDSI__OUT_SEL0) 
#define DATA_5V0_PRTDSI__OUT_SEL1       (* (reg8 *) DATA_5V0__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define DATA_5V0_PRTDSI__SYNC_OUT       (* (reg8 *) DATA_5V0__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(DATA_5V0__SIO_CFG)
    #define DATA_5V0_SIO_HYST_EN        (* (reg8 *) DATA_5V0__SIO_HYST_EN)
    #define DATA_5V0_SIO_REG_HIFREQ     (* (reg8 *) DATA_5V0__SIO_REG_HIFREQ)
    #define DATA_5V0_SIO_CFG            (* (reg8 *) DATA_5V0__SIO_CFG)
    #define DATA_5V0_SIO_DIFF           (* (reg8 *) DATA_5V0__SIO_DIFF)
#endif /* (DATA_5V0__SIO_CFG) */

/* Interrupt Registers */
#if defined(DATA_5V0__INTSTAT)
    #define DATA_5V0_INTSTAT            (* (reg8 *) DATA_5V0__INTSTAT)
    #define DATA_5V0_SNAP               (* (reg8 *) DATA_5V0__SNAP)
    
	#define DATA_5V0_0_INTTYPE_REG 		(* (reg8 *) DATA_5V0__0__INTTYPE)
#endif /* (DATA_5V0__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_DATA_5V0_H */


/* [] END OF FILE */
