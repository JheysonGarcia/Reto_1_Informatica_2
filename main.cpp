#include <Wire.h>
#include <Adafruit_LiquidCrystal.h>

const int PinAnalogico = 0;
int ValorActual = 0;
int ValorMaximo = 0;
int ValorMinimo = 1023; 
unsigned long TiempoReal = 0; 
unsigned long TiempoAnterior = 0; 
float LapsoPicos = 0;
int Pico = 0;
float Amplitud = 0; 
float LongitudOnda = 0.0; 
const float VelocidadOnda = 343.0; 
float Datos[20] = {0}; 
char TipoDeOnda = "No detectada";

Adafruit_LiquidCrystal lcd(0);

void setup() {
    Serial.begin(9600);
    lcd.begin(2, 16);
    lcd.print("Frecuencia (Hz)");
    lcd.setBacklight(1);
}

void loop() {
    ValorActual = analogRead(PinAnalogico);

    lcd.setCursor(0, 1); 
    lcd.print("Freq: ");
    lcd.print(ValorActual);
    lcd.print(" Hz    "); 

    
    for (int i = 0; i < 20; i++) {
        if (Datos[i] == 0) {  
            Datos[i] = ValorActual;

            if (ValorMaximo < Datos[i]) {
                ValorMaximo = Datos[i];
            }
            if (ValorMinimo > Datos[i]) {
                ValorMinimo = Datos[i];
            }
            break;  
        }
    }

   
    Amplitud = (ValorMaximo - ValorMinimo) / 2.0;

    
    Tiempo();

    
    float Frecuencia = 1000000.0 / LapsoPicos; 

    
    if (Frecuencia > 0) { 
        LongitudOnda = VelocidadOnda / Frecuencia;
    }

    
    if (Pico) {
        Serial.print("Lapso entre picos: ");
        Serial.print(LapsoPicos);
        Serial.println(" microsegundos");
        Serial.print("Longitud de Onda: ");
        Serial.print(LongitudOnda);
        Serial.println(" m");
        Pico = 0; 
    }

    delay(100); 
}

void Tiempo() {
    TiempoReal = micros();
  
    if (TiempoAnterior != 0) {
        LapsoPicos = TiempoReal - TiempoAnterior; 
    }
    TiempoAnterior = TiempoReal;
    Pico = 1; 
}

void DeteccionDeOnda() {
  for(int j = 0; j < 19; j++ ){
    if (Datos[j] == Datos[j+1]){
    TipoDeOnda = "La onda es cuadrada";
    break;
    }
                         
  }
}
