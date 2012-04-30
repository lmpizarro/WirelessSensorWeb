/* Configure ADC Temp Sensor Channel */
void ConfigureAdcTempSensor(void)
{
//  unsigned char i;
  ADC10CTL1 = INCH_10 + ADC10DIV_3;         // Temp Sensor ADC10CLK/4
  ADC10CTL0 = SREF_1 + ADC10SHT_3 + REFON + ADC10ON + ADC10IE;
  __delay_cycles(1000);                     // Wait for ADC Ref to settle

//  ADC10CTL0 |= ENC + ADC10SC;               // Sampling and conversion start
//  __bis_SR_register(CPUOFF + GIE);          // LPM0 with interrupts enabled
//  tempCalibrated = ADC10MEM;
//  for (i=0; i < 8; i++)
//    tempMeasured[i] = tempCalibrated;
//  tempAverage = tempCalibrated;
}

int  adqAdcTempSensor(void)
{
   ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start
    __bis_SR_register(CPUOFF + GIE);        // LPM0 with interrupts enabled
   return (ADC10MEM);
}

// ADC10 interrupt service routine
interrupt (ADC10_VECTOR) ADC10_ISR(void)
{
  __bic_SR_register_on_exit(CPUOFF);        // Return to active mode
}
