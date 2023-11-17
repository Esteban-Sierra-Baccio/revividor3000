#include <Wire.h>

//Defino pines para NodeMCU
//MOTORES
#define ENA 4 // D2
#define ENB 2 // D4
#define IN1 0 // D3
#define IN2 13 // D7
#define IN3 12 // D6
#define IN4 14 // D5

//SEGUIDOR DE LÍNEA
const int SEG1 = D0;
const int SEG2 = D1;


void setup() {
  Serial.begin(9600);


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
