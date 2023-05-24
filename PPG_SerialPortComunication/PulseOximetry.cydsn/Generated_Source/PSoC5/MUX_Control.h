/*******************************************************************************
* File Name: MUX_Control.h  
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

#if !defined(CY_PINS_MUX_Control_H) /* Pins MUX_Control_H */
#define CY_PINS_MUX_Control_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "MUX_Control_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 MUX_Control__PORT == 15 && ((MUX_Control__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    MUX_Control_Write(uint8 value);
void    MUX_Control_SetDriveMode(uint8 mode);
uint8   MUX_Control_ReadDataReg(void);
uint8   MUX_Control_Read(void);
void    MUX_Control_SetInterruptMode(uint16 position, uint16 mode);
uint8   MUX_Control_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the MUX_Control_SetDriveMode() function.
     *  @{
     */
        #define MUX_Control_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define MUX_Control_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define MUX_Control_DM_RES_UP          PIN_DM_RES_UP
        #define MUX_Control_DM_RES_DWN         PIN_DM_RES_DWN
        #define MUX_Control_DM_OD_LO           PIN_DM_OD_LO
        #define MUX_Control_DM_OD_HI           PIN_DM_OD_HI
        #define MUX_Control_DM_STRONG          PIN_DM_STRONG
        #define MUX_Control_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define MUX_Control_MASK               MUX_Control__MASK
#define MUX_Control_SHIFT              MUX_Control__SHIFT
#define MUX_Control_WIDTH              1u

/* Interrupt constants */
#if defined(MUX_Control__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in MUX_Control_SetInterruptMode() function.
     *  @{
     */
        #define MUX_Control_INTR_NONE      (uint16)(0x0000u)
        #define MUX_Control_INTR_RISING    (uint16)(0x0001u)
        #define MUX_Control_INTR_FALLING   (uint16)(0x0002u)
        #define MUX_Control_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define MUX_Control_INTR_MASK      (0x01u) 
#endif /* (MUX_Control__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define MUX_Control_PS                     (* (reg8 *) MUX_Control__PS)
/* Data Register */
#define MUX_Control_DR                     (* (reg8 *) MUX_Control__DR)
/* Port Number */
#define MUX_Control_PRT_NUM                (* (reg8 *) MUX_Control__PRT) 
/* Connect to Analog Globals */                                                  
#define MUX_Control_AG                     (* (reg8 *) MUX_Control__AG)                       
/* Analog MUX bux enable */
#define MUX_Control_AMUX                   (* (reg8 *) MUX_Control__AMUX) 
/* Bidirectional Enable */                                                        
#define MUX_Control_BIE                    (* (reg8 *) MUX_Control__BIE)
/* Bit-mask for Aliased Register Access */
#define MUX_Control_BIT_MASK               (* (reg8 *) MUX_Control__BIT_MASK)
/* Bypass Enable */
#define MUX_Control_BYP                    (* (reg8 *) MUX_Control__BYP)
/* Port wide control signals */                                                   
#define MUX_Control_CTL                    (* (reg8 *) MUX_Control__CTL)
/* Drive Modes */
#define MUX_Control_DM0                    (* (reg8 *) MUX_Control__DM0) 
#define MUX_Control_DM1                    (* (reg8 *) MUX_Control__DM1)
#define MUX_Control_DM2                    (* (reg8 *) MUX_Control__DM2) 
/* Input Buffer Disable Override */
#define MUX_Control_INP_DIS                (* (reg8 *) MUX_Control__INP_DIS)
/* LCD Common or Segment Drive */
#define MUX_Control_LCD_COM_SEG            (* (reg8 *) MUX_Control__LCD_COM_SEG)
/* Enable Segment LCD */
#define MUX_Control_LCD_EN                 (* (reg8 *) MUX_Control__LCD_EN)
/* Slew Rate Control */
#define MUX_Control_SLW                    (* (reg8 *) MUX_Control__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define MUX_Control_PRTDSI__CAPS_SEL       (* (reg8 *) MUX_Control__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define MUX_Control_PRTDSI__DBL_SYNC_IN    (* (reg8 *) MUX_Control__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define MUX_Control_PRTDSI__OE_SEL0        (* (reg8 *) MUX_Control__PRTDSI__OE_SEL0) 
#define MUX_Control_PRTDSI__OE_SEL1        (* (reg8 *) MUX_Control__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define MUX_Control_PRTDSI__OUT_SEL0       (* (reg8 *) MUX_Control__PRTDSI__OUT_SEL0) 
#define MUX_Control_PRTDSI__OUT_SEL1       (* (reg8 *) MUX_Control__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define MUX_Control_PRTDSI__SYNC_OUT       (* (reg8 *) MUX_Control__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(MUX_Control__SIO_CFG)
    #define MUX_Control_SIO_HYST_EN        (* (reg8 *) MUX_Control__SIO_HYST_EN)
    #define MUX_Control_SIO_REG_HIFREQ     (* (reg8 *) MUX_Control__SIO_REG_HIFREQ)
    #define MUX_Control_SIO_CFG            (* (reg8 *) MUX_Control__SIO_CFG)
    #define MUX_Control_SIO_DIFF           (* (reg8 *) MUX_Control__SIO_DIFF)
#endif /* (MUX_Control__SIO_CFG) */

/* Interrupt Registers */
#if defined(MUX_Control__INTSTAT)
    #define MUX_Control_INTSTAT            (* (reg8 *) MUX_Control__INTSTAT)
    #define MUX_Control_SNAP               (* (reg8 *) MUX_Control__SNAP)
    
	#define MUX_Control_0_INTTYPE_REG 		(* (reg8 *) MUX_Control__0__INTTYPE)
#endif /* (MUX_Control__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_MUX_Control_H */


/* [] END OF FILE */
