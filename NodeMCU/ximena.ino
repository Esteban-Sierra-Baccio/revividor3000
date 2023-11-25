//Conexión a WiFi
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
//Establecer cliente de HTTP (librería)
#include <ESP8266HTTPClient.h>

//Se definen variables del sensor de color
const int S0 = D4;
const int S1 = D3;
const int S2 = D1;
const int S3 = D0;
const int sensorOut = D2;

//Colores básicos del sensor, que serán calculados por métodos
int rojo = 0;
int azul = 0;
int verde = 0;
String colorR = "";

//Nombre y password de la red
const char* ssid = "Tec-IoT";
const char* password = "spotless.magnetic.bridge";

//Variables para HTTP de cliente
HTTPClient httpClient;
WiFiClient wClient;

//Liga generada con Postman
String URL = "http://10.22.229.203:3100/api/logColor/6/";

void setup() {
  Serial.begin(9600); 
  Serial.println("Inicio");
  //Pines del sensor de color
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);

  //Establecer sensorOut como input
  pinMode(sensorOut, INPUT);
  digitalWrite(S0, HIGH);
  digitalWrite(S1, HIGH);

  //Iniciar Serial Monitor
  Serial.println("***Inicializando conexión a My SQL***");

  //Conectar a internet
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  Serial.println("Hola");

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
}

void loop() {
  //Verificar que el sensor nos dé parámetros
  colorR = identificaColor();

    if (colorR == " ") {
      //Si es un valor no aceptable, se muestra error
      Serial.println("Error obteniendo los datos del sensor de colores");
      return;
    }
    //Mostraer temperatura si no entra en if
    Serial.print("\nColor: ");
    Serial.print(colorR);

    //Llamado con temperatura
    logIntento(colorR);
      
    delay(1000);
}

//Log de temperatura en base de datos
void logIntento(String t){
  //Si estoy conectado a internet
  if(WiFi.status() == WL_CONNECTED){
    Serial.println(" ");
    String data = URL;
    data = data + "'" + t + "'";
    Serial.println(data); 
    
    //Inicializar http
    httpClient.begin(wClient, data.c_str()); 
    httpClient.addHeader("Content-Type", "Content-Type: application/json");
    //Hacer post
    int httpResponseCode = httpClient.POST(data.c_str());
    //Imprimir respuesta de http
    Serial.println(httpResponseCode); 
    httpClient.end(); 
  }
  return;
}

void color(){
  //Calcular escala RGB
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  rojo = pulseIn(sensorOut, digitalRead(sensorOut) == HIGH ? LOW : HIGH);
  digitalWrite(S3, HIGH);
  azul = pulseIn(sensorOut, digitalRead(sensorOut) == HIGH ? LOW : HIGH);
  digitalWrite(S2, HIGH);
  verde = pulseIn(sensorOut, digitalRead(sensorOut) == HIGH ? LOW : HIGH);
}

String identificaColor(){
  //Llamada para entonces desplegar en monitor cada cálculo
  color();
  Serial.print("R ");
  Serial.print(rojo, DEC);
  Serial.print("V ");
  Serial.print(verde, DEC);
  Serial.print("A ");
  Serial.print(azul, DEC);

  //Salto de línea
  Serial.println(" ");

  //Parámetros para retornar rojo. Esto ayudará a parar el prototipo cuando se construya la API
  if( rojo >= 3 && rojo <= 25){
    if(verde >= 32 && verde <= 45){
      if(azul >= 22 && azul <= 38){
            return "Rojo";
            Serial.println(" ");
            Serial.print("Rojo");
            Serial.println(" ");
      }
    }
  }
  return "No_rojo";

}
