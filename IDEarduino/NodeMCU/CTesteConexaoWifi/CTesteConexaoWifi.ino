//ANEXO C – Código C++ para Conexão à Rede WiFi
#include <ESP8266WiFi.h>
//Conecta no WiFi (COLOQUE O NOME E SENHA DA SUA REDE!).
const char* ssid = "WIFI";
const char* password = "senha";
int wifiStatus;
void setup() {
Serial.begin(9600);
delay(200);
// Iniciar ligação à rede
Serial.println();
Serial.println();
Serial.print("A ligar à rede ");
Serial.println(ssid);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
}
void loop() {
wifiStatus = WiFi.status();
if(wifiStatus == WL_CONNECTED){
Serial.println("");
Serial.println("O seu nodeMCU está ligado!");
Serial.print("Endereço IP: ");
Serial.println(WiFi.localIP());
}
else{
Serial.println("");
Serial.println("Upsss...o seu nodeMCU não se consegue ligar...");
}
delay(1000);
}
