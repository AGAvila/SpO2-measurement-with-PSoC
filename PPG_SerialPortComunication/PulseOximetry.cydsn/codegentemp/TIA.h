/*******************************************************************************
* File Name: TIA.h
* Version 2.0
*
* Description:
*  This file contains the function prototypes and constants used in
*  the TIA User Module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_TIA_TIA_H) 
#define CY_TIA_TIA_H 

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h"

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component TIA_v2_0 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


#if(!CY_PSOC5A)
    #if(CYDEV_VARIABLE_VDDA == 1)
        #if (!defined(CY_LIB_SC_BST_CLK_EN))
            #error Component TIA_v2_0 requires cy_boot v3.30 or later
        #endif /* (!defined(CY_LIB_SC_BST_CLK_EN)) */
    #endif /* CYDEV_VARIABLE_VDDA == 1 */
#endif /* (!CY_PSOC5A) */

/***************************************
*   Data Struct Definition
***************************************/

/* Low power Mode API Support */
typedef struct
{
    uint8   enableState;
    uint8   scCR0reg;
    uint8   scCR1Reg;
    uint8   scCR2Reg;
}TIA_BACKUP_STRUCT;

/* Variable describes init state of the component */
extern uint8 TIA_initVar;


/***************************************
*        Function Prototypes
***************************************/

void TIA_Start(void)                  ;
void TIA_Stop(void)                   ;
void TIA_SetPower(uint8 power)        ;
void TIA_SetResFB(uint8 res_feedback) ;
void TIA_SetCapFB(uint8 cap_feedback) ;
void TIA_Sleep(void)                  ;
void TIA_Wakeup(void)                 ;
void TIA_SaveConfig(void)             ;
void TIA_RestoreConfig(void)          ;
void TIA_Init(void)                   ;
void TIA_Enable(void)                 ;


/***************************************
*           API Constants
***************************************/

/* Power constants for SetPower function */
#define TIA_MINPOWER                   (0x00u)
#define TIA_LOWPOWER                   (0x01u)
#define TIA_MEDPOWER                   (0x02u)
#define TIA_HIGHPOWER                  (0x03u)

/* Constants for SetResFB function */
#define TIA_RES_FEEDBACK_20K           (0x00u)
#define TIA_RES_FEEDBACK_30K           (0x01u)
#define TIA_RES_FEEDBACK_40K           (0x02u)
#define TIA_RES_FEEDBACK_80K           (0x03u)
#define TIA_RES_FEEDBACK_120K          (0x04u)
#define TIA_RES_FEEDBACK_250K          (0x05u)
#define TIA_RES_FEEDBACK_500K          (0x06u)
#define TIA_RES_FEEDBACK_1000K         (0x07u)
#define TIA_RES_FEEDBACK_MAX           (0x07u)

/* Constants for SetCapFB function */
#define TIA_CAP_FEEDBACK_NONE          (0x00u)
#define TIA_CAP_FEEDBACK_1_3PF         (0x01u)
#define TIA_CAP_FEEDBACK_3_3PF         (0x02u)
#define TIA_CAP_FEEDBACK_4_6PF         (0x03u)
#define TIA_CAP_FEEDBACK_MAX           (0x03u)


/***************************************
*       Initial Paramater Values
***************************************/

#define TIA_INIT_POWER                 (1u)
#define TIA_INIT_RES_FEEDBACK          (7u)
#define TIA_INIT_CAP_FEEDBACK          (3u)


/***************************************
*              Registers
***************************************/

#define TIA_CR0_REG                    (* (reg8 *) TIA_SC__CR0 )
#define TIA_CR0_PTR                    (  (reg8 *) TIA_SC__CR0 )
#define TIA_CR1_REG                    (* (reg8 *) TIA_SC__CR1 )
#define TIA_CR1_PTR                    (  (reg8 *) TIA_SC__CR1 )
#define TIA_CR2_REG                    (* (reg8 *) TIA_SC__CR2 )
#define TIA_CR2_PTR                    (  (reg8 *) TIA_SC__CR2 )
/* Power manager */
#define TIA_PM_ACT_CFG_REG             (* (reg8 *) TIA_SC__PM_ACT_CFG )
#define TIA_PM_ACT_CFG_PTR             (  (reg8 *) TIA_SC__PM_ACT_CFG )
#define TIA_PM_STBY_CFG_REG            (* (reg8 *) TIA_SC__PM_STBY_CFG )
#define TIA_PM_STBY_CFG_PTR            (  (reg8 *) TIA_SC__PM_STBY_CFG )
/* SC Boost Clk Control */
#define TIA_BSTCLK_REG                 (* (reg8 *) TIA_SC__BST )
#define TIA_BSTCLK_PTR                 (  (reg8 *) TIA_SC__BST )
/* Pump Register for SC block */
#define TIA_SC_MISC_REG                (* (reg8 *) CYDEV_ANAIF_RT_SC_MISC)
#define TIA_SC_MISC_PTR                (  (reg8 *) CYDEV_ANAIF_RT_SC_MISC)
/* Pump clock selectin register */
#define TIA_PUMP_CR1_REG               (* (reg8 *) CYDEV_ANAIF_CFG_PUMP_CR1)
#define TIA_PUMP_CR1_PTR               (  (reg8 *) CYDEV_ANAIF_CFG_PUMP_CR1)

/* PM_ACT_CFG (Active Power Mode CFG Register) mask */ 
#define TIA_ACT_PWR_EN                 TIA_SC__PM_ACT_MSK 

/* PM_STBY_CFG (Alternative Active Power Mode CFG Register) mask */ 
#define TIA_STBY_PWR_EN                TIA_SC__PM_STBY_MSK 

/*Backward Compatibility*/
#define TIA_CR0                        TIA_CR0_REG
#define TIA_CR1                        TIA_CR1_REG
#define TIA_CR2                        TIA_CR2_REG
#define TIA_BSTCLK                     TIA_BSTCLK_REG
#define TIA_PWRMGR                     TIA_PM_ACT_CFG_REG
#define TIA_SC_MISC                    TIA_SC_MISC_REG


/***************************************
*         Register constants        
***************************************/

/* SC_MISC constants */
#define TIA_PUMP_FORCE                 (0x20u)
#define TIA_PUMP_AUTO                  (0x10u)
#define TIA_DIFF_PGA_1_3               (0x02u)
#define TIA_DIFF_PGA_0_2               (0x01u)

/* ANIF.PUMP.CR1 Constants */
#define TIA_PUMP_CR1_SC_CLKSEL         (0x80u)

/* CR0 SC/CT Control Register 0 definitions */

/* Bit Field SC_MODE_ENUM - SCxx_CR0[3:1], TIA Mode = 3b'001' */
#define TIA_MODE_TIA                   (uint8)(0x01u << 1)

/* CR1 SC/CT Control Register 1 definitions */

/* Bit Field  SC_DRIVE_ENUM - SCxx_CR1[1:0] */
#define TIA_DRIVE_MASK                 (0x03u)
#define TIA_DRIVE_280UA                (0x00u)
#define TIA_DRIVE_420UA                (0x01u)
#define TIA_DRIVE_530UA                (0x02u)
#define TIA_DRIVE_650UA                (0x03u)

/* Bit Field  SC_COMP_ENUM - SCxx_CR1[3:2] */
#define TIA_COMP_MASK                  (uint8)(0x03u << 2)
#define TIA_COMP_3P0PF                 (uint8)(0x00u << 2)
#define TIA_COMP_3P6PF                 (uint8)(0x01u << 2)
#define TIA_COMP_4P35PF                (uint8)(0x02u << 2)
#define TIA_COMP_5P1PF                 (uint8)(0x03u << 2)

/* Bit Field  SC_DIV2_ENUM - SCxx_CR1[4] - n/a for TIA mode */
#define TIA_DIV2                       (uint8)(0x01u << 4)
#define TIA_DIV2_DISABLE               (uint8)(0x00u << 4)
#define TIA_DIV2_ENABLE                (uint8)(0x01u << 4)

/* Bit Field  SC_GAIN_ENUM - SCxx_CR1[5] - n/a for TIA mode] */
#define TIA_GAIN                       (uint8)(0x01u << 5)
#define TIA_GAIN_0DB                   (uint8)(0x00u << 5)
#define TIA_GAIN_6DB                   (uint8)(0x01u << 5)

/* CR2 SC/CT Control Register 2 definitions */

/* Bit Field  SC_BIAS_CONTROL_ENUM - SCxx_CR2[0] */
#define TIA_BIAS                       (0x01u)
#define TIA_BIAS_NORMAL                (0x00u)
#define TIA_BIAS_LOW                   (0x01u)

/* Bit Field  SC_R20_40B_ENUM - SCxx_CR2[1] - n/a for TIA mode */
#define TIA_R20_40B_MASK               (uint8)(0x01u << 1)
#define TIA_R20_40B_40K                (uint8)(0x00u << 1)
#define TIA_R20_40B_20K                (uint8)(0x01u << 1)

/* Bit Field  SC_REDC_ENUM  - SCxx_CR2[3:2] */
#define TIA_REDC_MASK                  (uint8)(0x03u << 2)
#define TIA_REDC_00                    (uint8)(0x00u << 2)
#define TIA_REDC_01                    (uint8)(0x02u << 2)
#define TIA_REDC_10                    (uint8)(0x04u << 2)
#define TIA_REDC_11                    (uint8)(0x03u << 2)

/* Bit Field  SC_RVAL_ENUM  - SCxx_CR2[6:4] */
#define TIA_RVAL_MASK                  (uint8)(0x07u << 4)
#define TIA_RVAL_20K                   (uint8)(0x00u << 4)
#define TIA_RVAL_30K                   (uint8)(0x01u << 4)
#define TIA_RVAL_40K                   (uint8)(0x02u << 4)
#define TIA_RVAL_60K                   (uint8)(0x03u << 4)
#define TIA_RVAL_120K                  (uint8)(0x04u << 4)
#define TIA_RVAL_250K                  (uint8)(0x05u << 4)
#define TIA_RVAL_500K                  (uint8)(0x06u << 4)
#define TIA_RVAL_1000K                 (uint8)(0x07u << 4)

/* Bit Field  SC_PGA_GNDVREF_ENUM - SCxx_CR2[7] - n/a for TIA mode */
#define TIA_GNDVREF                    (uint8)(0x01u << 7)
#define TIA_GNDVREF_DI                 (uint8)(0x00u << 7)
#define TIA_GNDVREF_E                  (uint8)(0x01u << 7)

/* SC Blook Boost Clock Selection Register - Boost Clock Enable  SCxx_BST[3] */
#define TIA_BST_CLK_EN                 (uint8)(0x01u << 3)
#define TIA_BST_CLK_INDEX_MASK         (0x07u)
#define TIA_PM_ACT_CFG_MASK            (0x0Fu)

/* Constant for VDDA Threshold */
#define TIA_CYDEV_VDDA_MV              (CYDEV_VDDA_MV)
#define TIA_MINIMUM_VDDA_THRESHOLD_MV  (2700u)

/*******************************************************************************
* Following code are OBSOLETE and must not be used starting from TIA 2.0
*******************************************************************************/
#define TIA_SC_REG_CLR                 (0x00u)

#endif /* CY_TIA_TIA_H */


/* [] END OF FILE */
