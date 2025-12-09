// Faz a conexão do wemos com a rede WI-FI.
#include <ESP8266WiFi.h>
// Inscreve e publica nos topicos MQTT.
// Faz a conexão com o BROKER.
#include <PubSubClient.h>
// Faz o post de objetos JSON.
#include <ArduinoJson.h>
// Faz requisições HTTP
#include <ESP8266HTTPClient.h>
#include <string>

#include <OneWire.h>
#include <DallasTemperature.h>
#define PINO_SENSOR_TEMP D2

//pegando os binarios para entregar em temperaturas
OneWire barramento(PINO_SENSOR_TEMP);
DallasTemperature sensor(&barramento);
// Definição da URL da api.
const char* cadastrarEventos = "http://192.168.137.82:3002/cadastrarEventos";

unsigned long tempo = 0;
unsigned long auxiliar = 0;
unsigned long int contador = 0;
bool minuto = false;
bool hora = false;
long randNumber;

// Definição dos tópicos.
#define topico_convencional "safratech/convencional/irrigacao/campo1"
#define topico_pivo_central "safratech/pivocentral/irrigacao/campo1"
#define topico_autopropelido "safratech/autopropelido/irrigacao/campo1"
#define topico_lateral_movel "safratech/lateralmovel/irrigacao/campo1"
#define topico_gotejamento "safratech/gotejamento/irrigacao/campo1"
#define topico_microaspersao "safratech/microaspersao/irrigacao/campo1"
#define topico_sensor_temp "safratech/sensor/topico_sensor_temp/campo1"
#define topico_sensor_umidade "safratech/sensor/topico_sensor_umidade/campo1"

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

//Definição de porta de sensor

String string_topico_sensor_temp = "safratech/sensor/topico_sensor_temp/campo1";
String string_topico_sensor_umidade = "safratech/sensor/topico_sensor_umidade/campo1";

// Cria conexões com as bibliotecas WiFiClient e PubSubClient.
// Fazendo a instancia.
WiFiClient espClient;
// Nome do objeto e a classe.
PubSubClient mqtt(espClient);

// Enviar as mensagens para o back-end
bool postDadosJson(String informacao, const int id, unsigned int length) {
  String mensagem = "";
  for (int i = 0; i < length; i++) {
    mensagem += (char)informacao[i];
  }

  // montando o JSON
  StaticJsonDocument<200> doc;

  doc["informacao"] = mensagem;
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
  Serial.println(code);
  Serial.println(responsePayload);
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
        postDadosJson(mensagem, 1, mensagem.length());
      }
    } else if (mensagem == "off") {
      desliga_luz_convencional;
      if (!digitalRead(D13)) {
        postDadosJson(mensagem, 1, mensagem.length());
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
        postDadosJson(mensagem, 2, mensagem.length());
      }
    } else if (mensagem == "off") {
      desliga_luz_pivo_central;
      if (!digitalRead(D12)) {
        postDadosJson(mensagem, 2, mensagem.length());
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
        postDadosJson(mensagem, 3, mensagem.length());
      }
    } else if (mensagem == "off") {
      desliga_luz_autopropelido;
      if (!digitalRead(D11)) {
        postDadosJson(mensagem, 3, mensagem.length());
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
        postDadosJson(mensagem, 4, mensagem.length());
      }
    } else if (mensagem == "off") {
      desliga_luz_lateral_movel;
      if (!digitalRead(D10)) {
        postDadosJson(mensagem, 4, mensagem.length());
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
        postDadosJson(mensagem, 5, mensagem.length());
      }
    } else if (mensagem == "off") {
      desliga_luz_gotejamento;
      if (!digitalRead(D9)) {
        postDadosJson(mensagem, 5, mensagem.length());
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
        postDadosJson(mensagem, 6, mensagem.length());
      }
    } else if (mensagem == "off") {
      desliga_luz_microaspersao;
      if (!digitalRead(D4)) {
        postDadosJson(mensagem, 6, mensagem.length());
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
      mqtt.subscribe(topico_sensor_temp);
      mqtt.subscribe(topico_sensor_umidade);
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
  mqtt.subscribe(topico_sensor_temp);
  mqtt.subscribe(topico_sensor_umidade);
  mqtt.setCallback(callback);
}

void configPinos() {
  pinMode(D13, OUTPUT);
  pinMode(D12, OUTPUT);
  pinMode(D11, OUTPUT);
  pinMode(D10, OUTPUT);
  pinMode(D9, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(A0, INPUT);
}
void timer() {
  minuto = false;
  hora = false;
  // Serial.println(tempo);
  // Serial.println(auxiliar);

  // long int tempoAtual = millis();
  // bool tempoAtingido;

  // if (tempoAtual - tempoAntigo > 1000) {
  //   tempoAtingido = false;
  //   tempoAntigo = millis();
  //   contador++;
  // }
  // if (contador > 60) {
  //   contador = 0;
  //   tempoAntigo = true;
  //   return tempoAtingido;
  // }
  tempo = millis();
  if (tempo % 5000 == 0) {
    int valorNivelDagua = analogRead(A0);
    String valorNivelDaguaFormatado = String(valorNivelDagua);
    int valorTemp = random(18, 43);
    String valorTempFormatado = String(valorTemp);
    int valorLuminosidade = random(0,100000);
    String valorLuminosidadeFormatado = String(valorLuminosidade);
    int valorUmidAr = random(0,101);
    String valorUmidArFormatado = String(valorUmidAr);
    int valorCaixa1 = random(0,101);
    String valorCaixa1Formatado = String(valorCaixa1);
    int valorCaixa2 = random(0,101);
    String valorCaixa2Formatado = String(valorCaixa2);
    mqtt.publish("safratech/sensor/topico_sensor_umidade/campo1", valorNivelDaguaFormatado.c_str());
    mqtt.publish("safratech/sensor/topico_sensor_temperatura/campo1", valorTempFormatado.c_str());
    mqtt.publish("safratech/sensor/topico_sensor_luminosidade/campo1", valorLuminosidadeFormatado.c_str());
    mqtt.publish("safratech/sensor/topico_sensor_umidAr/campo1", valorUmidArFormatado.c_str());
    mqtt.publish("safratech/sensor/topico_sensor_caixa1/campo1", valorCaixa1Formatado.c_str());
    mqtt.publish("safratech/sensor/topico_sensor_caixa2/campo1", valorCaixa2Formatado.c_str());
  }
  if (tempo % 3600000 == 0) {
    int valorNivelDagua = analogRead(A0);
    String valorNivelDaguaFormatado = String(valorNivelDagua);
    int valorTemp = random(18, 43);
    String valorTempFormatado = String(valorTemp);
    int valorLuminosidade = random(0,100000);
    String valorLuminosidadeFormatado = String(valorLuminosidade);
    int valorUmidAr = random(0,101);
    String valorUmidArFormatado = String(valorUmidAr);
    int valorCaixa1 = random(0,101);
    String valorCaixa1Formatado = String(valorCaixa1);
    int valorCaixa2 = random(0,101);
    String valorCaixa2Formatado = String(valorCaixa2);
    postDadosJson(valorNivelDaguaFormatado, 8, valorNivelDaguaFormatado.length());
    postDadosJson(valorTempFormatado, 7, valorTempFormatado.length());
    postDadosJson(valorLuminosidadeFormatado, 10, valorLuminosidadeFormatado.length());
    postDadosJson(valorUmidArFormatado, 9, valorUmidArFormatado.length());
    postDadosJson(valorCaixa1Formatado, 11, valorCaixa1Formatado.length());
    postDadosJson(valorCaixa2Formatado, 12, valorCaixa2Formatado.length());
    auxiliar = tempo;
  }
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

// void nivelDagua() {

//   if (contador == 60) {
//     contador = 0;
//     if (nivelDagua > 900) {
//       digitalWrite(D13, 1);
//       digitalWrite(D12, 0);
//       digitalWrite(D11, 0);
//     } else if (nivelDagua <= 900 && nivelDagua >= 500) {
//       digitalWrite(D13, 0);
//       digitalWrite(D12, 1);
//       digitalWrite(D11, 0);
//     } else {
//       digitalWrite(D13, 0);
//       digitalWrite(D12, 0);
//       digitalWrite(D11, 1);
//     }
//     Serial.println(nivelDagua);
//   }
// }

// Configurar o dispositivo Arduino.
// Executada uma unica vez quando o dispositivo é ligado.
void setup() {
  configSerial();
  configWifi();
  configMQTT();
  configPinos();
  sensor.begin();
}
void loop() {
  if (!mqtt.connected()) {
    reconectar();
  }
  timer();
  mqtt.loop();
}