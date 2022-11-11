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
 *
 *  //  MQ135 analog Output --> A00
 *  //  Interrupt           --> D02 with INT0
 *  //  Data Tx             --> TX_PIN 7
 *  //  Data Rx             --> RX_PIN 8
 *  //  SCL                 --> A04 Tied HIGH W/ 3k3 Ohm resistor
 *  //  SDA                 --> A05 Tied HIGH W/ 3k3 Ohm resistor
 *   
 *   
 *   
 *   
 *   Created: Feb 6, 2019 by Dan Parkolay (with a lot of help from a lot of other people)
 *   Updated: Oct 9, 2022 by Dan Parkolay (Removed HTM1735LF, updated Display values added INT for DST input)
*/


#include "Arduino.h"
#include "Wire.h"
#include "U8g2lib.h"
#include "SparkFunBME280.h"
#include "RTClib.h"
#include "SolarCalculator.h"
#include "HCWireless.h"

#define switched                            true // value if the button switch has been pressed
#define triggered                           true // controls interrupt handler
#define interrupt_trigger_type            RISING // interrupt triggered on a RISING input
#define debounce                              10 // time to wait in milli secs

// Digital pin used to connect to the Tx modules data input pin
#define TX_PIN 8


//Initialize BME280
BME280 bme280;

//Initialize SSD1306 Display
U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

//Initialize RTC
DS3231 rtc;

//initialize wireless
HCWireless HCWireless;

// Create a structure to send
typedef struct 
{
  float Tx_Humidity;
  float Tx_Pressure;
  float Tx_Temperature;
  float Tx_Altitude;
  float Tx_DewPoint; 
} Tx_teststruct;

Tx_teststruct Txdata;

// constants won't change. They're used here to set pin numbers:
const int DSTSwitchPin = 2;     // the number of the pushbutton pin
int DSTSwitch_mode = 1;

int DelayPeriod = 1000;           //setup for using millis() instead of delay()
unsigned long Current_Time = 0; //the "other part" of millis() (roll over around 50 days which might not work in this application)

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

// Location
double transit, sunrise, sunset;
double latitude = 39.7565;
double longitude = -77.966;
double HoursOLight = 0;
int utc_offset = -5;

int SunRiseHour = 0;
int SunRiseMinute = 0;
int SunSetHour = 0;
int SunSetMinute = 0;

bool DebugOn = false; //set to true for debug serial messages

void setup(void) 
{
  Wire.begin();
  Serial.begin(57600);
  Serial.println("initializing Weather Box 10/14/22...");

  SetupRTC();
   Serial.println("initializing RTC DS3231...");
  
  Setup_TxWireless();
   Serial.println("initializing Wireless TX...");

  u8g2.begin();
   Serial.println("initializing SSD1306...");
    // connect AREF to 3.3V and use that as VCC, less noisy!  
    //thank you for the tip Lady Ada
  analogReference(EXTERNAL);  

SetupBME280();


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
        Serial.println("Button has been Set.");
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
  // DebugBMEData();   //Get BME Data (send out serial data with readings)
  UpdateTime();     //GEt time date data
      if(millis() >= Current_Time + DelayPeriod)
    {
      //put "delay" items in here
        TxWireless();
        Current_Time += DelayPeriod;
    }

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
