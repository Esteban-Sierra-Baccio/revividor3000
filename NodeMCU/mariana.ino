#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "Tec-IoT";
const char* password = "spotless.magnetic.bridge";

Adafruit_MLX90614 mlx = Adafruit_MLX90614(); //Se declara una variable u objeto para el sensor
float t = 0;
int estado = 0; //Estado del LED
int val = 0; //Estado de button
int old_val = 0;
#define verde  2 //verde
#define amarillo 12  //amarillo
#define rojo 14 //rojo
#define button 0


HTTPClient httpClient;
WiFiClient wClient;

String URL = "http://10.22.229.203:3100/api/logTemp/1/";
String URL2 = "http://10.22.229.203:3100/api/logButton/7/";

void setup() {
  pinMode(button, INPUT);
  pinMode(verde, OUTPUT);
  pinMode(amarillo, OUTPUT);
  pinMode(rojo, OUTPUT);
  Serial.begin(9600); //Se inicia el monitor serie a 9600 baudios
  Serial.println("Iniciando test del MLX90614");
  mlx.begin(); //Se inicia el sensor

  
  Serial.begin(9600); 
  Serial.println("*Inicializando conexión a My SQL*");

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
    t = mlx.readObjectTempC();
    if (isnan(t)) {
      Serial.println("Error obteniendo los datos del sensor");
      return;
    }
    else{
    val = digitalRead(button);
  if(val == HIGH &&(old_val == LOW)){
    estado = 1-estado;
    delay(10);
  }
  old_val = val;
  if(estado==0){
    if (t > 33 && t < 42 ) {

      if (t >= 33 && t <= 35) {
        digitalWrite(amarillo, HIGH);
        digitalWrite(rojo, LOW);
        digitalWrite(verde, LOW);
      }
      else if (t >= 35.1 && t < 37.5) {
        digitalWrite(verde, HIGH);
        digitalWrite(amarillo, LOW);
        digitalWrite(rojo, LOW);
      }
      else if (t >= 37.5 && t <= 42) {
        digitalWrite(rojo, HIGH);
        digitalWrite(verde, LOW);
        digitalWrite(amarillo, LOW);
      }

      //Se imprimen los datos de sensor
      logIntento(t);
      Serial.print("Temperatura del Objeto= ");
      Serial.print(t); Serial.println(" °C");
      Serial.println();
      delay(500);
    }
    else {
      digitalWrite(verde, LOW);
      digitalWrite(amarillo, LOW);
      digitalWrite(rojo, LOW);
    }
  }
  else {
    digitalWrite(verde, LOW);
    digitalWrite(amarillo, LOW);
    digitalWrite(rojo, LOW);
  }
   
 }
}

void logIntento(float t){
  if(WiFi.status() == WL_CONNECTED){
    String data = URL;
    data = data + t;
    Serial.println(data); 
    
    httpClient.begin(wClient, data.c_str()); 
    httpClient.addHeader("Content-Type", "Content-Type: application/json");
    int httpResponseCode = httpClient.POST(data.c_str());
    Serial.println(httpResponseCode); 
    httpClient.end(); 
  }
  return;
}
