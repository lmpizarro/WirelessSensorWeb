
const unsigned int Bitime  =  104; //9600 Baud, SMCLK=1MHz (1MHz/9600)=104
unsigned char BitCnt;              // Bit count, used when transmitting byte


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

// Timer A0 interrupt service routine
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
