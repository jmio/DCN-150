/*******************************************************************************
* File Name: ShiftReg_2.h
* Version 2.30
*
* Description:
*  This header file contains definitions associated with the Shift Register
*  component.
*
* Note: none
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/


#if !defined(CY_SHIFTREG_ShiftReg_2_H)
#define CY_SHIFTREG_ShiftReg_2_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h"


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define ShiftReg_2_FIFO_SIZE          (4u)
#define ShiftReg_2_USE_INPUT_FIFO     (0u)
#define ShiftReg_2_USE_OUTPUT_FIFO    (0u)
#define ShiftReg_2_SR_SIZE            (24u)


/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;

    uint32 saveSrA0Reg;
    uint32 saveSrA1Reg;

    #if(CY_UDB_V0)
        uint32 saveSrIntMask;
    #endif /* (CY_UDB_V0) */

} ShiftReg_2_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void  ShiftReg_2_Start(void)                              ;
void  ShiftReg_2_Stop(void)                               ;
void  ShiftReg_2_Init(void)                               ;
void  ShiftReg_2_Enable(void)                             ;
void  ShiftReg_2_RestoreConfig(void)                      ;
void  ShiftReg_2_SaveConfig(void)                         ;
void  ShiftReg_2_Sleep(void)                              ;
void  ShiftReg_2_Wakeup(void)                             ;
void  ShiftReg_2_EnableInt(void)                          ;
void  ShiftReg_2_DisableInt(void)                         ;
void  ShiftReg_2_SetIntMode(uint8 interruptSource)        ;
uint8 ShiftReg_2_GetIntStatus(void)                       ;
void  ShiftReg_2_WriteRegValue(uint32 shiftData) \
                                                                ;
uint32 ShiftReg_2_ReadRegValue(void) ;
uint8    ShiftReg_2_GetFIFOStatus(uint8 fifoId)           ;

#if(0u != ShiftReg_2_USE_INPUT_FIFO)
    cystatus ShiftReg_2_WriteData(uint32 shiftData) \
                                                                ;
#endif /* (0u != ShiftReg_2_USE_INPUT_FIFO) */

#if(0u != ShiftReg_2_USE_OUTPUT_FIFO)
    uint32 ShiftReg_2_ReadData(void) ;
#endif /* (0u != ShiftReg_2_USE_OUTPUT_FIFO) */


/**********************************
*   Variable with external linkage
**********************************/

extern uint8 ShiftReg_2_initVar;


/***************************************
*           API Constants
***************************************/

#define ShiftReg_2_LOAD                   (0x01u)
#define ShiftReg_2_STORE                  (0x02u)
#define ShiftReg_2_RESET                  (0x04u)

#define ShiftReg_2_IN_FIFO                (0x01u)
#define ShiftReg_2_OUT_FIFO               (0x02u)

#define ShiftReg_2_RET_FIFO_FULL          (0x00u)

/* This define is obsolete */
#define ShiftReg_2_RET_FIFO_NOT_EMPTY     (0x01u)

#define ShiftReg_2_RET_FIFO_PARTIAL       (0x01u)
#define ShiftReg_2_RET_FIFO_EMPTY         (0x02u)
#define ShiftReg_2_RET_FIFO_NOT_DEFINED   (0xFEu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define ShiftReg_2__LEFT 0
#define ShiftReg_2__RIGHT 1



/***************************************
*    Initial Parameter Constants
***************************************/

#define ShiftReg_2_SR_MASK    (0xFFFFFFu) /* Unsigned is added to parameter */
#define ShiftReg_2_INT_SRC    (0u)
#define ShiftReg_2_DIRECTION  (1u)


/***************************************
*             Registers
***************************************/

/* Control register */
#define ShiftReg_2_SR_CONTROL_REG (* (reg8 *) \
                                           ShiftReg_2_bSR_SyncCtl_CtrlReg__CONTROL_REG)
#define ShiftReg_2_SR_CONTROL_PTR (  (reg8 *) \
                                           ShiftReg_2_bSR_SyncCtl_CtrlReg__CONTROL_REG)

/* Status register */
#define ShiftReg_2_SR_STATUS_REG      (* (reg8 *) ShiftReg_2_bSR_StsReg__STATUS_REG)
#define ShiftReg_2_SR_STATUS_PTR      (  (reg8 *) ShiftReg_2_bSR_StsReg__STATUS_REG)

/* Interrupt status register */
#define ShiftReg_2_SR_STATUS_MASK_REG (* (reg8 *) ShiftReg_2_bSR_StsReg__MASK_REG)
#define ShiftReg_2_SR_STATUS_MASK_PTR (  (reg8 *) ShiftReg_2_bSR_StsReg__MASK_REG)

/* Aux control register */
#define ShiftReg_2_SR_AUX_CONTROL_REG (* (reg8 *) ShiftReg_2_bSR_StsReg__STATUS_AUX_CTL_REG)
#define ShiftReg_2_SR_AUX_CONTROL_PTR (  (reg8 *) ShiftReg_2_bSR_StsReg__STATUS_AUX_CTL_REG)

/* A1 register: only used to implement capture function */
#define ShiftReg_2_SHIFT_REG_CAPTURE_PTR    ( (reg8 *) \
                                        ShiftReg_2_bSR_sC24_BShiftRegDp_u0__A1_REG )

#if(CY_PSOC3 || CY_PSOC5)
    #define ShiftReg_2_IN_FIFO_VAL_LSB_PTR        ( (reg32 *) \
                                        ShiftReg_2_bSR_sC24_BShiftRegDp_u0__F0_REG )

    #define ShiftReg_2_SHIFT_REG_LSB_PTR          ( (reg32 *) \
                                        ShiftReg_2_bSR_sC24_BShiftRegDp_u0__A0_REG )

    #define ShiftReg_2_SHIFT_REG_VALUE_LSB_PTR    ( (reg32 *) \
                                        ShiftReg_2_bSR_sC24_BShiftRegDp_u0__A1_REG )

    #define ShiftReg_2_OUT_FIFO_VAL_LSB_PTR       ( (reg32 *) \
                                        ShiftReg_2_bSR_sC24_BShiftRegDp_u0__F1_REG )

#else
    #if(ShiftReg_2_SR_SIZE <= 8u) /* 8bit - ShiftReg */
        #define ShiftReg_2_IN_FIFO_VAL_LSB_PTR        ( (reg8 *) \
                                        ShiftReg_2_bSR_sC24_BShiftRegDp_u0__F0_REG )

        #define ShiftReg_2_SHIFT_REG_LSB_PTR          ( (reg8 *) \
                                        ShiftReg_2_bSR_sC24_BShiftRegDp_u0__A0_REG )

        #define ShiftReg_2_SHIFT_REG_VALUE_LSB_PTR    ( (reg8 *) \
                                        ShiftReg_2_bSR_sC24_BShiftRegDp_u0__A1_REG )

        #define ShiftReg_2_OUT_FIFO_VAL_LSB_PTR       ( (reg8 *) \
                                        ShiftReg_2_bSR_sC24_BShiftRegDp_u0__F1_REG )

    #elif(ShiftReg_2_SR_SIZE <= 16u) /* 16bit - ShiftReg */
        #define ShiftReg_2_IN_FIFO_VAL_LSB_PTR        ( (reg16 *) \
                                  ShiftReg_2_bSR_sC24_BShiftRegDp_u0__16BIT_F0_REG )

        #define ShiftReg_2_SHIFT_REG_LSB_PTR          ( (reg16 *) \
                                  ShiftReg_2_bSR_sC24_BShiftRegDp_u0__16BIT_A0_REG )

        #define ShiftReg_2_SHIFT_REG_VALUE_LSB_PTR    ( (reg16 *) \
                                  ShiftReg_2_bSR_sC24_BShiftRegDp_u0__16BIT_A1_REG )

        #define ShiftReg_2_OUT_FIFO_VAL_LSB_PTR       ( (reg16 *) \
                                  ShiftReg_2_bSR_sC24_BShiftRegDp_u0__16BIT_F1_REG )


    #elif(ShiftReg_2_SR_SIZE <= 24u) /* 24bit - ShiftReg */
        #define ShiftReg_2_IN_FIFO_VAL_LSB_PTR        ( (reg32 *) \
                                        ShiftReg_2_bSR_sC24_BShiftRegDp_u0__F0_REG )

        #define ShiftReg_2_SHIFT_REG_LSB_PTR          ( (reg32 *) \
                                        ShiftReg_2_bSR_sC24_BShiftRegDp_u0__A0_REG )

        #define ShiftReg_2_SHIFT_REG_VALUE_LSB_PTR    ( (reg32 *) \
                                        ShiftReg_2_bSR_sC24_BShiftRegDp_u0__A1_REG )

        #define ShiftReg_2_OUT_FIFO_VAL_LSB_PTR       ( (reg32 *) \
                                        ShiftReg_2_bSR_sC24_BShiftRegDp_u0__F1_REG )

    #else /* 32bit - ShiftReg */
        #define ShiftReg_2_IN_FIFO_VAL_LSB_PTR        ( (reg32 *) \
                                  ShiftReg_2_bSR_sC24_BShiftRegDp_u0__32BIT_F0_REG )

        #define ShiftReg_2_SHIFT_REG_LSB_PTR          ( (reg32 *) \
                                  ShiftReg_2_bSR_sC24_BShiftRegDp_u0__32BIT_A0_REG )

        #define ShiftReg_2_SHIFT_REG_VALUE_LSB_PTR    ( (reg32 *) \
                                  ShiftReg_2_bSR_sC24_BShiftRegDp_u0__32BIT_A1_REG )

        #define ShiftReg_2_OUT_FIFO_VAL_LSB_PTR       ( (reg32 *) \
                                  ShiftReg_2_bSR_sC24_BShiftRegDp_u0__32BIT_F1_REG )

    #endif  /* (ShiftReg_2_SR_SIZE <= 8u) */
#endif      /* (CY_PSOC3 || CY_PSOC5) */


/***************************************
*       Register Constants
***************************************/

#define ShiftReg_2_INTERRUPTS_ENABLE      (0x10u)
#define ShiftReg_2_LOAD_INT_EN            (0x01u)
#define ShiftReg_2_STORE_INT_EN           (0x02u)
#define ShiftReg_2_RESET_INT_EN           (0x04u)
#define ShiftReg_2_CLK_EN                 (0x01u)

#define ShiftReg_2_RESET_INT_EN_MASK      (0xFBu)
#define ShiftReg_2_LOAD_INT_EN_MASK       (0xFEu)
#define ShiftReg_2_STORE_INT_EN_MASK      (0xFDu)
#define ShiftReg_2_INTS_EN_MASK           (0x07u)

#define ShiftReg_2_OUT_FIFO_CLR_BIT       (0x02u)

#if(0u != ShiftReg_2_USE_INPUT_FIFO)

    #define ShiftReg_2_IN_FIFO_MASK       (0x18u)

    #define ShiftReg_2_IN_FIFO_FULL       (0x00u)
    #define ShiftReg_2_IN_FIFO_EMPTY      (0x01u)
    #define ShiftReg_2_IN_FIFO_PARTIAL    (0x02u)
    
    /* This define is obsolete */
    #define ShiftReg_2_IN_FIFO_NOT_EMPTY  (0x02u)
    
#endif /* (0u != ShiftReg_2_USE_INPUT_FIFO) */

#define ShiftReg_2_OUT_FIFO_MASK          (0x60u)

#define ShiftReg_2_OUT_FIFO_EMPTY         (0x00u)
#define ShiftReg_2_OUT_FIFO_FULL          (0x01u)
#define ShiftReg_2_OUT_FIFO_PARTIAL       (0x02u)

/* This define is obsolete */
#define ShiftReg_2_OUT_FIFO_NOT_EMPTY     (0x02u)

#define ShiftReg_2_IN_FIFO_SHIFT_MASK     (0x03u)
#define ShiftReg_2_OUT_FIFO_SHIFT_MASK    (0x05u)

#define ShiftReg_2_DISABLED               (0u)
#define ShiftReg_2_DEFAULT_A0             (0u)
#define ShiftReg_2_DEFAULT_A1             (0u)


/***************************************
*       Macros
***************************************/

#define ShiftReg_2_IS_ENABLED         (0u != (ShiftReg_2_SR_CONTROL & ShiftReg_2_CLK_EN))

#define ShiftReg_2_GET_OUT_FIFO_STS   ((ShiftReg_2_SR_STATUS & ShiftReg_2_OUT_FIFO_MASK) >> \
                                              ShiftReg_2_OUT_FIFO_SHIFT_MASK)

#define ShiftReg_2_GET_IN_FIFO_STS    ((ShiftReg_2_SR_STATUS & ShiftReg_2_IN_FIFO_MASK)  >> \
                                              ShiftReg_2_IN_FIFO_SHIFT_MASK)


/***************************************
*       Obsolete
***************************************/

/* Following code are OBSOLETE and must not be used 
 * starting from ShiftReg 2.20 
 */

#define ShiftReg_2_SR_CONTROL     (ShiftReg_2_SR_CONTROL_REG)
#define ShiftReg_2_SR_STATUS      (ShiftReg_2_SR_STATUS_REG)
#define ShiftReg_2_SR_STATUS_MASK (ShiftReg_2_SR_STATUS_MASK_REG)
#define ShiftReg_2_SR_AUX_CONTROL (ShiftReg_2_SR_AUX_CONTROL_REG)

#define ShiftReg_2_IN_FIFO_SHFT_MASK  (ShiftReg_2_IN_FIFO_SHIFT_MASK)
#define ShiftReg_2_OUT_FIFO_SHFT_MASK (ShiftReg_2_OUT_FIFO_SHFIT_MASK)

#define ShiftReg_2_RET_FIFO_BAD_PARAM (0xFFu)

#endif /* (CY_SHIFTREG_ShiftReg_2_H) */


/* [] END OF FILE */
