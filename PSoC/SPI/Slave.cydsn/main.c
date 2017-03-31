/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"

CY_ISR(isr_Slave) 
{     
    uint8 i, j, buf[8];     
    float modtaget = 0;
    
//    j = SPIS_1_GetRxBufferSize();          // SPI Read data from SPIS RX software buffer to buf     
//    
//    for(i=0u; i<j; i++)     
//    {         
//        buf[i] = SPIS_1_ReadRxData();     
//    }        
    
    modtaget = SPIS_1_ReadRxData();
    
//    if (j>0)  // Process data received....     
//    {         
//        // Send last command back to master at next transaction!         
        SPIS_1_WriteTxData(modtaget);         
//    }          
    
    LED_Write(modtaget);  // Debug -> Toggle LED!  
    
    // Clear Rx Interrupt Source     
    SPIS_1_ClearFIFO();
    SPIS_1_ClearRxBuffer();
    SPIS_1_ClearTxBuffer();    
    
    // SPIS_ClearRxInterruptSource(source); 
} 
 
int main() 
{     
    CyGlobalIntEnable;             
    isr_SPI_StartEx(isr_Slave);   
    SPIS_1_Start();
    
    for(;;)     
    {         
        // Do nothing!!!     
    } 
    
    return 0;
} 

/* [] END OF FILE */
