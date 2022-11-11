// Digital pin used to connect to the Tx modules data input pin
// The instructions I read said that the Antenna should be ~13cm
// but 1/4 wave I calculated for 315MHz is ~23.8cm (23.793052222222222)
// using ~13cm worked poorly, using ~23.8cm worked well.

void Setup_TxWireless()
{
    // Initialise the Tx part of the library
  HCWireless.txInit(TX_PIN);

}

void TxWireless()
{
  // Put some test data into the structure
  Txdata.Tx_Humidity    = BME280_Humidity;
  Txdata.Tx_Pressure    = BME280_Pressure;
  Txdata.Tx_Temperature = ((BME280_Temperature * 9 / 5) + 32);
  Txdata.Tx_Altitude    = BME280_Altitude;
  Txdata.Tx_DewPoint    = BME280_DewPoint;
  // Send the contents of the structure once a second.
  HCWireless.send(Txdata);
      // Print out the contents of the structure
    Serial.print(Txdata.Tx_Humidity);
    Serial.println(" %RH");
    Serial.print(Txdata.Tx_Pressure);
    Serial.println(" kPA");
    Serial.print(Txdata.Tx_Temperature);
    Serial.println(" *f");
    Serial.print(Txdata.Tx_Altitude);
    Serial.println(" ft");
    Serial.print(Txdata.Tx_DewPoint);
    Serial.println(" *f Dew Point");
    Serial.println();
   //delay(1000);
}

