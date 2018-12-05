//ANEXO D – Código C++ para Conexão WiFi com Display
// Incluímos as bibliotecas
#include <ESP8266WiFi.h>
#include <LiquidCrystal_I2C.h>
//Declaramos as variáveis globais
const char* ssid = "WIFI"; //Configurar aqui o SSID da rede WiFi
const char* senha = "senha"; //Configurar aqui a Senha para acesso à rede
// setamos os pinos do NodeMcu D1 e D2 para o display lcd
//FUNCÃO DO TIPO "LiquidCrystal_I2C"
LiquidCrystal_I2C lcd(0x3F, 16, 2);
void setup() //Configuração inicial do dispositivo
{
  lcd.init(); // INICIALIZA O DISPLAY LCD
  lcd.backlight(); // HABILITA O BACKLIGHT (LUZ DE FUNDO)
  lcd.setCursor(0, 0);
  lcd.print("Conectando");// Iniciar ligação à rede
  lcd.setCursor(0, 1);
  lcd.print(ssid);
  WiFi.begin(ssid, senha);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    lcd.print(".");
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Conectado");
  lcd.setCursor(0, 1);
  lcd.print("IP:");
  lcd.print(WiFi.localIP());
}
void loop() {
}
