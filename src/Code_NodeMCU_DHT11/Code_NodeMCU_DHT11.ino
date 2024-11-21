#include <DHT.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

<<<<<<< HEAD
#define WIFI_SSID       "KNET_2G" // Nome da rede wifi
=======
#define WIFI_SSID       "" // Nome da rede wifi
>>>>>>> 76094c2 (sensitive data removed)
#define WIFI_PASS       "" // Senha da rede wifi

#define DHTPIN          2     // Pino onde o sensor DHT11 está conectado
#define DHTTYPE         DHT11 // Tipo de sensor (DHT11, DHT22, AM2302)

#define BUZZER_PIN      4 // Pino onde o buzzer ativo está conectado

#define MQTT_SERVER     "test.mosquitto.org"  // Endereço do broker
#define MQTT_PORT       1883  // porta
#define MQTT_USER       ""  // O nome de usuário configurado no broker
#define MQTT_PASSWORD   ""    // A senha configurada no broker
#define MQTT_TOPIC      "ksdht11/th" // tópico para publicação

#define WARNING_TEMP    40 // Em celsius
#define WARNING_HUM     30 // Porcentagem mínima de UR

DHT dht(DHTPIN, DHTTYPE);
WiFiClient espClient;
PubSubClient client(espClient);

struct SensorData {
  float temperature;
  float humidity;
};

void setup() {
  Serial.begin(115200);
  dht.begin();
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Conectando ao WiFi...");
  }
  Serial.println("Conectado ao WiFi");

  pinMode(BUZZER_PIN, OUTPUT);

  client.setServer(MQTT_SERVER, MQTT_PORT);
}

void loop() {
  //  Leitura do sensor
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  //  Print no serial dos dados obtidos
  Serial.print("Temperatura: ");
  Serial.print(temp);
  Serial.println(" °C");
  Serial.print("Umidade: ");
  Serial.print(hum);
  Serial.println("%");

  // Toque de alerta em caso de temperatura acima do esperado
  if (temp > WARNING_TEMP) {
    tone(BUZZER_PIN, 500);
    delay(400);
    noTone(BUZZER_PIN);
  }

  // Toque de alerta em caso de umidade relativa do ar abaixo do esperado
  if (hum < WARNING_HUM) {
    tone(BUZZER_PIN, 800);
    delay(150);
    noTone(BUZZER_PIN);

    delay(50);

    tone(BUZZER_PIN, 800);
    delay(150);
    noTone(BUZZER_PIN);
  }

  client.connect("NodeMCU_Client", MQTT_USER, MQTT_PASSWORD);
  
  if (client.connected()) {
    struct SensorData data;
    data.temperature = temp;
    data.humidity = hum;

    // Convertendo a estrutura SensorData para uma string
    char payload[50];  // ajuste o tamanho conforme necessário
    sprintf(payload, "{\"temperature\": %.2f, \"humidity\": %.2f}", data.temperature, data.humidity);

    Serial.println("Conectado ao Broker, tentando publicar...");

    // Publicando a string formatada
    if (client.publish(MQTT_TOPIC, payload)) {
      Serial.println("Publicação de temperatura bem-sucedida");
    } else {
      Serial.println("Falha na publicação de temperatura");
    }
  } else {
    Serial.println("Não conectado ao Broker");
    return;
  }
  client.disconnect();
  delay(2000); // Intervalo de leitura
}
