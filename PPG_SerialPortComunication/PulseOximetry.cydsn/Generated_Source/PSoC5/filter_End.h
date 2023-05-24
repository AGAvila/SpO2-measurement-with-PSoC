/*******************************************************************************
* File Name: filter_End.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_filter_End_H)
#define CY_ISR_filter_End_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void filter_End_Start(void);
void filter_End_StartEx(cyisraddress address);
void filter_End_Stop(void);

CY_ISR_PROTO(filter_End_Interrupt);

void filter_End_SetVector(cyisraddress address);
cyisraddress filter_End_GetVector(void);

void filter_End_SetPriority(uint8 priority);
uint8 filter_End_GetPriority(void);

void filter_End_Enable(void);
uint8 filter_End_GetState(void);
void filter_End_Disable(void);

void filter_End_SetPending(void);
void filter_End_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the filter_End ISR. */
#define filter_End_INTC_VECTOR            ((reg32 *) filter_End__INTC_VECT)

/* Address of the filter_End ISR priority. */
#define filter_End_INTC_PRIOR             ((reg8 *) filter_End__INTC_PRIOR_REG)

/* Priority of the filter_End interrupt. */
#define filter_End_INTC_PRIOR_NUMBER      filter_End__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable filter_End interrupt. */
#define filter_End_INTC_SET_EN            ((reg32 *) filter_End__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the filter_End interrupt. */
#define filter_End_INTC_CLR_EN            ((reg32 *) filter_End__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the filter_End interrupt state to pending. */
#define filter_End_INTC_SET_PD            ((reg32 *) filter_End__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the filter_End interrupt. */
#define filter_End_INTC_CLR_PD            ((reg32 *) filter_End__INTC_CLR_PD_REG)


#endif /* CY_ISR_filter_End_H */


/* [] END OF FILE */
