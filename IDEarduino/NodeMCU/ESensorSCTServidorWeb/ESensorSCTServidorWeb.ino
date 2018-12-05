//ANEXO E – Código C++ do Medidor como Servidor Web
//https://portal.vidadesilicio.com.br/servidor-web-esp/
#include <ESP8266WiFi.h>//Biblioteca que gerencia o WiFi.
#include <WiFiServer.h>//Biblioteca que gerencia o uso do TCP.
#include <EmonLib.h>
WiFiServer servidor(80);//Cria um objeto "servidor" na porta 80 (http).
WiFiClient cliente;//Cria um objeto "cliente".
EnergyMonitor emon1;
int rede = 220.0;
float fundoEscala = 0.020;
String html;//String que armazena o corpo do site.
void setup()
{
  Serial.begin(9600);//Inicia comunicaçao Serial.
  Serial.print("A ligar à rede ");
  Serial.println("JocileWIFI");
  WiFi.mode(WIFI_STA);//Habilita o modo STATION.
  //Conecta no WiFi (COLOQUE O NOME E SENHA DA SUA REDE!).
  WiFi.begin("WIFI", "SENHA");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("O seu nodeMCU está ligado!");
  Serial.print("Endereço IP: ");
  //Printa o IP que foi consebido ao ESP8266 (este ip que voce ira acessar).
  Serial.println(WiFi.localIP());
  servidor.begin();//Inicia o Servidor.
  pinMode(D4, OUTPUT);//Define o LED_BUILTIN como Saida.
  emon1.current((analogRead(0)), 11);
}
void loop()
{
  float Irms = emon1.calcIrms(1480);
  // Para testes podemos usar um valor aleatório: float Irms = random(1,20);
  cliente = servidor.available();//Diz ao cliente que há um servidor disponivel.
  if (cliente == true)//Se houver clientes conectados, ira enviar o HTML.
  {
    String req = cliente.readStringUntil('\r');//Faz a leitura do Cliente.
    Serial.println(req);//Printa o pedido no Serial monitor.
    if (req.indexOf("/Atualizar") > -1)//Caso o pedido houver led, inverter o seu estado.
    {
      digitalWrite(D4, !digitalRead(D4));//Inverte o estado do led.
    }
    html = "";//Reseta a string.
    html += "HTTP/1.1 Content-Type: text/html\n\n";//Identificaçao do HTML.
    html += "<!DOCTYPE html><html><head><title>ESP8266 WEB</title>";//Identificaçao e Titulo.
    html += "<meta name='viewport' content='user-scalable=no'>";//Desabilita o Zoom.
    html += "<style>h1{font-size:2vw;color:black;}</style></head>";//Cria uma nova fonte de tamanho e cor X.
    html += "<body bgcolor='ffffff'><center><h1>";//Cor do Background
    html += "<form action='/Atualizar' method='get'>";//Cria um botao GET para o link
    html += "<input type='submit' value='Atualizar' id='frm1_submit'/></form>";
    html += "</h1><p></p>";
    html += "<p>Consumo Eletrico: Corrente ";
    html += String(Irms, 3);
    html += " A; Potencia: ";
    html += String(Irms * rede, 1);
    html += " VA; ";
    html += String((Irms * rede) * 0.92, 1);
    html += " W; ";
    html += " FP 0.92. </p>";
    html += "</center></body></html>";
    cliente.print(html);//Finalmente, enviamos o HTML para o cliente.
    cliente.stop();//Encerra a conexao.
  }
}
