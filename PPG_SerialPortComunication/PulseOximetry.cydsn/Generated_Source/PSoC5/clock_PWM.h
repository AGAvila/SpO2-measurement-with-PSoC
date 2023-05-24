/*******************************************************************************
* File Name: clock_PWM.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_clock_PWM_H)
#define CY_CLOCK_clock_PWM_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void clock_PWM_Start(void) ;
void clock_PWM_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void clock_PWM_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void clock_PWM_StandbyPower(uint8 state) ;
void clock_PWM_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 clock_PWM_GetDividerRegister(void) ;
void clock_PWM_SetModeRegister(uint8 modeBitMask) ;
void clock_PWM_ClearModeRegister(uint8 modeBitMask) ;
uint8 clock_PWM_GetModeRegister(void) ;
void clock_PWM_SetSourceRegister(uint8 clkSource) ;
uint8 clock_PWM_GetSourceRegister(void) ;
#if defined(clock_PWM__CFG3)
void clock_PWM_SetPhaseRegister(uint8 clkPhase) ;
uint8 clock_PWM_GetPhaseRegister(void) ;
#endif /* defined(clock_PWM__CFG3) */

#define clock_PWM_Enable()                       clock_PWM_Start()
#define clock_PWM_Disable()                      clock_PWM_Stop()
#define clock_PWM_SetDivider(clkDivider)         clock_PWM_SetDividerRegister(clkDivider, 1u)
#define clock_PWM_SetDividerValue(clkDivider)    clock_PWM_SetDividerRegister((clkDivider) - 1u, 1u)
#define clock_PWM_SetMode(clkMode)               clock_PWM_SetModeRegister(clkMode)
#define clock_PWM_SetSource(clkSource)           clock_PWM_SetSourceRegister(clkSource)
#if defined(clock_PWM__CFG3)
#define clock_PWM_SetPhase(clkPhase)             clock_PWM_SetPhaseRegister(clkPhase)
#define clock_PWM_SetPhaseValue(clkPhase)        clock_PWM_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(clock_PWM__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define clock_PWM_CLKEN              (* (reg8 *) clock_PWM__PM_ACT_CFG)
#define clock_PWM_CLKEN_PTR          ((reg8 *) clock_PWM__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define clock_PWM_CLKSTBY            (* (reg8 *) clock_PWM__PM_STBY_CFG)
#define clock_PWM_CLKSTBY_PTR        ((reg8 *) clock_PWM__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define clock_PWM_DIV_LSB            (* (reg8 *) clock_PWM__CFG0)
#define clock_PWM_DIV_LSB_PTR        ((reg8 *) clock_PWM__CFG0)
#define clock_PWM_DIV_PTR            ((reg16 *) clock_PWM__CFG0)

/* Clock MSB divider configuration register. */
#define clock_PWM_DIV_MSB            (* (reg8 *) clock_PWM__CFG1)
#define clock_PWM_DIV_MSB_PTR        ((reg8 *) clock_PWM__CFG1)

/* Mode and source configuration register */
#define clock_PWM_MOD_SRC            (* (reg8 *) clock_PWM__CFG2)
#define clock_PWM_MOD_SRC_PTR        ((reg8 *) clock_PWM__CFG2)

#if defined(clock_PWM__CFG3)
/* Analog clock phase configuration register */
#define clock_PWM_PHASE              (* (reg8 *) clock_PWM__CFG3)
#define clock_PWM_PHASE_PTR          ((reg8 *) clock_PWM__CFG3)
#endif /* defined(clock_PWM__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define clock_PWM_CLKEN_MASK         clock_PWM__PM_ACT_MSK
#define clock_PWM_CLKSTBY_MASK       clock_PWM__PM_STBY_MSK

/* CFG2 field masks */
#define clock_PWM_SRC_SEL_MSK        clock_PWM__CFG2_SRC_SEL_MASK
#define clock_PWM_MODE_MASK          (~(clock_PWM_SRC_SEL_MSK))

#if defined(clock_PWM__CFG3)
/* CFG3 phase mask */
#define clock_PWM_PHASE_MASK         clock_PWM__CFG3_PHASE_DLY_MASK
#endif /* defined(clock_PWM__CFG3) */

#endif /* CY_CLOCK_clock_PWM_H */


/* [] END OF FILE */
