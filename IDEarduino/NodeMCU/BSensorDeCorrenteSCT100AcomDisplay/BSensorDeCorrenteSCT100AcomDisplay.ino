//ANEXO B – Código C++ do Monitor com Display
// //Programa o NodeMCU como medidor de corrente com saída por Display
// Incluímos as bibliotecas
#include <EmonLib.h>
#include <LiquidCrystal_I2C.h>
//Declaramos as variáveis globais
EnergyMonitor emon1; // Criamos uma instancia da classe
int rede; // Tensão da rede elétrica (127V OU 220V)
int potencia; // Potência instantânea
float fundoEscala; //Definimos a medição mínima
float Irms;
//Variável para guardar o cálculo da corrente RMS
// Definimos as portas Digitais D1 e D2 do NodeMcu para o display
//FUNCÃO DO TIPO "LiquidCrystal_I2C"
LiquidCrystal_I2C lcd(0x3F, 16, 2);
//Protótipos
void DisplayConsumoMinimo(void);
void DisplayConsumoEletrico(void);
//Implementação
void DisplayConsumoMinimo(void) {
  // Informamos por Display que chegamos ao fundo de nossa escala
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Consumo Inferior");
  lcd.setCursor(0, 1);
  lcd.print("|>> a 20mA <<|");
}
void DisplayConsumoEletrico(void)
{
  lcd.clear();// Limpamos o Display LCD
  // Setamos os Cursores e Valores Iniciais do Display
  lcd.setCursor(0, 0); // (Linha 1 e Linha 2 das 16 Colunas)
  lcd.print("A:");
  lcd.print(Irms, 3);//Mostramos o valor da corrente no Display
  //O Argumento "3" é limitador do numero de casas decimais a serem mostradas
  // Calcula e mostra o valor da potencia em Volt-Amperes (VA)
  lcd.setCursor(8, 0);
  lcd.print(" VA:");
  lcd.print(Irms * rede, 1);
  // O Argumento "1" é limitador do numero de casas decimais
  // Setamos os Cursores e Valores Iniciais do Display
  lcd.setCursor(0, 1);
  // (Linha 1 e Linha 2 das 16 Colunas)
  // Mostramos o valor da Potencia (W) no Display LCD
  lcd.print("W:");
  // já considerando o FP informado de 0.92 para correção
  lcd.print((Irms * rede) * 0.92, 1);
  // O Argumento "1" é limitador do numero de casas
  // decimais a serem mostradas.
  // Mostramos o Fator de Potência sendo considerado neste código
  lcd.setCursor(8, 1);
  lcd.print(" FP:0.92");
  delay(50); // Atualiza o display de 50 em 50ms!
}
void setup() //Configuração inicial do dispositivo
{
  rede = 220.0;
  fundoEscala = 0.020;
  //Define a entrada analógica A0 para o Sensor e um valor para calibragem:
  emon1.current((analogRead(0)), 18);
  lcd.init(); // INICIALIZA O DISPLAY LCD
  lcd.backlight(); // HABILITA O BACKLIGHT (LUZ DE FUNDO)
}
void loop() //Função executada continuamente
{ // Calcula o valor no sensor
  float Irms = emon1.calcIrms(1480);
  if (Irms <= fundoEscala) //E Compara ao valor mínimo
  {
    Irms = 0;
    DisplayConsumoMinimo();//Se menor informamos o consumo mínimo
  } else //Senão informamos o valor do consumo elétrico registrado
  {
    DisplayConsumoEletrico();
  }
}
