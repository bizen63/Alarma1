#include <Keypad.h>
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
// Conexiones de la pantalla LCD al adaptador
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); // Addr, En, Rw, Rs, d4, d5, d6, d7, backlighpin, polarity
 
//Código necesario para manejar el keypad
const byte filas = 4;
const byte columnas = 4;
byte pinsFilas[filas] = {11, 10, 9, 8}; //correspondencia pin-fila
byte pinsColumnas[columnas] = {7, 6, 5, 4}; //correspondencia pin-columna

char teclas [filas][columnas] = {
  
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'},
  };
  
 Keypad teclado = Keypad(makeKeymap(teclas), pinsFilas, pinsColumnas, filas, columnas);
//Fin del código necesario para manejar el keypad

char tecla;
char char1;
char char2;
char char3;
char char4;
int c = 0; //contador de pulsaciones de caractares
const int salida = 13;
// Inicio declaraciones módulo PIR
const int pinSensor = 0;
const int pinSalida = 1;
int estado;
// Fin declaraciones módulo PIR
void setup() {
pinMode(salida, OUTPUT);
// Inicio configuración módulo PIR
  pinMode(pinSensor, INPUT);
  pinMode(pinSalida, OUTPUT);
  digitalWrite(pinSalida, LOW);
// Fin configuración módulo PIR
digitalWrite(salida, LOW);
 Serial.begin(9600);
 	// Inicializamos la pantalla LCD
	lcd.begin(16,2);
//	lcd.noBacklight(); //Comentar para retroiluminar el display
 
	// Situamos el cursor en la primera casilla de la primera fila y escribimos un texto
	lcd.setCursor(0, 0);
        lcd.print("  ALARMA IES TM ");
        // Situamos el cursor en la primera casilla de la segunda fila
        lcd.setCursor(0, 1);
        lcd.print("PASSWORD:");
}


void loop() {

  tecla = teclado.getKey();
  
  if(tecla != NO_KEY && c<4){
    Serial.print(tecla); //monitorizamos carateres teclado
    Serial.print(c);     // monitorizamos pulsaciones teclado
   switch (c){
     case 0:
    c++;
    char1 = tecla;
    lcd.setCursor(11, 1);
    lcd.print("*");
    delay (50);
    break;
     case 1:
     char2 = tecla;
     c++;
    lcd.setCursor(12, 1);
    lcd.print("*");
    delay (50);
    break;
    case 2:    
    char3 = tecla;
    c++;
    lcd.setCursor(13, 1);
    lcd.print("*");
    delay (50);
    break;
    case 3:    
    char4 = tecla;
    c++;      //Saca de rango la alarma para no poder seguir introduciendo caracteres
    lcd.setCursor(14, 1);
    lcd.print("*");
    delay (50);
    break;
  }
    
  }
if(char1 == '#' && char2 == '2' && char3 == '9' && char4 == '#' && estado == LOW){
  digitalWrite(salida, HIGH);
  // Limpiamos la segunda linea de la pantalla LCD
	for(int i = 0; i < 16; i++){
	lcd.setCursor(i, 1);
	lcd.print(" ");
	}
        lcd.setCursor(0, 1);
        lcd.print("ALARMA ACTIVADA");
        delay(500);
 // La alarma PIR comienza a trabajar
        estado = digitalRead(pinSensor);
  if( estado == HIGH){
    
   
     // Limpiamos la primera linea de la pantalla LCD
	for(int i = 0; i < 16; i++){
	lcd.setCursor(i, 0);
	lcd.print(" ");
	}
        lcd.setCursor(0, 0);
        lcd.print("INTRUSION");
         // Limpiamos la segunda linea de la pantalla LCD
	for(int i = 0; i < 16; i++){
	lcd.setCursor(i, 1);
	lcd.print(" ");
	}
        lcd.setCursor(0, 1);
        lcd.print("DETECTADA");
        
           }
    
   else {
      digitalWrite(pinSalida, LOW);
      }
  }
  else {
      digitalWrite(salida, LOW);
       
	
        
      }
while(estado == HIGH){
        digitalWrite(pinSalida, HIGH);
        delay(1000);
        digitalWrite(pinSalida, LOW);
        delay(1000);
                }
}
