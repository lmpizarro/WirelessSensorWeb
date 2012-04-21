/******************************************************************************
 *                 Half Duplex Software UART on the LaunchPad
 * 
 * Description: This code provides a simple Bi-Directional Half Duplex
 * 		Software UART. The timing is dependant on SMCLK, which
 * 		is set to 1MHz. The transmit function is based off of
 * 		the example code provided by TI with the LaunchPad.
 * 		This code was originally created for "NJC's MSP430
 * 		LaunchPad Blog".
 * 
 * Author: Nicholas J. Conn - http://msp430launchpad.com
 * Email: webmaster at msp430launchpad.com
 * Date: 08-17-10
 ******************************************************************************/
  
#include	"msp430g2231.h"
#include	"stdbool.h"

#define		TXD             BIT1    // TXD on P1.1
#define		RXD		BIT2	// RXD on P1.2

#define     	Bit_time    	104		// 9600 Baud, SMCLK=1MHz (1MHz/9600)=104
#define		Bit_time_5	52		// Time for half a bit.

unsigned char BitCnt;		// Bit count, used when transmitting byte
unsigned int TXByte;		// Value sent over UART when Transmit() is called
unsigned int RXByte;		// Value recieved once hasRecieved is set

bool isReceiving;		// Status for when the device is receiving
bool hasReceived;		// Lets the program know when a byte is received

// Function Definitions
void Transmit(void);

void main(void)
{
	WDTCTL = WDTPW + WDTHOLD;		// Stop WDT
  
	BCSCTL1 = CALBC1_1MHZ;			// Set range
	DCOCTL = CALDCO_1MHZ;			// SMCLK = DCO = 1MHz  

	P1SEL |= TXD;
	P1DIR |= TXD;

	P1IES |= RXD;				// RXD Hi/lo edge interrupt
	P1IFG &= ~RXD;				// Clear RXD (flag) before enabling interrupt
	P1IE |= RXD;				// Enable RXD interrupt
  
	isReceiving = false;			// Set initial values
	hasReceived = false;
  
	__bis_SR_register(GIE);			// interrupts enabled\
  
	while(1)
	{
		if (hasReceived)		// If the device has recieved a value
		{
			hasReceived = false;	// Clear the flag
			TXByte = RXByte;	// Load the recieved byte into the byte to be transmitted
			Transmit();
		}
		if (~hasReceived)		// Loop again if another value has been received
    			__bis_SR_register(CPUOFF + GIE);        
			// LPM0, the ADC interrupt will wake the processor up. This is so that it does not
			//	endlessly loop when no value has been Received.
	}
}

// Function Transmits Character from TXByte 
void Transmit()
{ 
	while(isReceiving);			// Wait for RX completion
  	CCTL0 = OUT;				// TXD Idle as Mark
  	TACTL = TASSEL_2 + MC_2;		// SMCLK, continuous mode

  	BitCnt = 0xA;				// Load Bit counter, 8 bits + ST/SP
  	CCR0 = TAR;				// Initialize compare register
  
  	CCR0 += Bit_time;			// Set time till first bit
  	TXByte |= 0x100;			// Add stop bit to TXByte (which is logical 1)
  	TXByte = TXByte << 1;			// Add start bit (which is logical 0)
  
  	CCTL0 =  CCIS0 + OUTMOD0 + CCIE;	// Set signal, intial value, enable interrupts
  	while ( CCTL0 & CCIE );			// Wait for previous TX completion
}

// Port 1 interrupt service routine

//static void
//__attribute__((__interrupt__(PWM_VECTOR)))
//pwm_handler ()

static void
__attribute__((__interrupt__(PORT1_VECTOR)))
Port_1(void)
{  	
	isReceiving = true;
	
	P1IE &= ~RXD;			// Disable RXD interrupt
	P1IFG &= ~RXD;			// Clear RXD IFG (interrupt flag)
	
  	TACTL = TASSEL_2 + MC_2;	// SMCLK, continuous mode
  	CCR0 = TAR;			// Initialize compare register
  	CCR0 += Bit_time_5;		// Set time till first bit
	CCTL0 = OUTMOD1 + CCIE;		// Dissable TX and enable interrupts
	
	RXByte = 0;			// Initialize RXByte
	BitCnt = 0x9;			// Load Bit counter, 8 bits + ST
}

// Timer A0 interrupt service routine
//#pragma vector=TIMERA0_VECTOR
//__interrupt 

static void 
__attribute__((__interrupt__(TIMERA0_VECTOR)))
Timer_A (void)
{
	if(!isReceiving)
	{
		CCR0 += Bit_time;			// Add Offset to CCR0  
		if ( BitCnt == 0)			// If all bits TXed
		{
  			TACTL = TASSEL_2;		// SMCLK, timer off (for power consumption)
			CCTL0 &= ~ CCIE ;		// Disable interrupt
		}
		else
		{
			CCTL0 |=  OUTMOD2;		// Set TX bit to 0
			if (TXByte & 0x01)
				CCTL0 &= ~ OUTMOD2;	// If it should be 1, set it to 1
			TXByte = TXByte >> 1;
			BitCnt --;
		}
	}
	else
	{
		CCR0 += Bit_time;				// Add Offset to CCR0  
		if ( BitCnt == 0)
		{
  			TACTL = TASSEL_2;			// SMCLK, timer off (for power consumption)
			CCTL0 &= ~ CCIE ;			// Disable interrupt
			
			isReceiving = false;
			
			P1IFG &= ~RXD;				// clear RXD IFG (interrupt flag)
			P1IE |= RXD;				// enabled RXD interrupt
			
			if ( (RXByte & 0x201) == 0x200)		// Validate the start and stop bits are correct
			{
				RXByte = RXByte >> 1;		// Remove start bit
				RXByte &= 0xFF;			// Remove stop bit
				hasReceived = true;
			}
  			__bic_SR_register_on_exit(CPUOFF);	// Enable CPU so the main while loop continues
		}
		else
		{
			if ( (P1IN & RXD) == RXD)		// If bit is set?
				RXByte |= 0x400;		// Set the value in the RXByte 
			RXByte = RXByte >> 1;			// Shift the bits down
			BitCnt --;
		}
	}
}
