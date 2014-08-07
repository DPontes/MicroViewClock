#include <MicroView.h>
#include <Time.h>

#define clocksize 24

void setup() {
	uView.begin();		// begin of MicroView
	uView.clear(ALL);	// erase hardware memory inside the OLED controller
	uView.display();	// display the content in the buffer memory, by default it is the MicroView logo
	setTime(17,39,01,07,1,2014);
	delay(700);
	uView.clear(PAGE);	// erase the memory buffer, when next uView.display() is called, the OLED will be cleared.
}

void loop() {
	int i;
	static double counter=99999;
	static unsigned long mSec=millis()+1000;
	static uint8_t x0,y0,x1,y1;
	static float degresshour,degressmin,degresssec,hourx,houry,minx,miny,secx,secy;
	static boolean drawnFirst=false;

	uView.setFontType(0); 		// set font type 0, please see declaration in MicroView.cpp
	uView.setCursor(27,0);		// points cursor to x=27 y=0
	uView.print(12);			
	uView.setCursor(30,uView.getLCDHeight()-uView.getFontHeight());
	uView.print(6);
	uView.setCursor(0,uView.getLCDHeight() /2-(uView.getFontHeight()/2));
	uView.print(9);
	uView.setCursor(uView.getLCDWidth()-uView.getFontWidth(),uView.getLCDHeight()/2-(uView.getFontHeight()/2));
	uView.print(3);
	uView.display();			// display the memory buffer drawn

	while ((second() % 11 )!=0) {
		if (mSec!=(unsigned long)second()) {
			if (drawnFirst) {
				uView.line(32,24,32+hourx,24+houry,WHITE,XOR);
				uView.line(32,24,32+minx,24+miny,WHITE,XOR);
				uView.line(32,24,32+secx,24+secy,WHITE,XOR);
			} 
			
			degresshour = (((hour() * 360) / 12) + 270) * (PI / 180);
			degressmin = (((minute() * 360) / 60) + 270) * (PI / 180);
			degresssec = (((second() * 360) / 60) + 270) * (PI / 180);
			
			hourx = cos(degresshour) * (clocksize / 2.5);
			houry = sin(degresshour) * (clocksize / 2.5);

			minx = cos(degressmin) * (clocksize / 1.4);
			miny = sin(degressmin) * (clocksize / 1.4);

			secx = cos(degresssec) * (clocksize / 1.1);
			secy = sin(degresssec) * (clocksize / 1.1);
			

			uView.line(32,24,32+hourx,24+houry,WHITE,XOR);
			uView.line(32,24,32+minx,24+miny,WHITE,XOR);
			uView.line(32,24,32+secx,24+secy,WHITE,XOR);
			drawnFirst=true;
			uView.display();
			
			mSec=second();
		}
	}
}
