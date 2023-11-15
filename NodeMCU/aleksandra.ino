#include <Wire.h>                  
#include <LiquidCrystal_I2C.h>    
LiquidCrystal_I2C lcd(0x27, 16, 2);//Direccion de LCD
#include "DHT.h"
#include <DHT_U.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#define DHTPIN 0 //Conectamos el Sensor al pin digital 9
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);


// Conexion a internet
const char* ssid = "Tec-IoT";
const char* password = "spotless.magnetic.bridge";


HTTPClient httpClient;
WiFiClient wClient;


String URLTemp = "http://10.22.181.110:3100/api/logTemp/1/";
String URLHum = "http://10.22.181.110:3100/api/logHum/1/";


// Conexion a LCD
void setup() {
  lcd.init(); // Indicamos medidas de LCD
  lcd.backlight();
  lcd.clear();
  Serial.begin(9600);
  dht.begin();


  Serial.println("***Inicializando conexión a My SQL***");
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);


  WiFi.begin(ssid, password);
  Serial.print("Conectando a red WiFi \"");
  Serial.print(ssid);
  Serial.print("\"");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("\nConectado! IP: ");
  Serial.println(WiFi.localIP());
  delay(500);


}


void loop() {


float hume = dht.readHumidity();    // Lee la humedad
float temp = dht.readTemperature();  // Y la temperatura
Serial.println(hume);
Serial.println(temp);
     
if( isnan(temp) || isnan(hume)) {
  Serial.println("Error leyendo datos!!");
  return;
}
if(temp >= 23 || temp <= 25){    
  logIntento(temp);
  logIntento1(hume);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Estamos a ");
  lcd.print(String(abs(temp)));//Escribe la temperatura
  lcd.print("C");  
  lcd.setCursor(0, 1);
  lcd.print("Temp. baja");            
}
if(temp >= 26 || temp <= 30){
  logIntento(temp);
  logIntento1(hume);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Estamos a ");
  lcd.print(String(abs(temp)));//Escribe la temperatura
  lcd.print("C");  
  lcd.setCursor(0, 1);
  lcd.print("Temp. intermedia");
}
if(temp > 30){
  logIntento(temp);
  logIntento1(hume);  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Estamos a ");
  lcd.print(String(abs(temp)));//Escribe la temperatura
  lcd.print("C");  
  lcd.setCursor(0, 1);
  lcd.print("Temp. alta");
}
  Serial.println("Temperatura: " + String(abs(temp)) + "Humedad: " + String(abs(hume)));
  delay(2000);
}


void logIntento(float temp){


  if(WiFi.status() == WL_CONNECTED){
    String data = URLTemp;
    data = data + temp;
    Serial.println(data);
   
    httpClient.begin(wClient, data.c_str());
    httpClient.addHeader("Content-Type", "Content-Type: application/json");
    int httpResponseCode = httpClient.POST(data.c_str());
    Serial.println(httpResponseCode);
    httpClient.end();
}
return;
}
void logIntento1(float hume){


  if(WiFi.status() == WL_CONNECTED){
    String data = URLHum;
    data = data + hume;
    Serial.println(data);
    httpClient.begin(wClient, data.c_str());
    httpClient.addHeader("Content-Type", "Content-Type: application/json");
    int httpResponseCode = httpClient.POST(data.c_str());
    Serial.println(httpResponseCode);
    httpClient.end();
}
return;
}

