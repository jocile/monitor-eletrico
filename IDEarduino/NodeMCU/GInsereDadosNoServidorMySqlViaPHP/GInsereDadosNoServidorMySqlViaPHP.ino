//ANEXO F - Código em PHP
//ANEXO G – Este Código C++ do Medidor com o Servidor Web Externo
//          Envia os dados via HTTP GET através de uma página em PHP
//Incluindo as bibliotecas necessárias
#include <ESP8266WiFi.h>
#include <EmonLib.h>
#include <WiFiClient.h>
//Declaramos as variáveis globais
const char* ssid = "SSID"; //Configurar aqui o SSID da rede WiFi
const char* senha = "SENHA"; //Configurar aqui a Senha para acesso à rede
// Site que receberá os dados - IMPORTANTE: SEM O HTTP://
const char* host = "jocile.000webhostapp.com";
const int httpPort = 80;
EnergyMonitor emon1; // Criamos uma instancia da classe
int rede; // Tensão da rede elétrica (127V OU 220V)
int potencia; // Potência instantânea
float fundoEscala; //Definimos a medição mínima
float Irms; //Variável para guardar o cálculo da corrente RMS
WiFiClient client;
//Protótipos
void WiFiConectaSerial(void);
//Implementação
void WiFiConectaSerial(void) // Função de Conexão à rede WiFi
{
  Serial.print("Conectando para a rede");
  Serial.print(ssid);
  WiFi.begin(ssid, senha);
  while (WiFi.status() != WL_CONNECTED) { //Testa a conexão
    delay(500);
    Serial.println(".");
  }
  Serial.println(" ");
  Serial.println("WiFi Conectado"); //Exibe no Monitor Serial o Status
  Serial.println(ssid);
  Serial.println("Endereço IP: ");
  Serial.println(WiFi.localIP());
}
void setup()
{
  Serial.begin(9600);//Inicia comunicaçao Serial.
  rede = 220.0;
  fundoEscala = 0.020;
  //Define a entrada analógica A0 para o Sensor e um valor para calibragem:
  emon1.current((analogRead(0)), 11);
  WiFiConectaSerial(); //Aqui executando a conexão verificada por serial
}
void loop()
{
  Irms = emon1.calcIrms(1480); //Calcula o valor no sensor
  // Criando uma conexao TCP
  if (!client.connect(host, httpPort)) {//Testa o envio dos dados
    Serial.println("Falha na conexao com o site ");
  }
  // Enviando para o host os dados:
  String param = (String("GET /sensor.php?irms=") + String(Irms, 3) +
                  " HTTP/1.1\r\n" + "Host: " + host + "\r\n" +
                  "Connection: close\r\n\r\n");
  client.print(param);
  Serial.println("Dados enviados: ");
  Serial.print(param);
  // Informações de retorno do servidor para debug
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  // Repetindo a cada 1 minuto
  delay(60000);
}
