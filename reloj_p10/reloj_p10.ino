#include "DMD32.h"        //
#include "fonts/Arial_black_16.h"

//Fire up the DMD library as dmd
DMD dmd(1,1);

   //Timer setup
  //create a hardware timer  of ESP32
  hw_timer_t * timer = NULL;

/*--------------------------------------------------------------------------------------
  Interrupt handler for Timer1 (TimerOne) driven DMD refresh scanning, this gets
  called at the period set in Timer1.initialize();
--------------------------------------------------------------------------------------*/
void IRAM_ATTR triggerScan()
{
  dmd.scanDisplayBySPI();
}

/*--------------------------------------------------------------------------------------
  Show clock numerals on the screen from a 4 digit time value, and select whether the
  flashing colon is on or off
--------------------------------------------------------------------------------------*/
void ShowClockNumbers( unsigned int uiTime, byte bColonOn )
{
   dmd.clearScreen(true);
   dmd.drawChar(  1,  1,'0'+((uiTime%10000)/1000), GRAPHICS_NORMAL );   // thousands
   dmd.drawChar(  8,  1, '0'+((uiTime%1000) /100),  GRAPHICS_NORMAL );   // hundreds
   dmd.drawChar( 17,  1, '0'+((uiTime%100)  /10),   GRAPHICS_NORMAL );   // tens
   dmd.drawChar( 25,  1, '0'+ (uiTime%10),          GRAPHICS_NORMAL );   // units
   /*if( bColonOn )
      dmd.drawChar( 15,  1, ':', GRAPHICS_OR     );   // clock colon overlay on
   else
      dmd.drawChar( 15,  1, ':', GRAPHICS_NOR    );   // clock colon overlay off
*/}

/*--------------------------------------------------------------------------------------
  setup
  Called by the Arduino architecture before the main loop begins
--------------------------------------------------------------------------------------*/
void setup(void)
{
   
    //return the clock speed of the CPU
  uint8_t cpuClock = ESP.getCpuFreqMHz();
  
  // Use 1st timer of 4 
  // devide cpu clock speed on its speed value by MHz to get 1us for each signal  of the timer
  timer = timerBegin(0, cpuClock, true);
  // Attach triggerScan function to our timer 
  timerAttachInterrupt(timer, &triggerScan, true);
  // Set alarm to call triggerScan function  
  // Repeat the alarm (third parameter) 
  timerAlarmWrite(timer, 300, true);

  // Start an alarm 
  timerAlarmEnable(timer);

   //clear/init the DMD pixels held in RAM
   dmd.clearScreen( true );   //true is normal (all pixels off), false is negative (all pixels on)
   dmd.selectFont(Arial_Black_16);

}

/*--------------------------------------------------------------------------------------
  loop
  Arduino architecture main loop
--------------------------------------------------------------------------------------*/
void loop(void)
{
   unsigned int ui;
   
   // 10 x 14 font clock, including demo of OR and NOR modes for pixels so that the flashing colon can be overlayed
   ui = 1234;
   ShowClockNumbers( ui, true );
   delay( 1000 );
   ShowClockNumbers( ui, false );
   delay( 1000 );
   ShowClockNumbers( ui, true );
   delay( 1000 );
   ShowClockNumbers( ui, false );
   delay( 1000 );

   ui = 2345;
   ShowClockNumbers( ui, true );
   delay( 1000 );
   ShowClockNumbers( ui, false );
   delay( 1000 );
   ShowClockNumbers( ui, true );
   delay( 1000 );
   ShowClockNumbers( ui, false );
   delay( 1000 );
}
