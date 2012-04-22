/******************************************************************************
 *                  MSP-EXP430G2-LaunchPad Software UART Transmission
 * 
 * Original Code: From MSP-EXP430G2-LaunchPad User Experience Application
 * Original Author: Texas Instruments
 *  
 * Description: This code shows the minimum neeed to send data over a software 
 *     UART pin (P1.1). This is a highly condenced and modified version
 *     of the User Experience Application which comes programmed with
 *     the LaunchPad.
 * 
 * Modified by Nicholas J. Conn - http://msp430launchpad.blogspot.com
 * Date Modified: 07-25-10
 ******************************************************************************/
   
//#include  "msp430g2231.h"
#include  <signal.h>
#include "stdbool.h"
 
#define     TXD            BIT1                      // TXD on P1.1
#define     Bitime         104 //9600 Baud, SMCLK=1MHz (1MHz/9600)=104
#define     APC220_CTL     BIT0  // P1.0 al Pin 3 Sleep del transceiver APC220

unsigned char BitCnt;  // Bit count, used when transmitting byte
unsigned int TXByte;  // Value sent over UART when Transmit() is called

/* Using an 8-value moving average filter on sampled ADC values */
long tempMeasured[8];
unsigned char tempMeasuredPosition=0;
long tempAverage;

long tempCalibrated;

// Function Definitions
void Transmit(void);
void transChar(unsigned char c);
void setClockTrans();
void setVlo ();
void ConfigureAdcTempSensor(void);

#include "transmitADCValue.c"

int main (){

  unsigned char i;

  WDTCTL = WDTPW + WDTHOLD;              // Stop WDT
  setClockTrans();
  __bis_SR_register(GIE);                // interrupts enabled 

  P1SEL |= TXD + APC220_CTL;             //
  P1DIR |= TXD + APC220_CTL;             //
  P1REN |=  APC220_CTL;             //

  //P1OUT &= ~ BIT0;
  P1OUT = 0x00;

  ConfigureAdcTempSensor();

  __enable_interrupt();                     // Enable interrupts.

  while(1)
  {  
    ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start
    __bis_SR_register(CPUOFF + GIE);        // LPM0 with interrupts enabled

    /* Moving average filter out of 8 values to somewhat stabilize sampled ADC */
    tempMeasured[tempMeasuredPosition++] = ADC10MEM;
    if (tempMeasuredPosition == 8)
      tempMeasuredPosition = 0;
    tempAverage = 0;
    for (i = 0; i < 8; i++)
      tempAverage += tempMeasured[i];
    tempAverage >>= 3;

    ADCValue = tempAverage;
    // Habilitacion del APC220 para transmitir
    //P1OUT |=  BIT0;
    P1OUT =  0x01;
    //  Se necesita un tiempo de 50 ms para iniciar transmision luego de poner en 1 EN y SET 
    //  en APC220
    for (i = 0; i < 100; i++)
      __delay_cycles(500);

    TransmitADCValue ();    
 
    // Des-Habilitacion del APC220 para transmitir
    //P1OUT &= ~ BIT0;
    P1OUT = 0x00;
     
    //TXByte = 65;
    //Transmit(); 
    setVlo ();
    _BIS_SR(LPM3_bits + GIE);               // Enter LPM3
  }
}
 
void setClockTrans()
{
  BCSCTL1 = CALBC1_1MHZ;           // Set range
  DCOCTL = CALDCO_1MHZ;            // SMCLK = DCO = 1MHz
}

// Function Transmits Character from TXByte 
void Transmit()
{ 
  CCTL0 = OUT;                               // TXD Idle as Mark
  TACTL = TASSEL_2 + MC_2;               // SMCLK, continuous mode
 
  BitCnt = 0xA;                       // Load Bit counter, 8 bits + ST/SP
  CCR0 = TAR;
   
  CCR0 += Bitime;                  // Set time till first bit
  TXByte |= 0x100;                 // Add stop bit to TXByte (which is logical 1)
  TXByte = TXByte << 1;            // Add start bit (which is logical 0)
   
  CCTL0 =  CCIS0 + OUTMOD0 + CCIE; // Set signal, intial value, enable interrupts
  while ( CCTL0 & CCIE );          // Wait for TX completion
  TACTL = TASSEL_2;             // SMCLK, timer off (for power consumption)
}
 
void setVlo (){
  BCSCTL1 |= DIVA_3;                        // ACLK/2
  BCSCTL3 |= LFXT1S_2;                      // ACLK = VLO
  WDTCTL = WDT_ADLY_1000;                   // Interval timer
  IE1 |= WDTIE;                             // Enable WDT interrupt
}

// This function simply performs a software delay, hard from efficient but it's practical in this case.
void delay_ms(unsigned int ms ) { 

	unsigned int i;
	for (i = 0; i <= ms; i++) { 
// Make sure your < and = has no space in between (the syntax parser seems to be messing things up)
		__delay_cycles(500); 
// This should be dependent on clock speed... but what the hell, even the loop itself should be taken into account...
	}
}


/* Configure ADC Temp Sensor Channel */
void ConfigureAdcTempSensor(void)
{
  unsigned char i;
  ADC10CTL1 = INCH_10 + ADC10DIV_3;         // Temp Sensor ADC10CLK/4
  ADC10CTL0 = SREF_1 + ADC10SHT_3 + REFON + ADC10ON + ADC10IE;
  __delay_cycles(1000);                     // Wait for ADC Ref to settle

  ADC10CTL0 |= ENC + ADC10SC;               // Sampling and conversion start
  __bis_SR_register(CPUOFF + GIE);          // LPM0 with interrupts enabled
  tempCalibrated = ADC10MEM;
  for (i=0; i < 8; i++)
    tempMeasured[i] = tempCalibrated;
  tempAverage = tempCalibrated;
}

interrupt (WDT_VECTOR) watchdog_timer (void)
{
   setClockTrans();
  _BIC_SR_IRQ(LPM3_bits);                   // Clear LPM3 bits from 0(SR)
}


// ADC10 interrupt service routine
// -------- CCS & IAR convention
//#pragma vector=ADC10_VECTOR
//__interrupt void ADC10_ISR (void)
interrupt (ADC10_VECTOR) ADC10_ISR(void)
{
  __bic_SR_register_on_exit(CPUOFF);        // Return to active mode
}

// Timer A0 interrupt service routine
//#pragma vector=TIMERA0_VECTOR
interrupt (TIMERA0_VECTOR) Timer_A (void)
{
  CCR0 += Bitime;     // Add Offset to CCR0  
  if ( BitCnt == 0)     // If all bits TXed, disable interrupt
    CCTL0 &= ~ CCIE ;
  else
  {
    CCTL0 |=  OUTMOD2;                    // TX Space
    if (TXByte & 0x01)
      CCTL0 &= ~ OUTMOD2;                   // TX Mark
    TXByte = TXByte >> 1;
    BitCnt --;
  }
}
