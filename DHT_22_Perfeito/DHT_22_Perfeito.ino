#include <Wire.h>
#include "Barometer.h"
#include <LiquidCrystal_I2C.h>
#include <Adafruit_BMP085.h>




//          LCD                 //
#define LCD_ADDR 0x27 // I2C address
#define EN 2 // LCD En (Enable)
#define RW 1 // LCD Rw (Read/write)
#define RS 0 // LCD Rs (Reset)
#define D4 4 // LCD data 0
#define D5 5 // LCD data 1
#define D6 6 // LCD data 2
#define D7 7 // LCD data 3
#define BACKLIGHT_PIN 3
#define BACKLIGHT_POL POSITIVE //ligar ou nao o backlight (luz de fundo). Valor pode ser POSITIVE ou NEGATIVE

#define COLUNAS 16 // quantidade de colunas do LCD
#define LINHAS 2 // quantidade de linhas do LCD

LiquidCrystal_I2C lcd(LCD_ADDR, EN, RW, RS, D4, D5, D6, D7, BACKLIGHT_PIN, BACKLIGHT_POL);

//    LM 35                //
int pinoSensor = A0;
int valorLido = 0;
float temperatura = 0;


//          DHT 22         //
#include "DHT.h"
#define DHTPIN 53    
#define DHTTYPE DHT22   
DHT dht(DHTPIN, DHTTYPE);

//          BMP 180          //
Adafruit_BMP085 bmp;



int cont = 0;
float pressao = 0;
void setup() {

 Serial.begin(9600);
 //LCD
 lcd.begin(COLUNAS,LINHAS);
 lcd.print("    Grupo 8");
 delay(1000);
 lcd.clear();
 //DHT 22
 dht.begin();
 
 if (!bmp.begin()) {
	Serial.println("Could not find a valid BMP085 sensor, check wiring!");
	while (1) {}
  }
  
 
}

void loop(){
  //  Medicao DHT 22
  
  float h = dht.readHumidity();
  float t = dht.readTemperature();
 
  if (isnan(h) || isnan(t)) {
    lcd.print("Failed to read!");
  
    return;
  }
  

  
  
  
  // Medicao LM35     
  valorLido = analogRead(pinoSensor);
  temperatura = (valorLido * 0.00488);
  temperatura = temperatura * 100;
   
  
  //  Medicao  BMP 180
 
  pressao = bmp.readTemperature();
  
  //  Serial
  Serial.print("Umidade: ");
  Serial.print(h);
  
  Serial.print("  Temperatura: ");
  Serial.print(temperatura);
  
  Serial.print("  Pressure: ");
  Serial.print(pressao, 0); //whole number only.
  Serial.println(" Pa");
  
  Serial.print("  Medicao n: ");
  Serial.print(cont);
  Serial.println("");
  
  
  // LCD
  lcd.print("Umidade:  DHT22 "); 
  lcd.setCursor(0,1);
  lcd.print(h);
  lcd.setCursor(6,1);
  lcd.print("%");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temp:    LM35 "); 
  lcd.setCursor(0,1);
  lcd.print(temperatura);
  lcd.setCursor(6,1);
  lcd.print("C");
  delay(3000);
  lcd.clear();
  
  lcd.setCursor(0,0);
  lcd.print("Pressao: BMP 180"); 
  lcd.setCursor(0,1);
  lcd.print(pressao);
  lcd.setCursor(6,1);
  lcd.print("Pa");
  delay(3000);
  
  lcd.clear();
  
  
  
  cont++;
  delay(2000);
  lcd.clear();
  
  
  
  
 }
 
 
