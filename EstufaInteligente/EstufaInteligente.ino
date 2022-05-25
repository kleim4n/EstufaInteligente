//Adicionar sensor de temperatura ligando lampada de aquecimento

#include <DS3231.h>

//PORTA DO MODULO DE RELOGIO: SDA é A4 e SCL é A5
DS3231 rtc(SDA, SCL);
Time t;
int horaAnterior, minutoAnterior, segundoAnterior;

//Trecho de inicialização do sensor de umidade e temperatura
#include "DHT.h"
#define DHTPIN1 A1 // pino que estamos conectado
#define DHTPIN2 A3
#define DHTTYPE DHT11 // DHT 11
// Conecte pino 1 do sensor (esquerda) ao +5V
// Conecte pino 2 do sensor ao pino de dados definido em seu Arduino
// Conecte pino 4 do sensor ao GND
// Conecte o resistor de 10K entre pin 2 (dados) 
// e ao pino 1 (VCC) do sensor
DHT dht1(DHTPIN1, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);

//Portas digitais com LED
int ledNivelDeAgua1 = 3;
int ledNivelDeAgua2 = 5;
int ledNutrientes1 = 2;
int ledNutrientes2 = 0;
//Variaveis do estado anterior Portas digitais com LED
int AnteriorLedNivelDeAgua1 = 0;
int AnteriorLedNivelDeAgua2 = 0;
int AnteriorLedNutrientes1 = 0;
int AnteriorLedNutrientes2 = 0;

//Equipamentos ligados ao relé
int bombaCirculacao1 = 11;
int bombaCirculacao2 = 12;
int bombaNutrientes1 = 6;
int bombaNutrientes2 = 7;
int lampadaCultivo1 = 8;
int lampadaCultivo2 = 9;
int lampadaAquecimento1 = 10;
int lampadaAquecimento2 = 11;
//Variaveis do estado anterior Equipamentos ligados ao relé
int AnteriorBombaCirculacao1 = 0;
int AnteriorBombaCirculacao2 = 0;
int AnteriorBombaNutrientes1 = 0;
int AnteriorBombaNutrientes2 = 0;
int AnteriorLampadaCultivo1 = 0;
int AnteriorLampadaCultivo2 = 0;
int AnteriorLampadaAquecimento1 = 0;
int AnteriorLampadaAquecimento2 = 0;

//Sensores
int sensorNivelDeAgua1 = 6;
int sensorNivelDeAgua2 = 7;
int sensorDeTurbidez1 = A0;
int sensorDeTurbidez2 = A1;

//Valores da leitura dos sensores
bool leituraSensorNivelDeAgua1, leituraSensorNivelDeAgua2;

void setup(){
	/*
	pinMode(ledNivelDeAgua1, OUTPUT);
	pinMode(ledNivelDeAgua2, OUTPUT);
	pinMode(ledNutrientes1, OUTPUT);
	pinMode(ledNutrientes2, OUTPUT);
	pinMode(bombaCirculacao1, OUTPUT);
	pinMode(bombaCirculacao2, OUTPUT);
	pinMode(bombaNutrientes1, OUTPUT);
	pinMode(bombaNutrientes2, OUTPUT);
	pinMode(lampadaCultivo1, OUTPUT);
	pinMode(lampadaCultivo2, OUTPUT);
	pinMode(lampadaAquecimento1, OUTPUT);
	pinMode(lampadaAquecimento2, OUTPUT);
	*/
	Serial.begin(9600); //Deve selecionar esta frequência de comunicação no monitor serial (lupa)
	rtc.begin();
	//dht1.begin();
	//dht2.begin();
	
	//Leitura inicial do nivel de água
	leituraSensorNivelDeAgua1 = digitalRead(sensorNivelDeAgua1);
	leituraSensorNivelDeAgua2 = digitalRead(sensorNivelDeAgua2);
	
	//Leitura dos tempos iniciais
	horaAnterior = 0;
	minutoAnterior = 0;
	segundoAnterior = 0;
}

bool verificarHora(){
	if(t.hour > 6){
		if(horaAnterior <= 6){
			Serial.println("HORA true: PASSOU DAS 6H");
			return true;
		}
	} else {
		Serial.println("HORA false: ENTRE 0H E 6H");
		return false;
	}
}

bool verificarMinuto(){
	if(t.min <= 20){
		if(minutoAnterior > 20){
			Serial.println("MINUTO true: ENTRE 0 E 20 MINUTOS");
			return true;
		}
	} else {
		Serial.println("MINUTO false: ESTAMOS NOS ENTRE 21 E 60 MINUTOS");
		return false;
	}
}

bool verificarSegundo(){
	if(t.sec % 5 == 0){
		if(segundoAnterior % 5 != 0){
			Serial.println("SEGUNDOS true: ");
			return true;
		}
	} else {
		return false;
	}
}

//Função para ligar as lampadas de cultivo
void ligarLampadasDeCultivo(){
	if(not AnteriorLampadaCultivo1){
		AnteriorLampadaCultivo1 = 1;
		digitalWrite(lampadaCultivo1, HIGH);
		Serial.println("Lampada de cultivo 1 ligada.");
	}
	if(not AnteriorLampadaCultivo2){
		AnteriorLampadaCultivo2 = 1;
		digitalWrite(lampadaCultivo2, HIGH);
		Serial.println("Lampada de cultivo 2 ligada.");
	}
}
		
void desligarLampadasDeCultivo(){
	if(AnteriorLampadaCultivo1){
		AnteriorLampadaCultivo1 = 0;
		digitalWrite(lampadaCultivo1, LOW);
		Serial.println("Lampada de cultivo 1 desligada.");
	}
	if(AnteriorLampadaCultivo2){
		AnteriorLampadaCultivo2 = 0;
		digitalWrite(lampadaCultivo2, LOW);
		Serial.println("Lampada de cultivo 2 desligada.");
	}
}

void ligarBombaCirculacao1(){
	if(not AnteriorBombaCirculacao1){
		AnteriorBombaCirculacao1 = 1;
		digitalWrite(bombaCirculacao1, HIGH);
		Serial.println("Bomba de circulação 1 ligada.");
	}
}

void ligarBombaCirculacao2(){
	if(not AnteriorBombaCirculacao2){
		AnteriorBombaCirculacao2 = 1;
		digitalWrite(bombaCirculacao2, HIGH);
		Serial.println("Bomba de circulação 2 ligada.");
	}
}

void desligarBombaCirculacao1(){
	if(AnteriorBombaCirculacao1){
		AnteriorBombaCirculacao1 = 0;
		digitalWrite(bombaCirculacao1, LOW);
		Serial.println("Bomba de circulação 1 desligada.");
	}
}

void desligarBombaCirculacao2(){
	if(AnteriorBombaCirculacao2){
		AnteriorBombaCirculacao2 = 0;
		digitalWrite(bombaCirculacao2, LOW);
		Serial.println("Bomba de circulação 2 desligada.");
	}
}

void ligarLedNivelDeAgua1(){
	if(not AnteriorLedNivelDeAgua1){
		AnteriorLedNivelDeAgua1 = 1;
		digitalWrite(ledNivelDeAgua1, HIGH);
		Serial.println("Led nivel de agua 1 ligada.");
	}
}

void desligarLedNivelDeAgua1(){
	if(AnteriorLedNivelDeAgua1){
		AnteriorLedNivelDeAgua1 = 0;
		digitalWrite(ledNivelDeAgua1, LOW);
		Serial.println("Led nivel de agua 1 desligada.");
	}
}

void ligarLedNivelDeAgua2(){
	if(not AnteriorLedNivelDeAgua2){
		AnteriorLedNivelDeAgua2 = 1;
		digitalWrite(ledNivelDeAgua2, HIGH);
		Serial.println("Led nivel de agua 2 ligada.");
	}
}

void desligarLedNivelDeAgua2(){
	if(AnteriorLedNivelDeAgua2){
		AnteriorLedNivelDeAgua2 = 0;
		digitalWrite(ledNivelDeAgua2, LOW);
		Serial.println("Led nivel de agua 2 desligada.");
	}
}

void loop(){
	//Condições referentes ao horario
	t = rtc.getTime();
	//Trecho de código que só vai funcionar entre 6:00am e 23:59pm
	if(t.hour >= 6){
		//Liga as lampadas led de cultivo
		if(horaAnterior < 6){
			ligarLampadasDeCultivo();
		}
		
		//Liga as bombas de água por 30 minutos a cada 1h
		if(t.sec % 5 == 0 and segundoAnterior % 5 != 0){
			//Verifica se o nivel da água estava OK antes de ligar a bombaCirculacao1
			if(leituraSensorNivelDeAgua1){
				ligarBombaCirculacao1();
				desligarLedNivelDeAgua1();
			}
			//Acende as LEDs de sinalização de baixo nível de água se a leitura do nivel for baixa
			else{
				desligarBombaCirculacao1();
				ligarLedNivelDeAgua1();
			}
			//Verifica se o nivel da água estava OK antes de ligar a bombaCirculacao2
			if(leituraSensorNivelDeAgua2){
				ligarBombaCirculacao1();
				desligarLedNivelDeAgua1();
			}
			//Acende as LEDs de sinalização de baixo nível de água se a leitura do nivel for baixa
			else{
				desligarBombaCirculacao1();
				ligarLedNivelDeAgua1();
			}
		}
		//Realiza a leitura do nível de água enquanto a bomba de água estiver desligada
		leituraSensorNivelDeAgua1 = digitalRead(sensorNivelDeAgua1);
		leituraSensorNivelDeAgua2 = digitalRead(sensorNivelDeAgua2);
		//Apaga as LEDs de sinalização de baixo nível de água se a leitura do nivel for alto
		if(leituraSensorNivelDeAgua1){
			Serial.println("Nivel de agua 1 ALTO.");
			desligarLedNivelDeAgua1();
		} else {
			Serial.println("Nivel de agua 1 BAIXO.");
			ligarLedNivelDeAgua1();
		}
		if(leituraSensorNivelDeAgua2){
			Serial.println("Nivel de agua 2 ALTO.");
			desligarLedNivelDeAgua2();
		} else {
			Serial.println("Nivel de agua 2 BAIXO.");
			ligarLedNivelDeAgua2();
		}
	} else {
		//Desliga as lampadas led de cultivo quando estiver de noite
		desligarLampadasDeCultivo();
	}
	horaAnterior = t.hour;
	minutoAnterior = t.min;
	segundoAnterior = t.sec;
	delay(500);
}