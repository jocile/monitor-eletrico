//ANEXO A – Código C++ do Monitor
//Programa o NodeMCU como medidor de corrente com saída serial
#include <EmonLib.h> // Incluímos a biblioteca
//Declaramos as variáveis globais
EnergyMonitor emon1; // Criamos uma instancia da classe
int rede; // Tensão da rede elétrica (127V OU 220V)
int potencia; // Potência instantânea
float fundoEscala; //Definimos a medição mínima
float Irms;
//Variável para guardar o cálculo da corrente RMS
//Protótipos onde são declaradas as funções
void SerialConsumoMinimo(void);
void SerialConsumoEletrico(void);
//Implementação das funções
void SerialConsumoMinimo(void)
{ // SECÃO PARA DEBUG VIA MONITOR SERIAL DA IDE ARDUINO
  Serial.print("Consumo Inferior");
  Serial.print(" a 20mA ");
  Serial.print(Irms); // Irms
  // Informamos que chegamos ao fundo de nossa escala
}
void SerialConsumoEletrico(void)
{ // Visusalização do Sensor via Monitor Serial
  potencia = Irms * rede;// Calcula o valor da Potencia Instantânea
  Serial.print("Corrente = ");
  Serial.print(Irms);
  Serial.println(" A");
  Serial.print("Potencia = ");
  Serial.print(potencia);
  Serial.println(" W");
  delay(500);
  Serial.print(".");
  delay(500);
  Serial.print(".");
  delay(500);
  Serial.println(".");
  delay(500);
}
void setup() //Configuração inicial do dispositivo
{
  Serial.begin(9600); // Utilizamos o monitor serial em caso de debug
  rede = 220.0;
  fundoEscala = 0.020;
  //Define a entrada analógica A0 para o Sensor e um valor para calibragem:
  emon1.current((analogRead(0)), 18);
}
void loop() //Função executada continuamente
{
  Irms = emon1.calcIrms(1480); //Calcula o valor no sensor
  if (Irms <= fundoEscala) { //E Compara ao valor mínimo
    Irms = 0;
    SerialConsumoMinimo();//Se menor informamos o consumo mínimo
  } else { //Senão informamos o valor do consumo elétrico registrado
    SerialConsumoEletrico();
  }
}
