//******************************************************************************
//  D. Dang
//  Texas Instruments, Inc
//  October 2010
//  Built with CCS Version 4.2.0 and IAR Embedded Workbench Version: 5.10
//******************************************************************************

#include  <msp430g2231.h>
#include  <signal.h>
#include  <stdlib.h>
#include  "defs.h"

#define genRand02()  (rand ()%tSampleMs + (tSampleMs));
#define genRand03()  (rand ()%tSampleMs) + tSampleMs/2;


void main (){
  unsigned long int tSampleMs, auxTimeMs;

  WDTCTL = WDTPW + WDTHOLD;                // Stop watchdog timer
  P1DIR |= 0x40 + TXD + APC220_CTL;                           // Set P1.0  y P1.6 to output direction
  P1SEL |= TXD;// + APC220_CTL;
  
  //P1OUT = 0x00;

    ConfigureAdcTempSensor();

    __enable_interrupt();                     // Enable interrupts.

    BCSCTL1 |= DIVA_0;                               // ACLK / 8
    BCSCTL2 |= SELM_3 + DIVM_3 + SELS + DIVS_3;               // MCLK = LFXT1/8
    BCSCTL3 |= LFXT1S_2;                      // LFXT1 = VLO
    IFG1 &= ~OFIFG;                           // Clear OSCFault flag
    __bis_SR_register(SCG1 + SCG0);           // Stop DCO


    CCTL1 = CCIE;                            // interrupt enabled CC1
    CCR1 = dlyCC1;
    TACTL = TASSEL_1 + MC_2;                 // ACLK, upmode
   
    srand(deviceID); 
    
  //
  // 60000 ciclos 5 segundos
  // 12000 ciclos 1 segundo
  //
  // 12    ciclos 1 mS
  //
  sampleTimeSec =  5;
  tSampleMs = sampleTimeSec * 1000;

  auxTimeMs = genRand03();
  int i;
  while(1){
    if (auxTimeMs > minTime) {
         P1OUT |= 0x01;                           // 0100|0001 = 0x41 pone en 1 P1.0 y P1.6
         P1OUT &= ~0x01;                           // 0100|0001 = 0x41 pone en 1 P1.0 y P1.6
      auxTimeMs = auxTimeMs - minTime;
      _BIS_SR(LPM3_bits + GIE);                // Enter LPM3 w/ interrupt
    }else {
      if (auxTimeMs == 0){
         CCTL1 &= ~CCIE;                            // interrupt disabled CC1
         setClockTrans();

         auxTimeMs = genRand03();

         P1OUT |= 0x41;                           // 0100|0001 = 0x41 pone en 1 P1.0 y P1.6
         //for (i = 0; i < 200; i++) __delay_cycles(500);
         ADCValue = adqAdcTempSensor();

         TransmitADCValue (deviceID);
         P1OUT &= ~0x41;                          // 1011|1110 = 0xFE pone en 0 P1.0 

         CCTL0 &= ~CCIE;                            // interrupt disabled CC0
         CCR1 = dlyCC1;
         setVloClk();
 
     } else {
       CCR1 = auxTimeMs * 12;
       auxTimeMs = 0;
       _BIS_SR(LPM3_bits + GIE);                // Enter LPM3 w/ interrupt
     }
    }
  }
}


// Timer A1 interrupt service routine
interrupt (TIMERA1_VECTOR) Timer_A1 (void)
{
//   TACCTL1 &= ~CCIFG;                         /* Capture/compare interrupt flag */
   switch( TAIV )
     {
       case 10: 
       break;
       case 2:
       CCR1 += dlyCC1;
       // TAR = 0;
       _BIC_SR_IRQ(LPM3_bits);                   // Clear LPM3 bits from 0(SR)
       break;
       case  4: 
       break;
   }
}


void setVloClk (void){

    BCSCTL1 |= DIVA_0;                               // ACLK / 8
    BCSCTL2 |= SELM_3 + DIVM_3 + SELS + DIVS_3;               // MCLK = LFXT1/8
    BCSCTL3 |= LFXT1S_2;                      // LFXT1 = VLO
    IFG1 &= ~OFIFG;                           // Clear OSCFault flag
    __bis_SR_register(SCG1 + SCG0);           // Stop DCO


    CCTL1 = CCIE;                            // interrupt enabled CC1
    CCR1 = dlyCC1;
    TACTL = TASSEL_1 + MC_2;                 // ACLK, upmode

}

void setClockTrans(){

    BCSCTL1 = CALBC1_1MHZ;           // Set range
    DCOCTL = CALDCO_1MHZ;            // SMCLK = DCO = 1MHz
    //BCSCTL2 |= SELM_1 + DIVM_0;               // MCLK = LFXT1/8
    BCSCTL2 = 0x00;               // MCLK = LFXT1/8

    //CCTL0 = CCIE;                            // interrupt enabled CC1
    //CCR0 = dlyCC0;
    //TACTL = TASSEL_2 + MC_2;                 // SMCLK, upmode

}
