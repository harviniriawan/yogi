//**************
//Communication
//**************

//send data to ESP8266
String sendData(String command, const int timeout, boolean debug)
{
  String response = "";
  esp8266.print(command);
  long int time = millis();
  while ( (time + timeout) > millis())
  {
    while (esp8266.available()) //while the ESP8266 has data available at its output
    {
      char c = esp8266.read(); //read and store received characters
      response += c;
    }
  }
  if (debug) //if in debug mode, print answer
  {
    Serial.print(response);
  }
  return response;
}
