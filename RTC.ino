void SetupRTC()
{
  //initialize RTC
  rtc.begin();
      //rtc.adjust(DateTime(__DATE__, __TIME__));   //--> this is to force the time is it is set to something already
    if (! rtc.isrunning()) 
    {
      Serial.println("RTC is NOT running!");
      // following line sets the RTC to the date & time this sketch was compiled
      rtc.adjust(DateTime(__DATE__, __TIME__));
      
    }

  Serial.println("RTC has begun");
}

void UpdateRTC()
{
    DateTime now = rtc.now();
    char buf[100];          //buffer for the RTC TimeDate Stamp
    strncpy(buf,"DD.MM.YYYY  hh:mm:ss\0",100);
    Serial.println(now.format(buf));
    delay(1000);
}
void UpdateTime()
{
  DateTime now = rtc.now();
//  strncpy(TimeBuffer,"DD.MM.YY  hh:mm:ss\0",100); //this formats the TimeBuffer array
//  TimeReadout = (now.format(TimeBuffer));
//  Serial.println(strncpy(TimeReadout, TimeBuffer, 20);
  //Serial.println(now.format(TimeBuffer));
      
    seconds = now.second();
    minutes = now.minute();
    hours   = now.hour();
    days    = now.day();
    months  = now.month();
    years   = (now.year()-2000);  //remove the first 2 digits

    //     char buf[100];          //buffer for the RTC TimeDate Stamp
    // strncpy(buf,"DD.MM.YYYY  hh:mm:ss\0",100);
    // Serial.println(now.format(buf));
    if (DSTSwitch_mode == 0)
    {
      hours += 1;
      Serial.println(hours);
    }
    
}  // end void UpdateTime()