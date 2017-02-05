#include "s3c2440.h"

#define rGPECON 	(*(volatile unsigned *)0x56000040)
#define rGPEDAT 	(*(volatile unsigned *)0x56000044)
#define rGPEUP 	  (*(volatile unsigned *)0x56000048)

int main()
{
	int i; 
	int nOUT;
	
	rGPECON = 0x55;
	rGPEUP = 0xff;
  
  nOUT = 0x0f;
	
	while(1)
	{
		rGPEDAT = nOUT&0x07;
		for(i = 0; i <= 100000; i++);
		
		rGPEDAT = nOUT&0x03;
		for(i = 0; i <= 100000; i++);
		
		rGPEDAT = nOUT&0x01;
		for(i = 0; i <= 100000; i++);
		
		rGPEDAT = nOUT&0x00;
		for(i = 0; i <= 100000; i++);
		
		rGPEDAT = 0x0f;
  }
	
	return 0;
}
