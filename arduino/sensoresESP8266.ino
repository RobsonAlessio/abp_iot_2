

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <Ticker.h>

// Set these to run example.
#define FIREBASE_HOST "sua_url_do_firebase_aqui.firebaseio.com"
#define FIREBASE_AUTH "segredo_do_firebase_aqui"
#define WIFI_SSID "wifi_da_sua_casa"
#define WIFI_PASSWORD "senha_da_wifi"

#define DHT_PIN D5
// Publique a cada 5 min
#define PUBLISH_INTERVAL 2000

Ticker ticker;
bool publishNewState = true;

void publish(){
  publishNewState = true;
}


void setupWifi(){
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
}

void setupFirebase(){
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.setBool("lamp", false);
  Firebase.setBool("presence", false);
}

void setup() {
  Serial.begin(9600);

  setupWifi();    

  setupFirebase();

  // Registra o ticker para publicar de tempos em tempos
  ticker.attach_ms(PUBLISH_INTERVAL, publish);
}

void loop() {

  // Apenas publique quando passar o tempo determinado
  if(publishNewState){
    Serial.println("Publicando novo estado: ");
    // Obtem os dados do sensor DHT 
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();

    if(!isnan(humidity) && !isnan(temperature)){
      // Manda para o firebase
      Firebase.pushFloat("temperature", temperature);
      Firebase.pushFloat("humidity", humidity);    
      publishNewState = false;
    }else{
      Serial.println("Erro na publicação...");
    }
  }

  
  delay(200);
}
