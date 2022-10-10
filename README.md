/*  This sketch sets up a small OLED display and pulls analog signals from two sensors 
 *  MQ135(air quality --> SnO2 detects CO2 && VOC))
 *  A BME280 (I2C--> 0x76) was added to the project starting with the 04-07-2019 pre-release.
 *  An RTC (DS3231) and Touch sensor (with INT0) has also been added to this project. 
 * 
 *  Requirements:
 *
 *  * Nano or other Arduino board
 *  * Arduino 1.8.8+ IDE
 *  * Library: U8g2lib.h --> u8g2 by oliver was used
 *              RTCLib_by_NeiroN
 *              SparkFun_BME280_Arduino_Library
 *
 * 
 * 
 *  // Pinout
 *  //  MQ135 analog Output --> A00
 *  //  Interrupt           --> D02 with INT0
 *  //  SCL                 --> A04 Tied HIGH W/ 3k3 Ohm resistor
 *  //  SDA                 --> A05 Tied HIGH W/ 3k3 Ohm resistor
 * (value of I2C pull up can vary, check out the link below) 
 * https://electronics.stackexchange.com/questions/1849/is-there-a-correct-resistance-value-for-i2c-pull-up-resistors
 *   
 *   
 *   
 *   
 *   Created: Feb 6, 2019 by Dan Parkolay (with a lot of help from a lot of other people)
*/
