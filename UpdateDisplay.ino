/*
 
  U8G2_SSD1306_128X64_NONAME_1_4W_HW_SPI u8g2
  make -f Makefile.184.uno
  
   text     
   8732               default, all active
   8500     -232      -2.65%    no U8G2_WITH_CLIP_WINDOW_SUPPORT
   8316     -416      -4.76%    no U8G2_WITH_FONT_ROTATION
   8606     -126      -1.44%    no U8G2_WITH_UNICODE
   8692     -40     -0.45%    no U8G2_WITH_INTERSECTION
   8328     -404      -4.62%      no U8G2_WITH_INTERSECTION  no U8G2_WITH_CLIP_WINDOW_SUPPORT
   8718     -14     -4.86%    no U8G2_WITH_HVLINE_SPEED_OPTIMIZATION
   8026     -706      -8.08%    no U8G2_WITH_FONT_ROTATION   no U8G2_WITH_INTERSECTION  no U8G2_WITH_CLIP_WINDOW_SUPPORT
   
   Some flags depend on each other: `U8G2_WITH_INTERSECTION` is required for `U8G2_WITH_CLIP_WINDOW_SUPPORT`, so `U8G2_WITH_INTERSECTION` is partly active as long
   as `U8G2_WITH_CLIP_WINDOW_SUPPORT` is requested.
   
*/
/*
  U8glib Example Overview:
    Frame Buffer Examples: clearBuffer/sendBuffer. Fast, but may not work with all Arduino boards because of RAM consumption
    Page Buffer Examples: firstPage/nextPage. Less RAM usage, should work with all Arduino boards.
    U8x8 Text Only Example: No RAM usage, direct communication with display controller. No graphics, 8x8 Text only.
    
  This is a page buffer example.    
*/

void UpdateDisplay()
{
  GetLine1();
  GetLine2();
  //GetLine3();
  GetLine4();
  GetLine5();
  //GetLine6();
}

void GetLine1()
{
    u8g2.setFont(u8g2_font_ncenB12_tr);
    //u8g2.drawStr(0,13,"Air Quality Sensor");//I don't know if this will fit on display :(
    u8g2.drawStr(0,13,"AirQltySensor");
}

void GetLine2()
{
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.setCursor(0,24);
    u8g2.print(AirQualitySensorValue);
}

void GetLine3()
{
    u8g2.setCursor(0,34);
    u8g2.print("012345678901234567890"); 
//    u8g2.print(samples[1]); 
//    u8g2.setCursor(42,34);
//    u8g2.print(TempSensorAverage); 
    
}

void GetLine4()
{
    u8g2.setCursor(0,44);
    //u8g2.print("012345678901234567890"); 
    u8g2.print(BME280_Humidity); 
    //u8g2.setCursor(32,54); 
    u8g2.print("%RH"); 
    u8g2.setCursor(60,44);
    u8g2.print(BME280_Pressure);
    u8g2.print(" kPa ");
}

void GetLine5()
{
    
    //u8g2.setCursor(0,54);
    //u8g2.print("012345678901234567890"); 
    u8g2.setCursor(0,54);
    u8g2.print(BME280_Temperature);
    u8g2.print(" *C ");
    u8g2.setCursor(64,54);
    u8g2.print((BME280_Temperature * 9 / 5) + 32);
    u8g2.print(" *f ");
    //u8g2.setCursor(72,54); 
    //u8g2.setCursor(96,54); 

}

void GetLine6()
{
    u8g2.setCursor(0,64);
    u8g2.print("012345678901234567890"); 
//    u8g2.print(RHRawSensorValue);
//    //u8g2.setCursor(25,64);
//    u8g2.print("Tks ");
//    //u8g2.setCursor(43,64);
//    u8g2.print(RHSensorValue);
//   // u8g2.setCursor(64,64);
//    u8g2.print("V ");
//    //u8g2.setCursor(72,64); 
//    u8g2.print(RHValue); 
//    //u8g2.setCursor(96,64); 
//    u8g2.print("%RH"); 
}
