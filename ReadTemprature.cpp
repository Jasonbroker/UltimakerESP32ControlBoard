#include "ReadTemprature.h"
#include <OneWire.h>

OneWire  ds(19);  // on pin 10 (a 4.7K resistor is necessary)

int readTemprature(float temps[])
 {
	byte i;
	byte present = 0;
	byte type_s;
	byte data[12];
	byte addr[8];
	float celsius;
	int count = 0;
  	while (ds.search(addr))
  	{
    	for( i = 0; i < 8; i++) {
    		Serial.write(' ');
    		Serial.print(addr[i], HEX);
  		}
    	delay(250);

		if (OneWire::crc8(addr, 7) != addr[7]) {
      		Serial.println("CRC is not valid!");
      		return count;
  		}

		switch (addr[0]) {
    	case 0x10:
     	Serial.println("  Chip = DS18S20");  // or old DS1820
      		type_s = 1;
      		break;
    	case 0x28:
			Serial.println("  Chip = DS18B20");
			type_s = 0;
      		break;
    	case 0x22:
			Serial.println("  Chip = DS1822");
			type_s = 0;
			break;
		default:
			Serial.println("Device is not a DS18x20 family device.");
			return 0;
  		}   

		ds.reset();
  		ds.select(addr);
  		ds.write(0x44, 1);        // start conversion, with parasite power on at the end
  
  		delay(1000);     // maybe 750ms is enough, maybe not
  // we might do a ds.depower() here, but the reset will take care of it.
  
		present = ds.reset();
		ds.select(addr);    
		ds.write(0xBE);         // Read Scratchpad

		for ( i = 0; i < 9; i++) {           // we need 9 bytes
			data[i] = ds.read();
		//    Serial.print(data[i], HEX);
		//    Serial.print(" ");
		}

		int16_t raw = (data[1] << 8) | data[0];
		if (type_s) {
			raw = raw << 3; // 9 bit resolution default
			if (data[7] == 0x10) {
			// "count remain" gives full 12 bit resolution
			raw = (raw & 0xFFF0) + 12 - data[6];
			}
		} else {
			byte cfg = (data[4] & 0x60);
			// at lower res, the low bits are undefined, so let's zero them
			if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
			else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
			else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
			//// default is 12 bit resolution, 750 ms conversion time
		}
		celsius = (float)raw / 16.0;
		Serial.print("sensor");
		Serial.print(count);
		Serial.print(": ");
		Serial.print(celsius);
		Serial.println("°C");

		temps[count] = celsius;
		count++;

		// 测温频率不需要这么高
  		delay(1000);
  	}

  	Serial.println("No more addresses.");
  	ds.reset_search();
	
  	return count;
}
