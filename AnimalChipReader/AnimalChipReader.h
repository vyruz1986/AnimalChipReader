// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef AnimalChipReader_H_
#define AnimalChipReader_H_
#include "Arduino.h"
//add your includes for the project AnimalChipReader here


//end of add your includes here
#ifdef __cplusplus
extern "C" {
#endif
void loop();
void setup();
#ifdef __cplusplus
} // extern "C"
#endif

//add your function definitions for the project AnimalChipReader here
bool fChipAvailable();
String fGetchipNumber();
bool fSetRGBLedColor(char charColor);
void fUpdateLCD(int iLine, String strMessage);

//Do not add code below this line
#endif /* AnimalChipReader_H_ */
