#include <LiquidCrystal.h>

// Definición de pines
const int pirPin = 7;
const int buttonPin = 8;
const int ledPin = 9;

// Variables globales
unsigned long tiempo1 = 0;
unsigned long tiempo2 = 0;
unsigned long tiempoInicioContador = 0;
unsigned long tiempoTotal = 0;
bool contadorActivo = false;

// Inicialización del LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // Inicialización del LCD
  lcd.begin(16, 2);
  lcd.print("Temporizador F1");
  lcd.setCursor(0, 1); 
  lcd.print("Tiempo: 0:00:000");
  
  // Configuración de pines
  pinMode(pirPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Detección de movimiento
  if (digitalRead(pirPin)) {
    if (!contadorActivo) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Start");
      delay(1000);
      tiempo1 = millis(); 
      contadorActivo = true;
      tiempoInicioContador = millis(); 
    } else {
      tiempo2 = millis(); 
      tiempoTotal = tiempo2 - tiempo1;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Finish");
      lcd.setCursor(0, 1);
      lcd.print("Tiempo: ");
      // Calcular minutos, segundos y milisegundos
      unsigned long minutos = tiempoTotal / 60000;
      unsigned long segundos = (tiempoTotal / 1000) % 60;
      unsigned long milisegundos = tiempoTotal % 1000;
      // Mostrar en el formato deseado
      lcd.print(minutos);
      lcd.print(":");
      if (segundos < 10) {
        lcd.print("0"); 
      }
      lcd.print(segundos);
      lcd.print(":");
      if (milisegundos < 100) {
        lcd.print("0"); 
      }
      if (milisegundos < 10) {
        lcd.print("0"); 
      }
      lcd.print(milisegundos);
      
      // Detener el contador
      contadorActivo = false;
    }
    delay(2000); // Retraso de 2 segundos
  }

  // Mostrar el contador durante la segunda detección de movimiento
  if (contadorActivo) {
    unsigned long tiempoTranscurrido = millis() - tiempoInicioContador;
    unsigned long minutos = tiempoTranscurrido / 60000;
    unsigned long segundos = (tiempoTranscurrido / 1000) % 60;
    unsigned long milisegundos = tiempoTranscurrido % 1000;
    lcd.setCursor(0, 1);
    lcd.print("Tiempo: ");
   
    lcd.print(minutos);
    lcd.print(":");
    if (segundos < 10) {
      lcd.print("0");
    }
    lcd.print(segundos);
    lcd.print(":");
    if (milisegundos < 100) {
      lcd.print("0"); 
    }
    if (milisegundos < 10) {
      lcd.print("0"); 
    }
    lcd.print(milisegundos);
  }

  // Reiniciar el contador si se pulsa el botón
  if (!digitalRead(buttonPin)) {
    tiempoTotal = 0;
    contadorActivo = false;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Contador: F1");
    lcd.setCursor(0, 1);
    lcd.print("Tiempo: 0:00:000");
    delay(500); 
  }

  // Encender el LED si el tiempo total es menor que 10 segundos
  if (tiempoTotal < 10000 && contadorActivo) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  delay(100);
}
