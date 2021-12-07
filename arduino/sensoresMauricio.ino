/* 
  Referências:
  https://medium.com/@alvaroviebrantz/sensoriamento-realtime-com-firebase-e-esp8266-6e54b9bff1c1#.u00dghukd
*/

//Importações das bibliotecas
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <Ticker.h>

//Definindo o database do Firebase
#define FIREBASE_HOST "abp-iot-2-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "XmMpRoPvM0LHhQVEqx0DWGmneob13BuxeHiGOsrO"
//Definindo a rede WiFi
#define WIFI_SSID "wifi_da_sua_casa"
#define WIFI_PASSWORD "senha_da_wifi"

//Definição das variáveis
#define LED_ONBOARD LED_BUILTIN
const int echoPin = D2; 
const int trigPin = D3;
float distancia; 
String distanciaMauricio;
const int IN_A0 = A0;
int luminosidadeMauricio;
// Publicação a cada 1 segundo
#define PUBLISH_INTERVAL 1000;
Ticker ticker;
bool publishNewState = true;

//Declaração das variáveis
void publish();
void setupWifi();
void setupFirebase();
void setupPinos();
void hcsr04();
void sensorLuminosity();

//VOID SETUP
void setup() {
  Serial.begin(115200);

  setupWifi();    
  setupFirebase();
  setupPinos()
  // Registra o ticker para publicar de tempos em tempos
  ticker.attach_ms(PUBLISH_INTERVAL, publish);
}

//VOID LOOP
void loop() {

  // Apenas publique quando passar o tempo determinado
  if(publishNewState){
    Serial.println("Publicando novo estado: ");
    // Obtem os dados dos sensores
    hcsr04();
    sensorLuminosity();

    if(!isnan(distanciaMauricio) && !isnan(luminosidadeMauricio)){
      // Mandando para o Firebase
      Serial.println("Distância Mauricio: " +(String)distanciaMauricio);
      Serial.println("Luminosidade Mauricio: " +(String)luminosidadeMauricio);
      Firebase.setFloat("distanciaMauricio", distanciaMauricio);
      Firebase.setFloat("luminosidadeMauricio", luminosidadeMauricio);    
      publishNewState = false;
    }else{
      Serial.println("Erro na publicação...");
    }
  }
  delay(200);
}


//Funções criadas

void publish(){
  publishNewState = true;
}

void setupWifi(){
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Conectando");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Conectado - IP: ");
  Serial.println(WiFi.localIP());
}

void setupFirebase(){
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void setupPinos(){
  pinMode(echoPin, INPUT); 
  pinMode(trigPin, OUTPUT); 
  pinMode (IN_A0, INPUT);
  pinMode(LED_ONBOARD, OUTPUT);
}

void hcsr04(){
    digitalWrite(trigPin, LOW); 
    delayMicroseconds(2); 
    digitalWrite(trigPin, HIGH); 
    delayMicroseconds(10); 
    digitalWrite(trigPin, LOW); 
    unsigned long int tempo = pulseIn(echoPin,HIGH); //Retorna o tempo em microsegundos 
    //Distancia = Velocidade(Cm/Ms)*(tempo/2)
    distancia = ((0.034*(tempo/2))/100);
    distanciaMauricio = String(distancia);
    delay(100);
}

void sensorLuminosity(){
  luminosidadeMauricio = analogRead(IN_A0);
}