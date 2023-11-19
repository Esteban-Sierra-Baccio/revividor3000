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

String ip = "10.22.238.112";
String port = "3100";

String URL = "http://" + ip + ":" + port + "/api/logtag/5/"; // pc.server:nodejsport/api/LogTemp/1/


void setup() {
  // Iniciamos el monitor serial
  Serial.begin(9600);

  // Iniciamos el RFID
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522
  pinMode(BZ_PIN, OUTPUT);
  Serial.println("Iniciando...");

  // Iniciamos conexión a internet
  Serial.println("**Inicializando conexión a My SQL**");

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


    
    Serial.println("Tag recibido: " + tag);
    bool an = isTagInDatabase(tag);

    
    // Si el tag es el esperado, el sonido se repetirá 3 veces
    if (an) {
      Serial.println("Acceso_concedido");
      logIntento(tag,"Acceso_concedido");
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
      logIntento(tag,"Acceso_denegado");
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

void logIntento(String t,String lgbt){
  Serial.print("Iniciando proceso POST: ");
  String respuesta;
  respuesta = String("/") + "'" + lgbt + "'";

  if(WiFi.status() == WL_CONNECTED){
    String data = URL;
    data = data + t + respuesta;
    Serial.println(data); 
    
    httpClient.begin(wClient, data.c_str());
    httpClient.addHeader("Content-Type", "Content-Type: application/json");
    int httpResponseCode = httpClient.POST(data.c_str());
    
    Serial.println(httpResponseCode);
    Serial.println(httpClient.errorToString(httpResponseCode).c_str());

    httpClient.end(); 
  } else {
    Serial.println("NodeMCU no conectado a Internet");
    }
  return;
}

String nUrl = "http://" + ip + ":" + port + "/api/getLogs/5";

bool isTagInDatabase(String tagg){
  Serial.println("Iniciando proceso GET: " + nUrl);
  if(WiFi.status() == WL_CONNECTED){
    
    httpClient.begin(wClient,nUrl); //Specify the URL
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
    String value = doc["data"][0]["tag"];

    while (value.endsWith("\r") || value.endsWith("\n")) {
      value.remove(value.length() - 1); // Elimina el último carácter
    }
    //long val = atol(value.c_str());
    //types(val);
    
    Serial.print(value);
    Serial.print(" == ");
    Serial.println(tagg);

    httpClient.end();
    if(value == tagg){
      return true;
    } else {
      return false;
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
  return false;
}
