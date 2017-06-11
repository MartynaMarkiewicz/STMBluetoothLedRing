# STMBluetoothLedRing

### Overview:
BluetoothLedRing is a project which enables to control two rings (LED RING RGB WS2812b 5050) with the use of an application (Android). The project is compatible with STM32F4xx Discovery which receives the signal from the application via Bluetooth. 

### Description:
We can remotedly control the LED RING WS2812B thanks to the application and via Bluetooth connection. The primary functions are: setting the values of RGB colours, setting the  brightness on all the diodes and turning off the colours and the sequences. In this project there were created six sequences which enabled the user to obtain the luminous effect.
The control output from STM board is connected to the first ring (DI) through the 200Ω resistor.
The output form the first ring (Do) is directly connected to the input of the second ring(DI).
The power supply (+5V, GND) of the first and the second ring is directly connected to the +5V external power supply.
The power supply (+5V, GND) coming out of the STM board is connected to the +5V external power supply.

Projects components:<br />
-STM32F4xxx DISCOVERY <br />
-Bluetooth module HC-06 <br />
-2x LED RING RGB WS2812B 5050 x 8 diode - 32mm <br />

### Tools: 
CooCox CoIDE 1.7.8 - language C  
Android Studio 2.3 - language JAVA

### How to run:
#### Connections:<br />
Bluetooth module HC-06:<br />
RxD-->PC10<br />
TxD-->PC11<br />
GND-->GND<br />
VCC-->5V<br /><br />
LED RING RGB WS2812B:<br />
DI-->PC9<br />

Turn on the Bluetooth on a mobile phone and pair devices (mobile phone with the HC-06 module)<br />
![alt tag](http://i.imgur.com/a/r3Dcu.png)
  1 – ring selection<br />
  2 – colour brightness control<br />
  3 – red colour settings<br />
  4 – green colour settings<br />
  5 – blue colour settings<br />
  6 – sequence selection<br />
  7 – colour selection<br />
  8 – turn off  colour/sequence

### How to compile:
An application project:<br />
    -Clone and compile project (e.g. Android Studio)<br />
    -Generate .apk file<br />
    -Install an application on a mobile phone<br /><br />
An STM project:<br />
    -Clone, compile project and flash to STM (e.g. CooCox)
 	
### Future improvements:
Improvements:<br />
    -controlling the speed  of sequences<br />
    -controlling the brightness  of sequences<br />
    -adding new sequences<br />
    
There is a one bug.<br />
While switching between the two rings, when the sequence is on, a glimpse can be seen.


### Attributions:
https://github.com/C3MA/stm-ledstrip - ws2812.h, ws2812.c<br />
https://github.com/adafruit/Adafruit_NeoPixel - getBrightness(void), setBrightness(uint8_t)<br />
http://www.instructables.com/id/Android-Bluetooth-Control-LED-Part-2/#step5 - DeviceList.java, class ConnectBT

### License:
Distributed under MIT license

### Credits:
Piotr Goździewski,<br />
Martyna Markiewicz

The project was conducted during the Microprocessor Lab course held by the Institute of Control and Information Engineering, Poznan University of Technology.<br />
Supervisor: Tomasz Mańkowski
