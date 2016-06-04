# ESP8266_TX20_wind_sensor
Technoline TX20 Wind Sensor on Wemos D1 mini (or any ESP8266)

This simple file made to testing the TX20 Wind Sensor on ESP8266 based microcontrollers. 

You can find a few documentation how to connect TX20 to Arduino, but that code is not working on ESP8266 because using the AVR library. Also there is some syncronisation different between Arduino and ESP8266, and the transistor in the Arduino's circuit make a signal inverse that we do not. So there is plenty of different.

The code is tested on Wemos D1 mini, but I am pretty sure, it will working on any ESP8266 based controller.

#Wiring:
You do not need any extra level shifting like on Arduino, just simple connect the ESP8266 to TX-20, because both working on 3.3V.

TX20 RJ11  -> ESP PIN
1	Brown	TxD  -> Any Digital pin (in code D2)
2	Red	Vcc  -> 3.3V
3	Green	DTR  -> Ground
4	Yellow	GND  -> Ground

#Customizing the code:
If you are using other pin than D2, just modify this line:
const byte DATAPIN=D2;

If you got data but have problem with them, that usually show the checksum. Also the code said: !!! ERROR !!! 
If this happened, try to change the delay in this line a little bit (step: +-5):
delayMicroseconds(1220);    

The decoding based on Fabrizio Zellini Arduino code:
http://fabrizio.zellini.org/decoding-la-crosse-tx20-anemometer-with-arduino

Also there is some important information on John's page:
https://www.john.geek.nz/2011/07/la-crosse-tx20-anemometer-communication-protocol


Hungary, jun 4, 2016

#Licence:
Free to use this code in any kind of project.
