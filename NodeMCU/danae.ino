#include <Wire.h>
//Conexión a WiFi
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
//Establecer cliente de HTTP (librería)
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

//Defino pines para NodeMCU
//MOTORES
#define ENA 4 // D2
#define ENB 2 // D4
#define IN1 0 // D3
#define IN2 13 // D7
#define IN3 12 // D6
#define IN4 14 // D5

//SEGUIDOR DE LÍNEA
#define SEG1 16 // D0
#define SEG2 5 // D1

//Nombre y password de la red
const char* ssid = "Tec-IoT";
const char* password = "spotless.magnetic.bridge";


//Variables para HTTP de cliente
HTTPClient httpClient;
WiFiClient wClient;


//Liga generada con Postman
String URLcolor = "http://10.22.172.75:3100/api/getLogs/6";

void setup() {
  Serial.begin(9600);

  //Iniciar Serial Monitor
  Serial.println("**Inicializando conexión a My SQL**");


  //Conectar a internet
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
  //Mostrar IP a la que estamos conectado
  Serial.print("\nConectado! IP: ");
  Serial.println(WiFi.localIP());
  delay(500);

  // Establecemos modo de los pines de los sensores infrarrojo
  pinMode(SEG1, INPUT);    
  pinMode(SEG2, INPUT);

  // Establecemos modo de los pines del control de motores
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Configuramos los dos motores a velocidad 150/255
  analogWrite(ENA, 150); 
  analogWrite(ENB, 150);  

  // Configuramos sentido de giro
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void loop() {


// Leemos el valor de los infrarrojo: 0 - fondo claro y 1 - línea negra
  int valorInfra = digitalRead(SEG1);  
  int valorInfra1 = digitalRead(SEG2);
     
  if( isnan(valorInfra) || isnan(valorInfra1)) {
    Serial.println("Error leyendo datos!!");
    return;
  }


  // Cuatro escenarios: De frente      
  if(valorInfra == 0 && valorInfra1 == 0){
    Serial.println("Ninguno en linea");
    // Modificamos sentido de giro de los motores
    //Motor izquierdo
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    //Motor derecho
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    isColorRed("Rojo");
  }


  // El robot encuentra línea negra con el infrarrojo derecho y hay que corregir girando a la derecha
  if(valorInfra == 0 && valorInfra1 == 1){  
    Serial.println("Derecho en linea");
    // Modificamos sentido de giro de los motores
    //Motor izquierdo
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    //Motor derecho
    digitalWrite(IN3, LOW);
    digitalWrite(IN4,HIGH);
  }


  // El robot encuentra línea negra con el infrarrojo izquierdo y hay que corregir girando a la izquierda
  if(valorInfra == 1 && valorInfra1 == 0){
    // Modificamos sentido de giro de los motores
    Serial.println("Izquierdo en linea");
    //Motor izquierdo
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2, LOW);
    //Motor derecho
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4, LOW);
  }
}

void isColorRed(String color){
  if(WiFi.status() == WL_CONNECTED){
    
    httpClient.begin(wClient,URLcolor); //Specify the URL
    int httpCode = httpClient.GET();                                 //Make the request
    
    if (httpCode > 0) { //Check for the returning code
      if (httpCode == HTTP_CODE_OK) { 
        String payload = httpClient.getString();
        Serial.println(httpCode);
        Serial.println(payload);

// Analizar el JSON

DynamicJsonDocument doc(256);
DeserializationError error = deserializeJson(doc, payload);

  if (error) {
    Serial.println("Error al analizar el JSON");
  } else {
    // Extraer datos del JSON
    String value = doc["data"][0]["color"];

    while (value.endsWith("\r") || value.endsWith("\n")) {
      value.remove(value.length() - 1); // Elimina el último carácter
    }

    Serial.print(value);
    Serial.print(" == ");
    Serial.println(color);

    httpClient.end();
    if(value == color){
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      //Motor derecho
      digitalWrite(IN3, LOW);
      digitalWrite(IN4,HIGH);
      delay(5000);
    } else {
    }

  }

// Fin del análisis del JSON       
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", httpClient.errorToString(httpCode).c_str());
      }
    } else {
      Serial.println("Error on HTTP request");
    }
    
    httpClient.end(); //Free the resources
  } else {Serial.println("NodeMCU no conectado a Internet");}
}