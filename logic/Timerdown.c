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
#include "Timerdown.h"


// logic
#include "menu.h"
#include "user.h"
#include "bluerobin.h"
#include "date.h"

// *************************************************************************************************
// Prototypes section
void reset_timedown(void);
void tickrate(void);
void mx_timedown(u8 line);
void sx_timedown(u8 line);
void display_timedown(u8 line, u8 update);

void calc_24H_to_12H(u8 * hours, u8 * timeAM);
void conv_24H_to_12H(u8 * hours24, u8 * hours12, u8 * timeAMorPM);


// *************************************************************************************************
// Defines section


// *************************************************************************************************
// Global Variable section
struct timedown sTimedown;

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
void reset_timedown(void) 
{
	// Set global system time to 0
	sTimedown.system_timedown = 0;
	
	// Set main 24H time to start value
	sTimedown.minute = 30; 
	sTimedown.second = 0; 
	
	// Display style of both lines is default (HH:MM)
	sTimedown.line1ViewStyle = DISPLAY_DEFAULT_VIEW;
	
	// Reset timeout detection
	sTimedown.last_activity 		  = 0;
}


// *************************************************************************************************
// @fn          clock_tick
// @brief       Add 1 second to system time and to display time
// @param       none
// @return      none
// *************************************************************************************************
void tickrate(void) 
{
	// Use sTime.drawFlag to minimize display updates
	// sTime.drawFlag = 1: second
	// sTime.drawFlag = 2: minute, second
	// sTime.drawFlag = 3: hour, minute
	sTimedown.drawFlag = 1;

	// Increase global system time
	sTimedown.system_timedown--;

	// Add 1 second
	sTimedown.second--;
	
	// Add 1 minute
	if (sTimedown.second == 60)
	{
		sTimedown.drawFlag++;
		sTimedown.second = 0;
		sTimedown.minute--;		
		}
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
void mx_timedown(u8 line)
{
	u8 select;
	s32 timeformat;
	s16 timeformat1;
	s32 minutes;
	s32 seconds;
	u8 * str;
	
	// Clear display
	clear_display_all();
		
	minutes 	= sTimedown.minute;
	seconds 	= sTimedown.second;
	
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
			sTimedown.minute = minutes;
			sTimedown.second = seconds;

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
						set_value(&timeformat, 1, 0, 0, 1, SETVALUE_ROLLOVER_VALUE + SETVALUE_DISPLAY_SELECTION + SETVALUE_NEXT_VALUE, LCD_SEG_L1_3_1, display_selection_Timeformat1);
						
						// Modify global time format variable immediately to update AM/PM icon correctly
						if (timeformat == TIMEFORMAT_24H) 	sys.flag.use_metric_units = 1;
						else								sys.flag.use_metric_units = 0;
						select = 1;
						break;
			
			case 1:		// Display MM:SS (LINE1) 
						str = itoa(minutes, 2, 0);
						display_chars(LCD_SEG_L1_3_2, str, SEG_ON);
						display_symbol(LCD_SEG_L1_COL, SEG_ON);
						
						str = itoa(seconds, 2, 0);
						display_chars(LCD_SEG_L1_1_0, str, SEG_ON);

													
						// Set Minutes
						set_value(&minutes, 2, 0, 0, 23, SETVALUE_ROLLOVER_VALUE + SETVALUE_DISPLAY_VALUE + SETVALUE_NEXT_VALUE, LCD_SEG_L1_3_2, display_hours1);
						select = 2;
			
						// Set Seconds
						set_value(&seconds, 2, 0, 0, 59, SETVALUE_ROLLOVER_VALUE + SETVALUE_DISPLAY_VALUE + SETVALUE_NEXT_VALUE, LCD_SEG_L1_1_0, display_value1);
						select = 3;
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
void sx_timedown(u8 line)
{
	// Toggle display view style
	if (sTimedown.line1ViewStyle == DISPLAY_DEFAULT_VIEW) 	sTimedown.line1ViewStyle = DISPLAY_ALTERNATIVE_VIEW;
	else 									 			sTimedown.line1ViewStyle = DISPLAY_DEFAULT_VIEW;
}


// *************************************************************************************************
// @fn          display_time
// @brief       Clock display routine. Supports 24H and 12H time format. 
// @param       u8 line			LINE1
//				u8 update		DISPLAY_LINE_UPDATE_FULL, DISPLAY_LINE_UPDATE_PARTIAL
// @return      none
// *************************************************************************************************
void display_timedown(u8 line, u8 update)
{
	
	// Partial update
 	if (update == DISPLAY_LINE_UPDATE_PARTIAL) 
	{
		if(sTimedown.drawFlag != 0) 
		{
			if (sTimedown.line1ViewStyle == DISPLAY_DEFAULT_VIEW)
			{
				switch(sTimedown.drawFlag) 
				{
					case 3: if (sys.flag.use_metric_units)
							{
								// Display 12H time "HH" + AM/PM
							}
							
					case 2: display_chars(switch_seg(line, LCD_SEG_L1_1_0, LCD_SEG_L2_1_0), itoa(sTimedown.minute, 2, 0), SEG_ON); 
				}
			}
			else
			{
				// Seconds are always updated
				display_chars(switch_seg(line, LCD_SEG_L1_1_0, LCD_SEG_L2_1_0), itoa(sTimedown.second, 2, 0), SEG_ON);
			}
		}	
	}
	else if (update == DISPLAY_LINE_UPDATE_FULL)			
	{
		// Full update
		if (sTimedown.line1ViewStyle == DISPLAY_DEFAULT_VIEW)
		{	
			// Display 24H/12H time
			if (sys.flag.use_metric_units)
			{
					// Display minute
					display_chars(switch_seg(line, LCD_SEG_L1_1_0, LCD_SEG_L2_1_0), itoa(sTimedown.minute, 2, 0), SEG_ON); 
					display_symbol(switch_seg(line, LCD_SEG_L1_COL, LCD_SEG_L2_COL0), SEG_ON_BLINK_ON);
			}

		else
		{
			// Display seconds
			display_chars(switch_seg(line, LCD_SEG_L1_1_0, LCD_SEG_L2_1_0), itoa(sTimedown.second, 2, 0), SEG_ON);
			display_symbol(switch_seg(line, LCD_SEG_L1_DP1,LCD_SEG_L2_DP), SEG_ON);
		}
	}
	else if (update == DISPLAY_LINE_CLEAR)
	{
		display_symbol(switch_seg(line, LCD_SEG_L1_COL, LCD_SEG_L2_COL0), SEG_OFF_BLINK_OFF);
		// Change display style to default (HH:MM)
		sTimedown.line1ViewStyle = DISPLAY_DEFAULT_VIEW;
		// Clean up AM/PM icon
		display_symbol(LCD_SYMB_AM, SEG_OFF);
	}
}
