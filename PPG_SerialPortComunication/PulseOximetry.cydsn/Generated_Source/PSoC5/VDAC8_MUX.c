/*******************************************************************************
* File Name: VDAC8_MUX.c  
* Version 1.90
*
* Description:
*  This file provides the source code to the API for the 8-bit Voltage DAC 
*  (VDAC8) User Module.
*
* Note:
*  Any unusual or non-standard behavior should be noted here. Other-
*  wise, this section should remain blank.
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "VDAC8_MUX.h"

#if (CY_PSOC5A)
#include <CyLib.h>
#endif /* CY_PSOC5A */

uint8 VDAC8_MUX_initVar = 0u;

#if (CY_PSOC5A)
    static uint8 VDAC8_MUX_restoreVal = 0u;
#endif /* CY_PSOC5A */

#if (CY_PSOC5A)
    static VDAC8_MUX_backupStruct VDAC8_MUX_backup;
#endif /* CY_PSOC5A */


/*******************************************************************************
* Function Name: VDAC8_MUX_Init
********************************************************************************
* Summary:
*  Initialize to the schematic state.
* 
* Parameters:
*  void:
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void VDAC8_MUX_Init(void) 
{
    VDAC8_MUX_CR0 = (VDAC8_MUX_MODE_V );

    /* Set default data source */
    #if(VDAC8_MUX_DEFAULT_DATA_SRC != 0 )
        VDAC8_MUX_CR1 = (VDAC8_MUX_DEFAULT_CNTL | VDAC8_MUX_DACBUS_ENABLE) ;
    #else
        VDAC8_MUX_CR1 = (VDAC8_MUX_DEFAULT_CNTL | VDAC8_MUX_DACBUS_DISABLE) ;
    #endif /* (VDAC8_MUX_DEFAULT_DATA_SRC != 0 ) */

    /* Set default strobe mode */
    #if(VDAC8_MUX_DEFAULT_STRB != 0)
        VDAC8_MUX_Strobe |= VDAC8_MUX_STRB_EN ;
    #endif/* (VDAC8_MUX_DEFAULT_STRB != 0) */

    /* Set default range */
    VDAC8_MUX_SetRange(VDAC8_MUX_DEFAULT_RANGE); 

    /* Set default speed */
    VDAC8_MUX_SetSpeed(VDAC8_MUX_DEFAULT_SPEED);
}


/*******************************************************************************
* Function Name: VDAC8_MUX_Enable
********************************************************************************
* Summary:
*  Enable the VDAC8
* 
* Parameters:
*  void
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void VDAC8_MUX_Enable(void) 
{
    VDAC8_MUX_PWRMGR |= VDAC8_MUX_ACT_PWR_EN;
    VDAC8_MUX_STBY_PWRMGR |= VDAC8_MUX_STBY_PWR_EN;

    /*This is to restore the value of register CR0 ,
    which is modified  in Stop API , this prevents misbehaviour of VDAC */
    #if (CY_PSOC5A)
        if(VDAC8_MUX_restoreVal == 1u) 
        {
             VDAC8_MUX_CR0 = VDAC8_MUX_backup.data_value;
             VDAC8_MUX_restoreVal = 0u;
        }
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: VDAC8_MUX_Start
********************************************************************************
*
* Summary:
*  The start function initializes the voltage DAC with the default values, 
*  and sets the power to the given level.  A power level of 0, is the same as
*  executing the stop function.
*
* Parameters:
*  Power: Sets power level between off (0) and (3) high power
*
* Return:
*  void 
*
* Global variables:
*  VDAC8_MUX_initVar: Is modified when this function is called for the 
*  first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void VDAC8_MUX_Start(void)  
{
    /* Hardware initiazation only needs to occure the first time */
    if(VDAC8_MUX_initVar == 0u)
    { 
        VDAC8_MUX_Init();
        VDAC8_MUX_initVar = 1u;
    }

    /* Enable power to DAC */
    VDAC8_MUX_Enable();

    /* Set default value */
    VDAC8_MUX_SetValue(VDAC8_MUX_DEFAULT_DATA); 
}


/*******************************************************************************
* Function Name: VDAC8_MUX_Stop
********************************************************************************
*
* Summary:
*  Powers down DAC to lowest power state.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void VDAC8_MUX_Stop(void) 
{
    /* Disble power to DAC */
    VDAC8_MUX_PWRMGR &= (uint8)(~VDAC8_MUX_ACT_PWR_EN);
    VDAC8_MUX_STBY_PWRMGR &= (uint8)(~VDAC8_MUX_STBY_PWR_EN);

    /* This is a work around for PSoC5A  ,
    this sets VDAC to current mode with output off */
    #if (CY_PSOC5A)
        VDAC8_MUX_backup.data_value = VDAC8_MUX_CR0;
        VDAC8_MUX_CR0 = VDAC8_MUX_CUR_MODE_OUT_OFF;
        VDAC8_MUX_restoreVal = 1u;
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: VDAC8_MUX_SetSpeed
********************************************************************************
*
* Summary:
*  Set DAC speed
*
* Parameters:
*  power: Sets speed value
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void VDAC8_MUX_SetSpeed(uint8 speed) 
{
    /* Clear power mask then write in new value */
    VDAC8_MUX_CR0 &= (uint8)(~VDAC8_MUX_HS_MASK);
    VDAC8_MUX_CR0 |=  (speed & VDAC8_MUX_HS_MASK);
}


/*******************************************************************************
* Function Name: VDAC8_MUX_SetRange
********************************************************************************
*
* Summary:
*  Set one of three current ranges.
*
* Parameters:
*  Range: Sets one of Three valid ranges.
*
* Return:
*  void 
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void VDAC8_MUX_SetRange(uint8 range) 
{
    VDAC8_MUX_CR0 &= (uint8)(~VDAC8_MUX_RANGE_MASK);      /* Clear existing mode */
    VDAC8_MUX_CR0 |= (range & VDAC8_MUX_RANGE_MASK);      /*  Set Range  */
    VDAC8_MUX_DacTrim();
}


/*******************************************************************************
* Function Name: VDAC8_MUX_SetValue
********************************************************************************
*
* Summary:
*  Set 8-bit DAC value
*
* Parameters:  
*  value:  Sets DAC value between 0 and 255.
*
* Return: 
*  void 
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
void VDAC8_MUX_SetValue(uint8 value) 
{
    #if (CY_PSOC5A)
        uint8 VDAC8_MUX_intrStatus = CyEnterCriticalSection();
    #endif /* CY_PSOC5A */

    VDAC8_MUX_Data = value;                /*  Set Value  */

    /* PSOC5A requires a double write */
    /* Exit Critical Section */
    #if (CY_PSOC5A)
        VDAC8_MUX_Data = value;
        CyExitCriticalSection(VDAC8_MUX_intrStatus);
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: VDAC8_MUX_DacTrim
********************************************************************************
*
* Summary:
*  Set the trim value for the given range.
*
* Parameters:
*  range:  1V or 4V range.  See constants.
*
* Return:
*  void
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
void VDAC8_MUX_DacTrim(void) 
{
    uint8 mode;

    mode = (uint8)((VDAC8_MUX_CR0 & VDAC8_MUX_RANGE_MASK) >> 2) + VDAC8_MUX_TRIM_M7_1V_RNG_OFFSET;
    VDAC8_MUX_TR = CY_GET_XTND_REG8((uint8 *)(VDAC8_MUX_DAC_TRIM_BASE + mode));
}


/* [] END OF FILE */
