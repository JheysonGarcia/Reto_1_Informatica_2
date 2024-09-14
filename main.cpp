#include <iostream>

using namespace std;

int analogPin = 0;
int val = 0;
double Entrada = 0,00;
double Pos_Memory = &Entrada;

void setup(){
    Serial.begin(9600);

}

void loop(){

    lcd.SetCursor(2,2);
    *Pos_Memory = analogRead(analogPin);
    Serial.printIn(*Pos_Memory);
    
}   