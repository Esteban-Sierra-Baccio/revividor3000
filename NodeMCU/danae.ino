#include <Wire.h>                  
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>


//Defino pines para NodeMCU
//MOTORES


//SEGUIDOR DE LÍNEA
const int SEG1 = D0;
const int SEG2 = D1;


// Conexion a internet
const char* ssid = "Tec-IoT";
const char* password = "spotless.magnetic.bridge";


HTTPClient httpClient;
WiFiClient wClient;


String URLSeg = "http://10.22.172.75:3100/api/logSegLinea/3/"; // URL con IP y device_ID 3
String URLSeg2 = "http://10.22.172.75:3100/api/logSegLinea2/4/"; // URL con IP y device_ID 4


void setup() {
  Serial.begin(9600);


  // Establecemos modo de los pines de los sensores infrarrojo
  pinMode(SEG1, INPUT);    
  pinMode(SEG2, INPUT);


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


// Leemos el valor de los infrarrojo: 0 - fondo claro y 1 - línea negra
  int valorInfra = digitalRead(SEG1);  
  int valorInfra1 = digitalRead(SEG2);


  Serial.println(valorInfra);
  Serial.println(valorInfra1);
     
  if( isnan(valorInfra) || isnan(valorInfra1)) {
    Serial.println("Error leyendo datos!!");
    return;
  }


  // Cuatro escenarios: De frente      
  if(valorInfra == 0 && valorInfra1 == 0){
    logIntento(valorInfra);
    logIntento1(valorInfra1);


    Serial.println("Ninguno en linea");
    delay(40);                    
  }


  // El robot encuentra línea negra con el infrarrojo derecho y hay que corregir girando a la derecha
  if(valorInfra == 0 && valorInfra1 == 1){  
    logIntento(valorInfra);
    logIntento1(valorInfra1);


    Serial.println("Derecho en linea");
   
    delay(45);
  }


  // El robot encuentra línea negra con el infrarrojo izquierdo y hay que corregir girando a la izquierda
  if(valorInfra == 1 && valorInfra1 == 0){
    logIntento(valorInfra);
    logIntento1(valorInfra1);
    Serial.println("Izquierdo en linea");
   
    delay(45);
  }


  // Imprimir valores de cada seguidor
  Serial.println("Seguidor de linea 1: " + String(abs(valorInfra)) + " Seguidor de linea 2: " + String(abs(valorInfra1)));
  delay(2000);
}


// Log de Seguidor de Linea 1 en base de datos
void logIntento(int In1){


  if(WiFi.status() == WL_CONNECTED){ // Verificar conexión Wifi
    String data = URLSeg;  
    data = data + In1; // añadir medición al URL
    Serial.println(data); // imprimir url con datos del sensor
    // inicializar http
    httpClient.begin(wClient, data.c_str());
    httpClient.addHeader("Content-Type", "Content-Type: application/json");
    int httpResponseCode = httpClient.POST(data.c_str()); // mandar la solicitud de POST con los datos del sensor
    Serial.println(httpResponseCode); // imprimir respuesta de la solicitud
    httpClient.end();
}
return;
}


// Log de Seguidor de Linea 2 en base de datos
void logIntento1(int In2){


  if(WiFi.status() == WL_CONNECTED){
    String data = URLSeg2;
    data = data + In2; // añadir medición al URL
    Serial.println(data); // imprimir url con datos del sensor
    // inicializar http
    httpClient.begin(wClient, data.c_str());
    httpClient.addHeader("Content-Type", "Content-Type: application/json");
    int httpResponseCode = httpClient.POST(data.c_str()); // mandar la solicitud de POST con los datos del sensor
    Serial.println(httpResponseCode); // imprimir respuesta de la solicitud
    httpClient.end();
}
return;
}
