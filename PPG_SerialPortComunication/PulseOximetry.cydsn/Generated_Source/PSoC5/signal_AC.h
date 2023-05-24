/*******************************************************************************
* File Name: signal_AC.h  
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

#if !defined(CY_PINS_signal_AC_H) /* Pins signal_AC_H */
#define CY_PINS_signal_AC_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "signal_AC_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 signal_AC__PORT == 15 && ((signal_AC__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    signal_AC_Write(uint8 value);
void    signal_AC_SetDriveMode(uint8 mode);
uint8   signal_AC_ReadDataReg(void);
uint8   signal_AC_Read(void);
void    signal_AC_SetInterruptMode(uint16 position, uint16 mode);
uint8   signal_AC_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the signal_AC_SetDriveMode() function.
     *  @{
     */
        #define signal_AC_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define signal_AC_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define signal_AC_DM_RES_UP          PIN_DM_RES_UP
        #define signal_AC_DM_RES_DWN         PIN_DM_RES_DWN
        #define signal_AC_DM_OD_LO           PIN_DM_OD_LO
        #define signal_AC_DM_OD_HI           PIN_DM_OD_HI
        #define signal_AC_DM_STRONG          PIN_DM_STRONG
        #define signal_AC_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define signal_AC_MASK               signal_AC__MASK
#define signal_AC_SHIFT              signal_AC__SHIFT
#define signal_AC_WIDTH              1u

/* Interrupt constants */
#if defined(signal_AC__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in signal_AC_SetInterruptMode() function.
     *  @{
     */
        #define signal_AC_INTR_NONE      (uint16)(0x0000u)
        #define signal_AC_INTR_RISING    (uint16)(0x0001u)
        #define signal_AC_INTR_FALLING   (uint16)(0x0002u)
        #define signal_AC_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define signal_AC_INTR_MASK      (0x01u) 
#endif /* (signal_AC__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define signal_AC_PS                     (* (reg8 *) signal_AC__PS)
/* Data Register */
#define signal_AC_DR                     (* (reg8 *) signal_AC__DR)
/* Port Number */
#define signal_AC_PRT_NUM                (* (reg8 *) signal_AC__PRT) 
/* Connect to Analog Globals */                                                  
#define signal_AC_AG                     (* (reg8 *) signal_AC__AG)                       
/* Analog MUX bux enable */
#define signal_AC_AMUX                   (* (reg8 *) signal_AC__AMUX) 
/* Bidirectional Enable */                                                        
#define signal_AC_BIE                    (* (reg8 *) signal_AC__BIE)
/* Bit-mask for Aliased Register Access */
#define signal_AC_BIT_MASK               (* (reg8 *) signal_AC__BIT_MASK)
/* Bypass Enable */
#define signal_AC_BYP                    (* (reg8 *) signal_AC__BYP)
/* Port wide control signals */                                                   
#define signal_AC_CTL                    (* (reg8 *) signal_AC__CTL)
/* Drive Modes */
#define signal_AC_DM0                    (* (reg8 *) signal_AC__DM0) 
#define signal_AC_DM1                    (* (reg8 *) signal_AC__DM1)
#define signal_AC_DM2                    (* (reg8 *) signal_AC__DM2) 
/* Input Buffer Disable Override */
#define signal_AC_INP_DIS                (* (reg8 *) signal_AC__INP_DIS)
/* LCD Common or Segment Drive */
#define signal_AC_LCD_COM_SEG            (* (reg8 *) signal_AC__LCD_COM_SEG)
/* Enable Segment LCD */
#define signal_AC_LCD_EN                 (* (reg8 *) signal_AC__LCD_EN)
/* Slew Rate Control */
#define signal_AC_SLW                    (* (reg8 *) signal_AC__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define signal_AC_PRTDSI__CAPS_SEL       (* (reg8 *) signal_AC__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define signal_AC_PRTDSI__DBL_SYNC_IN    (* (reg8 *) signal_AC__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define signal_AC_PRTDSI__OE_SEL0        (* (reg8 *) signal_AC__PRTDSI__OE_SEL0) 
#define signal_AC_PRTDSI__OE_SEL1        (* (reg8 *) signal_AC__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define signal_AC_PRTDSI__OUT_SEL0       (* (reg8 *) signal_AC__PRTDSI__OUT_SEL0) 
#define signal_AC_PRTDSI__OUT_SEL1       (* (reg8 *) signal_AC__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define signal_AC_PRTDSI__SYNC_OUT       (* (reg8 *) signal_AC__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(signal_AC__SIO_CFG)
    #define signal_AC_SIO_HYST_EN        (* (reg8 *) signal_AC__SIO_HYST_EN)
    #define signal_AC_SIO_REG_HIFREQ     (* (reg8 *) signal_AC__SIO_REG_HIFREQ)
    #define signal_AC_SIO_CFG            (* (reg8 *) signal_AC__SIO_CFG)
    #define signal_AC_SIO_DIFF           (* (reg8 *) signal_AC__SIO_DIFF)
#endif /* (signal_AC__SIO_CFG) */

/* Interrupt Registers */
#if defined(signal_AC__INTSTAT)
    #define signal_AC_INTSTAT            (* (reg8 *) signal_AC__INTSTAT)
    #define signal_AC_SNAP               (* (reg8 *) signal_AC__SNAP)
    
	#define signal_AC_0_INTTYPE_REG 		(* (reg8 *) signal_AC__0__INTTYPE)
#endif /* (signal_AC__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_signal_AC_H */


/* [] END OF FILE */
