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
 *  //  RTC update Pinout   --> D12 as pullup
 *  //  SCL                 --> A04 Tied HIGH W/ 3k3 Ohm resistor
 *  //  SDA                 --> A05 Tied HIGH W/ 3k3 Ohm resistor
 * (value of I2C pull up can vary, check out the link below) 
 * https://electronics.stackexchange.com/questions/1849/is-there-a-correct-resistance-value-for-i2c-pull-up-resistors
 *   
 *   
 *   
 *   
 *   Created: Feb 6, 2019 by Dan Parkolay (with a lot of help from a lot of other people)
 *   Updated: Oct 9, 2022 by Dan Parkolay (Removed HTM1735LF, updated Display values added INT for DST input)
*/
as of 11-10-2022
Using library U8g2 at version 2.33.15 in folder: D:\Github\libraries\U8g2 
Using library SparkFun BME280 at version 2.0.10 in folder: D:\Github\libraries\SparkFun_BME280_Arduino_Library 
Using library Wire at version 1.0 in folder: Arduino15\packages\arduino\hardware\avr\1.8.6\libraries\Wire 
Using library SPI at version 1.0 in folder:Arduino15\packages\arduino\hardware\avr\1.8.6\libraries\SPI 
Using library RTCLib by NeiroN at version 1.6.2 in folder: D:\Github\libraries\RTCLib_by_NeiroN 
Using library HCWireless in folder: D:\Github\libraries\HCWireless (legacy)
"\Arduino15\\packages\\arduino\\tools\\avr-gcc\\7.3.0-atmel3.6.1-arduino7/bin/avr-size" -A 
"arduino-sketch-CCC7E1FB68E3BD453D5ACB884EDD52CA/WeatherBox.ino.elf"
Sketch uses 24048 bytes (78%) of program storage space. Maximum is 30720 bytes.
Global variables use 1334 bytes (65%) of dynamic memory, leaving 714 bytes for local variables. Maximum is 2048 bytes.

as of 11-11-2022
Using library Wire at version 1.0 in folder: \Arduino15\packages\arduino\hardware\avr\1.8.6\libraries\Wire 
Using library U8g2 at version 2.33.15 in folder: D:\Github\libraries\U8g2 
Using library SparkFun BME280 at version 2.0.10 in folder: D:\Github\libraries\SparkFun_BME280_Arduino_Library 
Using library SPI at version 1.0 in folder: \Arduino15\packages\arduino\hardware\avr\1.8.6\libraries\SPI 
Using library RTCLib by NeiroN at version 1.6.2 in folder: D:\Github\libraries\RTCLib_by_NeiroN 
Using library SolarCalculator at version 2.0.1 in folder: D:\Github\libraries\SolarCalculator 
Using library HCWireless in folder: D:\Github\libraries\HCWireless (legacy)
"\Arduino15\\packages\\arduino\\tools\\avr-gcc\\7.3.0-atmel3.6.1-arduino7/bin/avr-size" -A 
"\arduino-sketch-CCC7E1FB68E3BD453D5ACB884EDD52CA/WeatherBox.ino.elf"
Sketch uses 29988 bytes (97%) of program storage space. Maximum is 30720 bytes.
Global variables use 1402 bytes (68%) of dynamic memory, leaving 646 bytes for local variables. Maximum is 2048 bytes.

As of 030142023 (aka StarDate 76664)
Added serial.println (Version)
Updated display info and structure
Added RTC_UPDATE_PIN
Corrected call to sunrise/sunset updated utc_offset using DST pin
Using library Wire at version 1.0 in folder: \Arduino15\packages\arduino\hardware\avr\1.8.6\libraries\Wire 
Using library U8g2 at version 2.33.15 in folder: D:\Github\libraries\U8g2 
Using library SparkFun BME280 at version 2.0.10 in folder: D:\Github\libraries\SparkFun_BME280_Arduino_Library 
Using library SPI at version 1.0 in folder: \Arduino15\packages\arduino\hardware\avr\1.8.6\libraries\SPI 
Using library RTCLib by NeiroN at version 1.6.3 in folder: D:\Github\libraries\RTCLib_by_NeiroN 
Using library SolarCalculator at version 2.0.1 in folder: D:\Github\libraries\SolarCalculator 
Using library HCWireless in folder: D:\Github\libraries\HCWireless (legacy)
\Arduino15\\packages\\arduino\\tools\\avr-gcc\\7.3.0-atmel3.6.1-arduino7/bin/avr-size" -A 
\arduino\\sketches\\CCC7E1FB68E3BD453D5ACB884EDD52CA/WeatherBox.ino.elf"
Sketch uses 29864 bytes (97%) of program storage space. Maximum is 30720 bytes.
Global variables use 1406 bytes (68%) of dynamic memory, leaving 642 bytes for local variables. Maximum is 2048 bytes.