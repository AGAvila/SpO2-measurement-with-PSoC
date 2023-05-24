/*
This program allows the acquisition of the SpO2 using 2 LEDs and 1 photodiode
*/

#include "project.h"
#include <math.h>
#include <stdbool.h>

#define LED_ON 0u
#define LED_OFF 1u
#define LENGTH_ALL_SAMPLES 2000        // Length of the array send from DMA2
#define LENGTH_SEPARATED_SAMPLES 8000  // Length of the complete array of samples for one of the LEDs
#define A 110                          // Coeficients used to calculate R
#define B 25

volatile uint16 samples1[LENGTH_ALL_SAMPLES];
volatile uint16 samples2[LENGTH_ALL_SAMPLES];

bool send_flag = false;           // Control if the value of R is ready
bool acquisition_active = false;  // Control if the adquisition of values is ON

uint16 RED_samples[LENGTH_SEPARATED_SAMPLES]; // Stores samples only from the RED LED
uint16 IR_samples[LENGTH_SEPARATED_SAMPLES];  // Stores samples only from the IR LED
uint16 R = 0;                                 // Ratio of absorbance
uint16 count = 0;                             // Count how many times 2000 samples has been stored  

float last_measure = 0;  // Measure from the last adquisition  

// Variables declaration for DMA_1 and DMA_2
uint8 DMA_1_Chan;
uint8 DMA_1_TD[1];
uint8 DMA_2_Chan;
uint8 DMA_2_TD[2];


void DMA_1_Init(){
    /* Defines for DMA_1 */

    #define DMA_1_BYTES_PER_BURST 2
    #define DMA_1_REQUEST_PER_BURST 1
    #define DMA_1_SRC_BASE (CYDEV_PERIPH_BASE)
    #define DMA_1_DST_BASE (CYDEV_PERIPH_BASE)

    /* DMA Configuration for DMA_1 */
    DMA_1_Chan = DMA_1_DmaInitialize(DMA_1_BYTES_PER_BURST, DMA_1_REQUEST_PER_BURST, 
        HI16(DMA_1_SRC_BASE), HI16(DMA_1_DST_BASE));
    DMA_1_TD[0] = CyDmaTdAllocate();
    CyDmaTdSetConfiguration(DMA_1_TD[0], 2, DMA_1_TD[0], 0);
    CyDmaTdSetAddress(DMA_1_TD[0], LO16((uint32)ADC_DelSig_DEC_SAMP_PTR), LO16((uint32)Filter_1_STAGEA_PTR));
    CyDmaChSetInitialTd(DMA_1_Chan, DMA_1_TD[0]);
    CyDmaChEnable(DMA_1_Chan, 1);
}


void DMA_2_Init(){
   /* Defines for DMA_2 */
    
    #define DMA_2_BYTES_PER_BURST 2
    #define DMA_2_REQUEST_PER_BURST 1
    #define DMA_2_SRC_BASE (CYDEV_PERIPH_BASE)
    #define DMA_2_DST_BASE (CYDEV_SRAM_BASE)

    /* DMA Configuration for DMA_2 */
    DMA_2_Chan = DMA_2_DmaInitialize(DMA_2_BYTES_PER_BURST, DMA_2_REQUEST_PER_BURST, 
        HI16(DMA_2_SRC_BASE), HI16(DMA_2_DST_BASE));
    DMA_2_TD[0] = CyDmaTdAllocate();
    DMA_2_TD[1] = CyDmaTdAllocate();
    CyDmaTdSetConfiguration(DMA_2_TD[0], 4000, DMA_2_TD[1], DMA_2__TD_TERMOUT_EN | CY_DMA_TD_INC_DST_ADR);
    CyDmaTdSetConfiguration(DMA_2_TD[1], 4000, DMA_2_TD[0], DMA_2__TD_TERMOUT_EN | CY_DMA_TD_INC_DST_ADR);
    CyDmaTdSetAddress(DMA_2_TD[0], LO16((uint32)Filter_1_HOLDA_PTR), LO16((uint32)&samples1[0]));
    CyDmaTdSetAddress(DMA_2_TD[1], LO16((uint32)Filter_1_HOLDA_PTR), LO16((uint32)&samples2[0]));
    CyDmaChSetInitialTd(DMA_2_Chan, DMA_2_TD[0]);
}


float calculateMean (uint16 samples_array[]){
    /* Calculates the mean of the samples vector
    
    Inputs -> 
    - Array of samples for one light
    */
    
    uint32 sum = 0;
    
    for(int i = 0; i < LENGTH_SEPARATED_SAMPLES; i++){
        sum += samples_array[i]; 
    }
    
    return (float) sum/LENGTH_SEPARATED_SAMPLES;
}


float calculateRMS (uint16 samples_array[], float DC){
    /* Calculates the RMS of the signal 
    
    Inputs ->
    - Array of samples from the filter
    - Mean of the samples
    */
    
    uint32 sum = 0;
    
    for(int i = 0; i < LENGTH_SEPARATED_SAMPLES; i++){
        sum += pow(samples_array[i] - DC, 2);
    }
    
    return (float) sqrt(sum/LENGTH_SEPARATED_SAMPLES);
}


float calculateOxygen(){
    /* Calculate the percentaje of oxigen in blood using the coef R (ratio of ratios) */
    
    float DC_RED, DC_IR, AC_RED, AC_IR;
    
    DC_RED = calculateMean(RED_samples);
    DC_IR = calculateMean(IR_samples);
    
    AC_RED = calculateRMS(RED_samples, DC_RED);
    AC_IR = calculateRMS(IR_samples, DC_IR);
    
    return A - (B * (AC_RED/DC_RED) / (AC_IR/DC_IR));
}


CY_ISR(UARTInput){
    /* Recieved the start order from the UART conection. This interrupt is call when 
    an instruction is received from the BLE module */
    
    char order;
    
     if (UART_1_ReadRxStatus() & (uint8)UART_1_RX_STS_FIFO_NOTEMPTY){
        order = (char)UART_1_ReadRxData();
        
        switch(order){
            case 'a':
                UART_1_PutString("Starting Adquisition...\r\n");
                
                Filter_1_ClearInterruptSource();
                CyDmaChEnable(DMA_2_Chan, 1);
                
                // Both LEDs turn off at the start
                Out1_1_Write(LED_ON);
                Out1_2_Write(LED_OFF);
                
                count = 0;  // Restart timer counter
                last_measure = 0;
                acquisition_active = true;
                
                break;
                
            case 's':
                UART_1_PutString("Stopping Adquisition...\r\n");
                
                Out1_1_Write(LED_OFF);
                Out1_2_Write(LED_OFF);
                
                CyDmaChDisable(DMA_2_Chan);
                
                acquisition_active = false;
                
                break;
                
        } // end switch    
    } 
    
    UART_1_ClearRxBuffer();
}


CY_ISR(FilterDone){
    /* Stores the data from each LED in a different array. 
    
    This interrupt is call each time the filter has send 4000 bytes, so this interrupt is call 
    each 1 seconds (2000 samples/second of 2 bytes/sample). */
    
    static uint16 i, j, last_index = 0; 
    float R_aux;
    
    // Turn ON LED IR
    if(count == 4 && acquisition_active){ 
        Out1_1_Write(LED_OFF); // RED
        Out1_2_Write(LED_ON);  // IR
    }
    
    // Fill samples arrays
    if(count % 2 == 0 && count < 8){ // "count" is even
        j = 0;
        for(i = last_index; i < last_index + LENGTH_ALL_SAMPLES; i++){ 
            if(count <= 3){  // Red
                RED_samples[i] = samples1[j]; 
            }
            else{  // IR
                //select_LED = LED_IR;
                IR_samples[i] = samples1[j];
            }
            j++;
        } // end for
        
        last_index += LENGTH_ALL_SAMPLES;
        count++;
        
        if(count > 3){ // Reset the index of the IR LED array
            last_index = 0;
        }
    }
    
    else if(count % 2 != 0 && count < 8){ // "count" is odd
        j = 0;
        for(i = last_index; i < last_index + LENGTH_ALL_SAMPLES; i++){ 
            if(count <= 3){  // Red
                RED_samples[i] = samples2[j]; 
            }
            else{  // IR
                IR_samples[i] = samples2[j];
            }
            j++;
        } // end for
        
        // If 8 seconds has passed
        if(count == 7){ 
            
            // Activates the sending flag
            send_flag = true;
            
            // Reset samples acquisition
            last_index = 0;
            if(acquisition_active){
                Out1_1_Write(LED_ON);
                Out1_2_Write(LED_OFF);
            }
            
            // Calculate R            
            R_aux = calculateOxygen();
            R = 0.8 * R_aux + 0.2 * last_measure;  // Feeds the value of previous measures
            
            last_measure = R;   // Saves the result for the next acquisition
            count = 0;          // Restart the loop
            
            if((R > 100 || R < 95) && acquisition_active){
                UART_1_PutString("Error in the measure\r\n");
            }
        }
        
        last_index += LENGTH_ALL_SAMPLES;
        count++;
    }
    
} 


int main(void){
    CyGlobalIntEnable;  // Enable global interrupts
 
    uint8 uart_array[2];
    
    // Initialize the hardware components
    TIA_Start(); 
    ADC_DelSig_Start();
    ADC_DelSig_StartConvert();
    UART_1_Start();
    Filter_1_Start();
    
    Filter_1_SetCoherency(Filter_1_CHANNEL_A,Filter_1_KEY_MID);
    
    DMA_1_Init();
    DMA_2_Init();
    
    Out1_1_Write(LED_OFF);  // RED
    Out1_2_Write(LED_OFF);  // IR
    
    // Initialize interrupts
    isr_UART_StartEx(UARTInput);
    isr_Filter_End_StartEx(FilterDone);
    
    UART_1_PutString("UART Comunication: ON LINE\r\n");
    
    // Main loop
    for(;;){
        if(send_flag == true && acquisition_active){
            
            UART_1_PutString("R: ");
            
            send_flag = false;

            // Separate bytes from R
            uart_array[0] = R >> 8 ;
            uart_array[1] = (uint8) R;
            
            // Send result
            UART_1_PutArray(uart_array, (uint8) 2);
            
            UART_1_PutString("\r\n");
        }
    } 
   
}
