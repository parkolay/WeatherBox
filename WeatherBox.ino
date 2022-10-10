/*  This sketch sets up a small OLED display and pulls analog signals from two sensors 
 * (BME280 (RH && Temp && Press) && MQ135(air quality --> SnO2 detects CO2 && VOC))
 * an RTC (DS3231) and Touch sensor (with INT0) has also been added to this project. 
 * 
 *  Requirements:
 *
 *  * Nano or other Arduino board
 *  * Arduino 1.8.8+ IDE
 *  * Library:  U8g2lib.h --> u8g2 by oliver was used
 *              RTCLib_by_NeiroN
 *              SparkFun_BME280_Arduino_Library
 *
 * 
 * 
 *  // Pinout
 *  //  Interrupt D02
 *  //  MQ135 analog Output --> A00
 *  //  Interrupt           --> D02 with INT0
 *  //  SCL                 --> A04 Tied HIGH W/ 3k3 Ohm resistor
 *  //  SDA                 --> A05 Tied HIGH W/ 3k3 Ohm resistor
 *   
 *   
 *   
 *   
 *   Created: Feb 6, 2019 by Dan Parkolay (with a lot of help from a lot of other people)
 *   Updated: Oct 9, 2022 by Dan Parkolay (Removed HTM1735LF, updated Display values added INT for DST input)
*/


#include <Arduino.h>
#include <U8g2lib.h>
#include "SparkFunBME280.h"
#include "RTClib.h"

#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

#define switched                            true // value if the button switch has been pressed
#define triggered                           true // controls interrupt handler
#define interrupt_trigger_type            RISING // interrupt triggered on a RISING input
#define debounce                              10 // time to wait in milli secs

//Initialize BME280
BME280 bme280;

//Initialize SSD1306 Display
U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

//Initialize RTC
DS3231 rtc;

// constants won't change. They're used here to set pin numbers:
const int DSTSwitchPin = 2;     // the number of the pushbutton pin
int DSTSwitch_mode = 1;



volatile  bool interrupt_process_status = 
{
  !triggered                                     // start with no switch press pending, ie false (!triggered)
};
bool initialisation_complete =            false; // inhibit any interrupts until initialisation is complete


int seconds = 0;  // varible to store the seconds from clock
int minutes = 0;  // varible to store the minutes from clock
int hours   = 0;  // varible to store the hours from clock
int days    = 0;  // varible to store the seconds from clock
int months  = 0;  // varible to store the minutes from clock
int years   = 0;  // varible to store the hours from clock

void setup(void) 
{
  Wire.begin();
  Serial.begin(57600);
  Serial.println("initializing...");

  SetupRTC();
  
  u8g2.begin();
    // connect AREF to 3.3V and use that as VCC, less noisy!  
    //thank you for the tip Lady Ada
  analogReference(EXTERNAL);  

  bme280.setI2CAddress(0x76); //Connect to a second sensor
  if (bme280.beginI2C() == false) 
    {
      Serial.println("Sensor connect failed");
    }

  attachInterrupt(digitalPinToInterrupt(DSTSwitchPin),
                  button_interrupt_handler,
                  interrupt_trigger_type);
  initialisation_complete = true; // open interrupt processing for business

}

void loop(void) 
{
  // test buton switch and process if pressed
  if (read_button() == switched) 
  {
    // button on/off cycle now complete, so flip LED between HIGH and LOW
    // Check DSTSwitchPin to see if it's pressed.
    if (DSTSwitch_mode == 1) 
    {
      // Button was up before, but is pressed now. Set the button to pressed
      // and report that to the serial monitor.
      DSTSwitch_mode = 0;  // Button is pressed.
        Serial.println("Button has been pressed.");
    }
 
    else if (DSTSwitch_mode == 0) 
    {
      // Button was down before, but is released now. Set the button to
      // released and report that to the serial monitor.
      DSTSwitch_mode = 1;  // Button is released.
      Serial.println("Button has been released");
    }
  } 
  else 
  {

  UpdateMQ135();    //get Air Quality Data
  UpdateBME280();   //get BME data
  DebugBMEData();   //Get BME Data (send out serial data with readings)
  UpdateTime();      //GEt time date data

  delay(100);       
  u8g2.firstPage();
  do 
  {

    UpdateDisplay();
  } 
  while ( u8g2.nextPage() );
  //delay(1000);
  }
}
