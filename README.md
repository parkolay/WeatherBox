# WeatherBox

/*  This sketch sets up a small OLED display and pulls analog signals from two sensors 
 * (HTM1735LF (RH && Temp) && MQ135(air quality --> SnO2 detects CO2 && VOC))
 * 
 *  Requirements:
 *
 *  * Nano or other Arduino board
 *  * Arduino 1.8.8+ IDE
 *  * Library: U8g2lib.h --> u8g2 by oliver was used
 *
 * 
 * 
 *  // Pinout
 *  //  MQ135 analog Output --> A00
 *  //  RH Analog Output    --> A01
 *  //  Temp Analog Output  --> A02 Tied HIGH W/ 10k Ohm resistor 
 *  //  SCL                 --> A04
 *  //  SDA                 --> A05
