/*******************************************************************************
* File Name: PWM_Timer_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "PWM_Timer.h"

static PWM_Timer_backupStruct PWM_Timer_backup;


/*******************************************************************************
* Function Name: PWM_Timer_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_Timer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PWM_Timer_SaveConfig(void) 
{

    #if(!PWM_Timer_UsingFixedFunction)
        #if(!PWM_Timer_PWMModeIsCenterAligned)
            PWM_Timer_backup.PWMPeriod = PWM_Timer_ReadPeriod();
        #endif /* (!PWM_Timer_PWMModeIsCenterAligned) */
        PWM_Timer_backup.PWMUdb = PWM_Timer_ReadCounter();
        #if (PWM_Timer_UseStatus)
            PWM_Timer_backup.InterruptMaskValue = PWM_Timer_STATUS_MASK;
        #endif /* (PWM_Timer_UseStatus) */

        #if(PWM_Timer_DeadBandMode == PWM_Timer__B_PWM__DBM_256_CLOCKS || \
            PWM_Timer_DeadBandMode == PWM_Timer__B_PWM__DBM_2_4_CLOCKS)
            PWM_Timer_backup.PWMdeadBandValue = PWM_Timer_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(PWM_Timer_KillModeMinTime)
             PWM_Timer_backup.PWMKillCounterPeriod = PWM_Timer_ReadKillTime();
        #endif /* (PWM_Timer_KillModeMinTime) */

        #if(PWM_Timer_UseControl)
            PWM_Timer_backup.PWMControlRegister = PWM_Timer_ReadControlRegister();
        #endif /* (PWM_Timer_UseControl) */
    #endif  /* (!PWM_Timer_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_Timer_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_Timer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_Timer_RestoreConfig(void) 
{
        #if(!PWM_Timer_UsingFixedFunction)
            #if(!PWM_Timer_PWMModeIsCenterAligned)
                PWM_Timer_WritePeriod(PWM_Timer_backup.PWMPeriod);
            #endif /* (!PWM_Timer_PWMModeIsCenterAligned) */

            PWM_Timer_WriteCounter(PWM_Timer_backup.PWMUdb);

            #if (PWM_Timer_UseStatus)
                PWM_Timer_STATUS_MASK = PWM_Timer_backup.InterruptMaskValue;
            #endif /* (PWM_Timer_UseStatus) */

            #if(PWM_Timer_DeadBandMode == PWM_Timer__B_PWM__DBM_256_CLOCKS || \
                PWM_Timer_DeadBandMode == PWM_Timer__B_PWM__DBM_2_4_CLOCKS)
                PWM_Timer_WriteDeadTime(PWM_Timer_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(PWM_Timer_KillModeMinTime)
                PWM_Timer_WriteKillTime(PWM_Timer_backup.PWMKillCounterPeriod);
            #endif /* (PWM_Timer_KillModeMinTime) */

            #if(PWM_Timer_UseControl)
                PWM_Timer_WriteControlRegister(PWM_Timer_backup.PWMControlRegister);
            #endif /* (PWM_Timer_UseControl) */
        #endif  /* (!PWM_Timer_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWM_Timer_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_Timer_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM_Timer_Sleep(void) 
{
    #if(PWM_Timer_UseControl)
        if(PWM_Timer_CTRL_ENABLE == (PWM_Timer_CONTROL & PWM_Timer_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWM_Timer_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWM_Timer_backup.PWMEnableState = 0u;
        }
    #endif /* (PWM_Timer_UseControl) */

    /* Stop component */
    PWM_Timer_Stop();

    /* Save registers configuration */
    PWM_Timer_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_Timer_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_Timer_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_Timer_Wakeup(void) 
{
     /* Restore registers values */
    PWM_Timer_RestoreConfig();

    if(PWM_Timer_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWM_Timer_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
