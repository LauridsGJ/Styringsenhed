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

// Kan kun sende unit16, så for at modtage kommatal skal vi have shiftet dem eller ganget op.

int main()
{
    float TxCmd = 0, RxCmd = 0;       
    CyGlobalIntEnable;          
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */     
    SPIM_1_Start();
 
    TxCmd=0;
    for (;;)     
    {       
    // SPI Write         
    SPIM_1_WriteTxData(TxCmd++);    
    
    // Wait for SPI to complete       
    while(0 == (SPIM_1_ReadTxStatus() & SPIM_1_STS_SPI_DONE))       
    {         
        /* Wait while Master completes transaction -> Polling for SPI_DONE flag! */       
    } 

    // SPI Read.       
    RxCmd = SPIM_1_ReadRxData();             // Process RxCmd...............
    
    LED_Write(RxCmd);                 // Debug -> Toggle LED!            
    CyDelay(1000); 
    
    SPIM_1_ClearFIFO();
    SPIM_1_ClearTxBuffer();
    SPIM_1_ClearRxBuffer();
    }     
    return 0; 
}

/* [] END OF FILE */
