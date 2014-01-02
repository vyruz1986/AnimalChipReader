// Do not remove the include below
#include "AnimalChipReader.h"

#include "LiquidCrystal.h"

const int iBuzzerPin = 8;
const int iStatusLEDRedPin = 9;
const int iStatusLEDGreenPin = 10;
const int iStatusLEDBluePin = 11;
const int iControlButton = 12;
const int iDummyReadButton = 13;
const String strDummyChipNumber = "1234567890";
String strPreviousChipNumber;

LiquidCrystal lcd(7,6,5,4,3,2);

void setup()
{
	pinMode(iBuzzerPin, OUTPUT);
	pinMode(iStatusLEDRedPin, OUTPUT);
	pinMode(iStatusLEDGreenPin, OUTPUT);
	pinMode(iStatusLEDBluePin, OUTPUT);
	pinMode(iDummyReadButton, INPUT);
	pinMode(iControlButton, INPUT);

	lcd.begin(16,2);
	lcd.clear();

	Serial.begin(9600);
}

void loop()
{
	int iButtonDelay = 0;
	while (digitalRead(iControlButton) == LOW)
	{
		iButtonDelay++;
		delay(100);				//Wait 100 msec during each loop
		if(iButtonDelay > 20)	//If button delay is greater than 20 --> 2 seconds
		{
			//Button was pressed for 2 secs
			fUpdateLCD(0,"Previous chip number that was stored:");
			if (strPreviousChipNumber.length() > 1)
			{
				fUpdateLCD(1,strPreviousChipNumber);
			}
				else
				{
					fUpdateLCD(1,"No chip stored");
				}
			delay(5000);
		}
	}
	iButtonDelay = 0;
	if(fChipAvailable())
	{
		String strChipNumber = String(fGetchipNumber());
		strPreviousChipNumber = strChipNumber;
		//char* charChipNumber = iChipNumber;
		//We have the chip number
		fUpdateLCD(0,"Read successful!");
		fUpdateLCD(1,strChipNumber);
		fSetRGBLedColor('G');
		tone(iBuzzerPin, 1000, 100);
		delay(150);
		tone(iBuzzerPin, 1000, 100);
		delay(150);
		tone(iBuzzerPin, 1000, 100);
		delay(5000);
	}
	else
	{
		fUpdateLCD(0,"Ready to read!");
		fUpdateLCD(1,"No chip found");
		fSetRGBLedColor('R');
	}
}

bool fChipAvailable()
{
	//Dummy code, we only check a button so far
	if (digitalRead(iDummyReadButton) == LOW)
	{
		return true;
	}
	else
	{
		return false;
	}
}

String fGetchipNumber()
{
	//Dummy code, return fixed chip number for now
	String strChipNumber = strDummyChipNumber;

	return strChipNumber;
}

bool fSetRGBLedColor(char charColor)
{
	switch(charColor)
	{
		case 'R':
			digitalWrite(iStatusLEDRedPin, HIGH);
			digitalWrite(iStatusLEDGreenPin, LOW);
			digitalWrite(iStatusLEDBluePin, LOW);
			break;

		case 'G':
			digitalWrite(iStatusLEDRedPin, LOW);
			digitalWrite(iStatusLEDGreenPin, HIGH);
			digitalWrite(iStatusLEDBluePin, LOW);
			break;
	}
	return true;
}

void fUpdateLCD(int iLine, String strMessage)
{
	//Check how long strMessage is:
	int iMessageLength = strMessage.length();
	if(iMessageLength > 16)
	{
		//Message is too long, clip it
		//strMessage = strMessage.substring(0,15);

		//TODO: We should make the line scroll here...
		int iExtraChars = iMessageLength - 15;
		for (int i=0; i < iExtraChars; i++)
		{
			Serial.println(strMessage.substring(i,i+16));
			String strMessageSubString = strMessage.substring(i,i+16);
			lcd.setCursor(0,iLine);
			lcd.print(strMessageSubString);
			delay(250);
		}
		return;
	}
	else if(iMessageLength < 16)
	{
		//Message is too short, we need to pad it
		//First find missing characters
		int iMissingChars = 16 - iMessageLength;
		for (int i = 0; i < iMissingChars; i++)
		{
			strMessage = String(strMessage + " ");
		}
	}
	lcd.setCursor(0,iLine);
	lcd.print(strMessage);
}
