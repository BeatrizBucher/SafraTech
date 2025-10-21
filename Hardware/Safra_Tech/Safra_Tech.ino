// Faz a conexão do wemos com a rede WI-FI.
#include <ESP8266WiFi.h>
// Inscreve e publica nos topicos MQTT.
// Faz a conexão com o BROKER.
#include <PubSubClient.h>
// Faz o post de objetos JSON.
#include <ArduinoJson.h>
// Faz requisições HTTP
#include <ESP8266HTTPClient.h>

#include <OneWire.h>
#include <DallasTemperature.h>
#define PINO_SENSOR_TEMP D2

//pegando os binarios para entregar em temperaturas
OneWire barramento(PINO_SENSOR_TEMP);
DallasTemperature sensor(&barramento);
// Definição da URL da api.
const char* cadastrarEventos = "http://10.136.245.75:3001/cadastrarEventos";

long int tempoAntigo = 0;
long int contador = 0;

// Definição dos tópicos.
#define topico_convencional "safratech/convencional/irrigacao/campo1"
#define topico_pivo_central "safratech/pivocentral/irrigacao/campo1"
#define topico_autopropelido "safratech/autopropelido/irrigacao/campo1"
#define topico_lateral_movel "safratech/lateralmovel/irrigacao/campo1"
#define topico_gotejamento "safratech/gotejamento/irrigacao/campo1"
#define topico_microaspersao "safratech/microaspersao/irrigacao/campo1"

// Definição dos sensores
// #define temperatura "maquete/ambiente/temperatura";
// #define umidade "maquete/sistema/nivel_umidade";
// #define luminosidade "maquete/ambiente/luminosidade";
// #define nivel_agua "maquete/sistema/nivel_agua";
// #define nivel_bateria "maquete/energia/nivel_bateria";
// #define eficiencia "maquete/energia/eficiencia";

// Definição dos acionamentos ON.
#define liga_luz_convencional digitalWrite(D13, HIGH);
#define liga_luz_pivo_central digitalWrite(D12, HIGH);
#define liga_luz_autopropelido digitalWrite(D11, HIGH);
#define liga_luz_lateral_movel digitalWrite(D10, HIGH);
#define liga_luz_gotejamento digitalWrite(D9, HIGH);
#define liga_luz_microaspersao digitalWrite(D4, HIGH);

// Definição dos acionamentos OF.
#define desliga_luz_convencional digitalWrite(D13, LOW);
#define desliga_luz_pivo_central digitalWrite(D12, LOW);
#define desliga_luz_autopropelido digitalWrite(D11, LOW);
#define desliga_luz_lateral_movel digitalWrite(D10, LOW);
#define desliga_luz_gotejamento digitalWrite(D9, LOW);
#define desliga_luz_microaspersao digitalWrite(D4, LOW);

// Cria conexões com as bibliotecas WiFiClient e PubSubClient.
// Fazendo a instancia.
WiFiClient espClient;
// Nome do objeto e a classe.
PubSubClient mqtt(espClient);

// Enviar as mensagens para o back-end
bool postDadosJson(const String informacao, const int id) {

  // montando o JSON
  StaticJsonDocument<200> doc;

  doc["informacao"] = informacao;
  doc["dispositivo_id"] = id;

  // transforma o objeto em JSON
  String corpo;
  serializeJson(doc, corpo);

  //enviando o JSON com POST
  WiFiClient client;
  HTTPClient http;
  http.begin(client, cadastrarEventos);
  http.addHeader("content-Type", "application/json");
  int code = http.POST(corpo);
  //captura o corpo da resposta (payload) do servidor
  String responsePayload = http.getString();
  //imprime o codigo de status e a resposta no monitor serial
  Serial.print("Código de status HTTP:");
  Serial.print(code);
  Serial.print("Resposta do servidor:");
  Serial.print(responsePayload);
  Serial.print("--------------------------------");
  http.end();
  return (code > 0 && code < 400);
}

// Recebe as mensagens do tópico inscrito.
void callback(char* topic, byte* payload, unsigned int length) {

  String mensagem = "";
  for (int i = 0; i < length; i++) {
    mensagem += (char)payload[i];
  }

  // 0 => TRUE.
  // 1 => FALSE.
  // Função de c++ para comparação.
  // Compara o tópico recebido com o tópico desejado.
  //CONVENCIONAL
  if (strcmp(topic, topico_convencional) == 0) {
    if (mensagem == "on") {
      liga_luz_convencional;
      if (digitalRead(D13)) {
        postDadosJson(mensagem, 1);
      }
    } else if (mensagem == "off") {
      desliga_luz_convencional;
      if (!digitalRead(D13)) {
        postDadosJson(mensagem, 1);
      }
    } else {
      Serial.println("Mensagem inválida!");
    }
  }

  //PIVO_CENTRAL
  if (strcmp(topic, topico_pivo_central) == 0) {
    if (mensagem == "on") {
      liga_luz_pivo_central;
      if (digitalRead(D12)) {
        postDadosJson(mensagem, 2);
      }
    } else if (mensagem == "off") {
      desliga_luz_pivo_central;
      if (!digitalRead(D12)) {
        postDadosJson(mensagem, 2);
      }
    } else {
      Serial.println("Mensagem inválida!");
    }
  }

  //AUTOPROPELIDO
  if (strcmp(topic, topico_autopropelido) == 0) {
    if (mensagem == "on") {
      liga_luz_autopropelido;
      if (digitalRead(D11)) {
        postDadosJson(mensagem, 3);
      }
    } else if (mensagem == "off") {
      desliga_luz_autopropelido;
      if (!digitalRead(D11)) {
        postDadosJson(mensagem, 3);
      }
    } else {
      Serial.println("Mensagem inválida!");
    }
  }

  //LATERAL_MOVEL
  if (strcmp(topic, topico_lateral_movel) == 0) {
    if (mensagem == "on") {
      liga_luz_lateral_movel;
      if (digitalRead(D10)) {
        postDadosJson(mensagem, 4);
      }
    } else if (mensagem == "off") {
      desliga_luz_lateral_movel;
      if (!digitalRead(D10)) {
        postDadosJson(mensagem, 4);
      }
    } else {
      Serial.println("Mensagem inválida!");
    }
  }

  //GOTEJAMENTO
  if (strcmp(topic, topico_gotejamento) == 0) {
    if (mensagem == "on") {
      liga_luz_gotejamento;
      if (digitalRead(D9)) {
        postDadosJson(mensagem, 5);
      }
    } else if (mensagem == "off") {
      desliga_luz_gotejamento;
      if (!digitalRead(D9)) {
        postDadosJson(mensagem, 5);
      }
    } else {
      Serial.println("Mensagem inválida!");
    }
  }

  //MICROASPERSAO
  if (strcmp(topic, topico_microaspersao) == 0) {
    if (mensagem == "on") {
      liga_luz_microaspersao;
      if (digitalRead(D4)) {
        postDadosJson(mensagem, 6);
      }
    } else if (mensagem == "off") {
      desliga_luz_microaspersao;
      if (!digitalRead(D4)) {
        postDadosJson(mensagem, 6);
      }
    } else {
      Serial.println("Mensagem inválida!");
    }
  }
}

// Se não tiver conectado faz a conexão chamando a funçao de reconectar.
void acionar(float temp) {
  if (!mqtt.connected()) {
    reconectar();
  }
}

// Fazendo a conexão caso o BROKER tenha se perdido
void reconectar() {
  //cria um cliente ID único para o dispositivo usando o ID do chip
  String clientId = "SENAI927-";
  //Converte o ID numérico para String
  clientId += String(ESP.getChipId());
  while (!mqtt.connected()) {
    Serial.println("Testando conexão MQTT...");
    if (mqtt.connect(clientId.c_str())) {  //nn pode usar string pq pede char
      Serial.println("conectado!");
      mqtt.subscribe(topico_convencional);
      mqtt.subscribe(topico_pivo_central);
      mqtt.subscribe(topico_autopropelido);
      mqtt.subscribe(topico_lateral_movel);
      mqtt.subscribe(topico_gotejamento);
      mqtt.subscribe(topico_microaspersao);
    } else {
      Serial.println("MQTT desconectado!");
      delay(1000);
    }
  }
}

// Feita a configurando da conexão Serial do wemos.
void configSerial() {
  Serial.begin(9600);
  delay(10);
}

// Efetua a configuração da conexão Wi-fi.
void configWifi() {
  WiFi.begin("IOT", "iotsenai927");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("Conectado!");
  Serial.print(WiFi.SSID());
}

// Efetua a configuração do BROKER MQTT.
void configMQTT() {
  mqtt.setServer("broker.hivemq.com", 1883);
  mqtt.subscribe(topico_convencional);
  mqtt.subscribe(topico_pivo_central);
  mqtt.subscribe(topico_autopropelido);
  mqtt.subscribe(topico_lateral_movel);
  mqtt.subscribe(topico_gotejamento);
  mqtt.subscribe(topico_microaspersao);
  mqtt.setCallback(callback);
}

void configPinos() {
  pinMode(D13, OUTPUT);
  pinMode(D12, OUTPUT);
  pinMode(D11, OUTPUT);
  pinMode(D10, OUTPUT);
  pinMode(D9, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(A0, INPUT);
}
void timer() {
  long int tempoAtual = millis();

  if (tempoAtual - tempoAntigo > 1000) {

    tempoAntigo = millis();
    contador++;
  }
  return contador;
}
void temperatura() {
  // pede para o sensor fazer a leitura
  sensor.requestTemperatures();

  //busca o valor da temperatura em C
  float temperaturaC = sensor.getTempCByIndex(0);

  //exibindo as informações na serial
  if (contador == 60) {
    contador = 0;
    Serial.println("Temperatura: ");
    Serial.println(temperaturaC);
    Serial.println("°C");
  }
}

void sensorUmidade() {
  int sensorUmidade = analogRead(A0);
  if (contador == 60) {
    contador = 0;
    if (sensorUmidade > 900) {
      digitalWrite(D13, 1);
      digitalWrite(D12, 0);
      digitalWrite(D11, 0);
    } else if (sensorUmidade <= 900 && sensorUmidade >= 500) {
      digitalWrite(D13, 0);
      digitalWrite(D12, 1);
      digitalWrite(D11, 0);
    } else {
      digitalWrite(D13, 0);
      digitalWrite(D12, 0);
      digitalWrite(D11, 1);
    }
    Serial.println(sensorUmidade);
  }
}

// Configurar o dispositivo Arduino.
// Executada uma unica vez quando o dispositivo é ligado.
void setup() {
  configSerial();
  configWifi();
  configMQTT();
  configPinos();
  contador();
  sensor.begin();
}
void loop() {
  if (!mqtt.connected()) {
    reconectar();
  }
  mqtt.loop();
}