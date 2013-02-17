void Accel_logic(void) 
{
	u8 threshold;
	u8 accelout;
	u8 acceladd;
	
	threshold = 500;
	accelout = 0;
	acceladd = 0;	
			
		if (sAccel.data >= threshold)
		{
			accelout = 1;
			acceladd++;
			display_symbol(LCD_ICON_ALARM, SEG_ON_BLINK_ON);
		}
	
		if (sAccel.data < threshold)
		{	
			accelout = 0;
			acceladd--;
			display_symbol(LCD_ICON_ALARM, SEG_ON_BLINK_OFF);
		}	
		
		if (accelout == 1)
			{
		sTime.second -= 1;
		}
	
		if (acceladd == 5)
		{
			sTime.second -= 4;
		}
		else{
			sTime.second--;
		}
}
