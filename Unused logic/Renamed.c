
// *************************************************************************************************
//
//	Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/ 
//	 
//	 
//	  Redistribution and use in source and binary forms, with or without 
//	  modification, are permitted provided that the following conditions 
//	  are met:
//	
//	    Redistributions of source code must retain the above copyright 
//	    notice, this list of conditions and the following disclaimer.
//	 
//	    Redistributions in binary form must reproduce the above copyright
//	    notice, this list of conditions and the following disclaimer in the 
//	    documentation and/or other materials provided with the   
//	    distribution.
//	 
//	    Neither the name of Texas Instruments Incorporated nor the names of
//	    its contributors may be used to endorse or promote products derived
//	    from this software without specific prior written permission.
//	
//	  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
//	  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
//	  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//	  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
//	  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
//	  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
//	  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//	  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//	  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
//	  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
//	  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// *************************************************************************************************
// Time functions.
// *************************************************************************************************


// *************************************************************************************************
// Include section

// system
#include "project.h"

// driver
#include "ports.h"
#include "display.h"
#include "timer.h"
#include "buzzer.h"

// logic
#include "menu.h"
#include "clock.h"
#include "user.h"
#include "bluerobin.h"
#include "date.h"
#include "buzzer.h"
#include "acceleration.h"


// *************************************************************************************************
// Prototypes section
void reset_clock(void);
void clock_tick(void);
void mx_time(u8 line);
void sx_time(u8 line);

void calc_24H_to_12H(u8 * hours, u8 * timeAM);
void conv_24H_to_12H(u8 * hours24, u8 * hours12, u8 * timeAMorPM);


// *************************************************************************************************
// Defines section


// *************************************************************************************************
// Global Variable section
struct time sTime;

// Display values for time format selection
const u8 selection_Timeformat[][4] =
{
	"24H", "12H"
};


// *************************************************************************************************
// Extern section
extern void (*fptr_lcd_function_line1)(u8 line, u8 update);
extern void (*fptr_lcd_function_line2)(u8 line, u8 update);


// *************************************************************************************************
// @fn          reset_clock
// @brief       Resets clock time to 00:00:00, 24H time format.
// @param       none
// @return      none
// *************************************************************************************************
void reset_clock(void) 
{
	// Set global system time to 0
	sTime.system_time = 0;
	
	// Set main 24H time to start value
	sTime.hour   = 0; 
	sTime.minute = 4; 
	sTime.second = 60; 
	
	// Display style of both lines is default (HH:MM)
	sTime.line1ViewStyle = DISPLAY_DEFAULT_VIEW;
	
	// Reset timeout detection
	sTime.last_activity 		  = 0;
}


// *************************************************************************************************
// @fn          clock_tick
// @brief       Add 1 second to system time and to display time
// @param       none
// @return      none
// *************************************************************************************************
void clock_tick(void) 
{
	// Use sTime.drawFlag to minimize display updates
	// sTime.drawFlag = 1: second
	// sTime.drawFlag = 2: minute, second
	// sTime.drawFlag = 3: hour, minute
	
	
	// unassigned char to store counts of when the threshold has been triggered
	u8 accelout;
	
	accelout = 0;
	
	sTime.drawFlag = 1;


	do_acceleration_measurement();
	
	
	//Activates Alarm signal if exceeds threshold (set to be 10 and less than 9?
	//When threshold exceeded ad 1 to accelout, if it becomes 10 then kill the operation and set everything to zero
	if (sAccel.data >= 10)
	{
		accelout++;
		display_symbol(LCD_ICON_ALARM, SEG_ON_BLINK_ON);
	}
	if (sAccel.data < 9)
	{
		display_symbol(LCD_ICON_ALARM, SEG_OFF_BLINK_OFF);
	}

	if (accelout == 10)
	{
	 	Timer0_Stop();
		sTime.minute = 0;
		sTime.second = 0;	
	}
	
	// minus a second
	
	// sTime.second--;
	
	
	// countdown at a rate of 2 per second or of any value wished to be accelerated for countdown
	sTime.second -= 2;
	
	
	// decrease a minute when counted 60 seconds
	if (sTime.second == 0)
	{
		sTime.drawFlag++;
		sTime.minute--;
		sTime.second = 60;
	}
	
	
	// when the minutes have been ended then stop the counting and set everything to zero
	// the heart icon works and will be replaced by the sound function when it is implied.
	if (sTime.minute == 0)
	{
		Timer0_Stop();
		sTime.minute = 0;
		sTime.second = 0;
		display_symbol(LCD_ICON_HEART, SEG_ON_BLINK_ON);
	}
}


// *************************************************************************************************
// @fn          convert_hour_to_12H_format
// @brief       Convert internal 24H time to 12H time.
// @param       u8 hour		Hour in 24H format
// @return      u8				Hour in 12H format
// *************************************************************************************************
u8 convert_hour_to_12H_format(u8 hour)
{
	// 00:00 .. 11:59 --> AM 12:00 .. 11:59
	if (hour == 0)			return (hour + 12);
	else if (hour <= 12)	return (hour);	
	// 13:00 .. 23:59 --> PM 01:00 .. 11:59
	else  					return (hour - 12);
}


// *************************************************************************************************
// @fn          is_hour_am
// @brief       Checks if internal 24H time is AM or PM
// @param       u8 hour		Hour in 24H format
// @return      u8				1 = AM, 0 = PM
// *************************************************************************************************
u8 is_hour_am(u8 hour)
{
	// 00:00 .. 11:59 --> AM 12:00 .. 11:59
	if (hour < 12)	return (1);
	// 12:00 .. 23:59 --> PM 12:00 .. 11:59
	else  			return (0);
}


// *************************************************************************************************
// @fn          display_selection_Timeformat
// @brief       Display time format 12H / 24H. 
// @param       u8 segments			Target segments where to display information
//				u32 index			0 or 1, index for value string
//				u8 digits			Not used
//				u8 blanks			Not used
// @return      none
// *************************************************************************************************
void display_selection_Timeformat1(u8 segments, u32 index, u8 digits, u8 blanks)
{
	if (index < 2) display_chars(segments, (u8 *)selection_Timeformat[index], SEG_ON_BLINK_ON);
}


// *************************************************************************************************
// @fn          mx_time
// @brief       Clock set routine.
// @param       u8 line		LINE1, LINE2
// @return      none
// *************************************************************************************************
void mx_time(u8 line)
{
	u8 select;
	s32 timeformat;
	s16 timeformat1;
	s32 hours;
	s32 minutes;
	s32 seconds;
	u8 * str;
	
	// Clear display
	clear_display_all();
		
	// Convert global time to local variables
	// Global time keeps on ticking in background until it is overwritten
	if (sys.flag.use_metric_units)
	{
		timeformat 	= TIMEFORMAT_24H;
	}
	else
	{
		timeformat 	= TIMEFORMAT_12H;
	}
	timeformat1	= timeformat;
	hours 		= sTime.hour; 
	minutes 	= sTime.minute;
	seconds 	= sTime.second;
	
	// Init value index
	select = 0;	
		
	// Loop values until all are set or user breaks	set
	while(1) 
	{
		// Idle timeout: exit without saving 
		if (sys.flag.idle_timeout)
		{
			// Roll back time format
			if (timeformat1 == TIMEFORMAT_24H) 	sys.flag.use_metric_units = 1;
			else								sys.flag.use_metric_units = 0;
			display_symbol(LCD_SYMB_AM, SEG_OFF);
			break;
		}
		
		// Button STAR (short): save, then exit 
		if (button.flag.star) 
		{
			// Stop clock timer
			Timer0_Stop();

			// Store local variables in global clock time
			sTime.hour 	 = hours;
			sTime.minute = minutes;
			sTime.second = seconds;

			// Start clock timer
			Timer0_Start();
			
			// Full display update is done when returning from function
			display_symbol(LCD_SYMB_AM, SEG_OFF);
			break;
		}

		switch (select)
		{
			case 0:		// Clear LINE1 and LINE2 and AM icon - required when coming back from set_value(seconds)
						clear_display();
						display_symbol(LCD_SYMB_AM, SEG_OFF);
						
						// Set 24H / 12H time format
						
						// Modify global time format variable immediately to update AM/PM icon correctly
						if (timeformat == TIMEFORMAT_24H) 	sys.flag.use_metric_units = 1;
						else								sys.flag.use_metric_units = 0;
						select = 1;
						break;
			
			case 1:		// Display MM:SS (LINE1) and .HH (LINE2)
						str = itoa(minutes, 2, 0);
						display_chars(LCD_SEG_L1_3_2, str, SEG_ON);
						display_symbol(LCD_SEG_L1_COL, SEG_ON);
						
						str = itoa(seconds, 2, 0);
						display_chars(LCD_SEG_L1_1_0, str, SEG_ON);
						display_symbol(LCD_SEG_L1_DP1, SEG_ON);

						str = itoa(hours, 2, 0);
						display_chars(LCD_SEG_L2_1_0, str, SEG_ON);
									
						// Set Minutes
						set_value(&minutes, 2, 0, 0, 23, SETVALUE_ROLLOVER_VALUE + SETVALUE_DISPLAY_VALUE + SETVALUE_NEXT_VALUE, LCD_SEG_L1_3_2, display_value1);
						select = 2;
						break;
			
			case 2:		// Set Seconds
						set_value(&seconds, 2, 0, 0, 59, SETVALUE_ROLLOVER_VALUE + SETVALUE_DISPLAY_VALUE + SETVALUE_NEXT_VALUE, LCD_SEG_L1_1_0, display_value1);
						select = 3;
						break;
			
			case 3:		// Set Hours
						set_value(&hours, 2, 0, 0, 59, SETVALUE_ROLLOVER_VALUE + SETVALUE_DISPLAY_VALUE + SETVALUE_NEXT_VALUE, LCD_SEG_L2_1_0, display_hours1);
						select = 0;
						break;
		}
	}
	
	// Clear button flags
	button.all_flags = 0;
}


// *************************************************************************************************
// @fn          sx_time
// @brief       Time user routine. Toggles view style between HH:MM and SS.
// @param       line		LINE1
// @return      none
// *************************************************************************************************
void sx_time(u8 line)
{
	// Toggle display view style
	if (sTime.line1ViewStyle == DISPLAY_DEFAULT_VIEW) 	sTime.line1ViewStyle = DISPLAY_ALTERNATIVE_VIEW;
	else 									 			sTime.line1ViewStyle = DISPLAY_DEFAULT_VIEW;
}


// *************************************************************************************************
// @fn          display_time
// @brief       Clock display routine. Supports 24H and 12H time format. 
// @param       u8 line			LINE1
//				u8 update		DISPLAY_LINE_UPDATE_FULL, DISPLAY_LINE_UPDATE_PARTIAL
// @return      none
// *************************************************************************************************
void display_time(u8 line, u8 update)
{
	
	// Partial update
 	if (update == DISPLAY_LINE_UPDATE_PARTIAL) 
	{
		if(sTime.drawFlag != 0) 
		{
			if (sTime.line1ViewStyle == DISPLAY_DEFAULT_VIEW)
			{
				switch(sTime.drawFlag) 
				{
					case 3: 
							{
								// Display 24H time "HH" 
								// Nothing to do here
							}
					
					case 2: display_chars(switch_seg(line, LCD_SEG_L1_1_0, LCD_SEG_L2_1_0), itoa(sTime.hour, 2, 0), SEG_ON);
				}
			}
			else
			{
				// Constant Update
				
				display_chars(switch_seg(line, LCD_SEG_L1_3_2, LCD_SEG_L2_3_2), itoa(sTime.minute, 2, 0), SEG_ON);
				display_chars(switch_seg(line, LCD_SEG_L1_1_0, LCD_SEG_L2_1_0), itoa(sTime.second, 2, 0), SEG_ON); 
			}
		}	
	}
	else if (update == DISPLAY_LINE_UPDATE_FULL)			
	{
		// Full update
		if (sTime.line1ViewStyle == DISPLAY_DEFAULT_VIEW)
		{	
	
			//Display MM
			display_chars(switch_seg(line, LCD_SEG_L1_3_2, LCD_SEG_L2_3_2), itoa(sTime.minute, 2, 0), SEG_ON);
			display_symbol(switch_seg(line, LCD_SEG_L1_COL, LCD_SEG_L2_COL0), SEG_ON);
		

			
			// Display SS
			display_chars(switch_seg(line, LCD_SEG_L1_1_0, LCD_SEG_L2_1_0), itoa(sTime.second, 2, 0), SEG_ON);
			display_symbol(switch_seg(line, LCD_SEG_L1_DP1, LCD_SEG_L2_DP), SEG_ON); 
			
		}
		else
		{
			// Display HH
			display_chars(switch_seg(line, LCD_SEG_L1_1_0, LCD_SEG_L2_1_0), itoa(sTime.hour, 2, 0), SEG_ON);
			
		}
	}
	else if (update == DISPLAY_LINE_CLEAR)
	{
		
		// Change display style to default (HH:MM)
		sTime.line1ViewStyle = DISPLAY_DEFAULT_VIEW;
		// Clean up AM/PM icon
		display_symbol(LCD_SYMB_AM, SEG_OFF);
	}
}
