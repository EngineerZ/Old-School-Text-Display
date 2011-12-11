#include <Wire.h>

#define DISPADDR 0x27
#define DISPSIZE 16

void setup() {
  Wire.begin(); /* join i2c bus */
  led_string(DISPADDR,DISPSIZE, "TESTING 123ABC..");
}

void loop() { 
 delay(500);
 }

void led_string(byte daddr, int dsize, String dstring) {
  
  int length;  /* Length of string to display */
  int c; /* Gen purpose counter */
  
  /* Check to see if the string is longer than the display*/
  
  length = dstring.length();  
  if (length > dsize) length = dsize;
  
  /* Display the charcters from left to right - rightmost character is addr 0 */
  for (c=0;c<=dsize-1;c++) led_char(daddr, (dsize-1)-c, dstring.charAt(c));
}
  
void led_char(byte daddr, byte dpos, byte dchar) 

/* Send a character to a DL1414 alphanumeric LED display via a PCF8575
   i2c I/O expander chip*/
{
  /* First, set the data and address lines of the display */
  Wire.beginTransmission(daddr); /* 7-bit address of the PCF8575 */
  
  Wire.write(dchar);              /* 1st word (P0) is ASCII value of character displayed */
  Wire.write(dpos);               /* 4 LS bits of 2nd word (P1) is character address (R to L) */
  
  /* Next send the same data strobing the R/W bit (P15) to write the data to the display */
  Wire.write(dchar);       
  Wire.write(dpos | 0x10); 

  Wire.write(dchar);       
  Wire.write(dpos);           
  
  Wire.endTransmission();    // stop transmitting
}


