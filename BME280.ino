float BME280_Humidity;
float BME280_Pressure;
float BME280_Temperature;
float BME280_Altitude;
float BME280_DewPoint;

void UpdateBME280 ()
{
   BME280_Humidity = bme280.readFloatHumidity();
   BME280_Pressure = (bme280.readFloatPressure()/1000);
   BME280_Temperature = bme280.readTempC();
   BME280_DewPoint = bme280.dewPointF();
}

void UpdateSerialBME280 ()
{
    BME280_Humidity = bme280.readFloatHumidity();
    Serial.print("Humidity = ");
    Serial.print(BME280_Humidity);
    Serial.println(" %");

    BME280_Pressure = (bme280.readFloatPressure()/1000);
    Serial.print("Pressure = ");
    Serial.print(BME280_Pressure);
    Serial.println(" kPa");

    BME280_Temperature = bme280.readTempC();
    Serial.print("Temperature = ");
    Serial.print(BME280_Temperature);
    Serial.println(" *C");
    Serial.print("Temperature = ");
    Serial.print((BME280_Temperature * 9 / 5) + 32);
    Serial.println(" *f");
    
    
    BME280_DewPoint = bme280.dewPointF();
    Serial.print(" Dewpoint: ");
    Serial.print(bme280.dewPointC(), 2);
    Serial.println(" *C");
    Serial.print(" Dewpoint: ");
    Serial.print(BME280_DewPoint, 2);
    Serial.println(" *f");

    BME280_Altitude = bme280.readFloatAltitudeMeters();
    Serial.print("Approx. Altitude = ");
    Serial.print(BME280_Altitude);
    Serial.println(" m");
//
  Serial.println();
}

void DebugBMEData()
{
  Serial.print("Humidity: ");
  Serial.print(bme280.readFloatHumidity(), 0);

  Serial.print(" Pressure: ");
  Serial.print(bme280.readFloatPressure(), 0);
  
  Serial.print(" Alt: ");
  //Serial.print(bme280.readFloatAltitudeMeters(), 1);
  Serial.print(bme280.readFloatAltitudeFeet(), 1);
  
  Serial.print(" Temp: ");
  //Serial.print(bme280.readTempC(), 2);
  Serial.print(bme280.readTempF(), 2);

  Serial.print(" Dewpoint: ");
  //Serial.print(bme280.dewPointC(), 2);
  Serial.print(bme280.dewPointF(), 2);

  Serial.println();

}
