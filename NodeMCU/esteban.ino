/*
 *  Lector de RFID con BUZZER y BOTON de iniciacion
 *  Esteban Sierra Baccio
 *  3 / Nov / 2023
*/


// Librerías para hacer uso del RFID
#include <SPI.h>
#include <MFRC522.h> // Esta se descarga de aqui: https://github.com/miguelbalboa/rfid

// Librerías para conectarnos a internet, mandar y recibir información
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

// Se declaran los pines a usar
#define button 16 // D0
#define RST_PIN 0 // D3
#define SS_PIN 2 // D4
#define BZ_PIN 4 // D2


// Se crean las instancias necesarias.
MFRC522 rfid(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;


// Se crean las variables necesarias
String tag;
int val = 0;
int old_val = 0;
int estado = 0;

///

const char* ssid = "Tec-IoT";
const char* password = "spotless.magnetic.bridge";

HTTPClient httpClient;
WiFiClient wClient;

String URL = "http://10.22.224.37:3100/api/logTemp/1/"; // pc.server:nodejsport/api/LogTemp/1/


void setup() {
  // Iniciamos el monitor serial
  Serial.begin(9600);

  // Iniciamos el RFID
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522
  pinMode(BZ_PIN, OUTPUT);
  Serial.println("Iniciando...");

  // Iniciamos conexión a internet
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
  // Si el botón detecta un click, cambia el valor del estado
  val = digitalRead(button);
  if(val == HIGH &&(old_val == LOW)){
    estado = 1-estado;
    delay(10);
  }
  old_val = val;


  // Si el botón está en ON, se comporta de esta manera.
  if(estado==1){
      if ( ! rfid.PICC_IsNewCardPresent())
    return;
  if (rfid.PICC_ReadCardSerial()) {
    for (byte i = 0; i < 4; i++) {
      tag += rfid.uid.uidByte[i];
    }
    Serial.println(tag);
    logIntento(tag);
    //isTagInDatabase();
    // Si el tag es el esperado, el sonido se repetirá 3 veces
    if (tag == "67201018") {
      Serial.println("Acceso concedido!");
      digitalWrite(BZ_PIN, HIGH);
      delay(100);
      digitalWrite(BZ_PIN, LOW);
      delay(100);
      digitalWrite(BZ_PIN, HIGH);
      delay(100);
      digitalWrite(BZ_PIN, LOW);
      delay(100);
      digitalWrite(BZ_PIN, HIGH);
      delay(100);
      digitalWrite(BZ_PIN, LOW);
      delay(100);
    } else {
      // SI el tag es incorrecto, el sonidosolo se escuchará una vez, pero por dos segundos.
      Serial.println("Access Denied!");
      digitalWrite(BZ_PIN, HIGH);
      delay(2000);
      digitalWrite(BZ_PIN, LOW);
    }
    // Se reinician las variables, y los sensores se reinician.
    tag = "";
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  }
  }
  else{}
 
}


void logIntento(String t){
  
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
/*
void isTagInDatabase(){
  if(WiFi.status() == WL_CONNECTED){
    String data = URL;
    Serial.println(data); 
    
    httpClient.begin(wClient, data.c_str()); 
    httpClient.addHeader("Content-Type", "Content-Type: application/json");
    int httpResponse = httpClient.GET();
    Serial.println(httpResponse); 
    Serial.println(httpClient.getString());

    DynamicJsonDocument doc(256);
    DeserializationError error = deserializeJson(doc, httpClient.getString());
    if(error){
      Serial.println("Error al analizar el JSON");
    } else {
      //Extraer datos del JSON
      Serial.println(doc["data"])
    }
    
    httpClient.end(); 
  
}
*/