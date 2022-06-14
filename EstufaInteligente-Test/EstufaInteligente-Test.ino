//Gabriel Kleiman
int horaAnterior, minutoAnterior, segundoAnterior, hora, minuto, segundo, horaLigar = 6;

//Variaveis referentes ao tempo
float temperatura1, temperatura2, AnteriorTemperatura1, AnteriorTemperatura2;

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
int lampadaAquecimento2 = 13;
int ventoinha1 = 0;
int ventoinha2 = 2;

//Variaveis do estado anterior Equipamentos ligados ao relé
int AnteriorBombaCirculacao1 = 0;
int AnteriorBombaCirculacao2 = 0;
int AnteriorBombaNutrientes1 = 0;
int AnteriorBombaNutrientes2 = 0;
int AnteriorLampadaCultivo1 = 0;
int AnteriorLampadaCultivo2 = 0;
int AnteriorLampadaAquecimento1 = 0;
int AnteriorLampadaAquecimento2 = 0;
int AnteriorVentoinha1 = 0;
int AnteriorVentoinha2 = 0;

//Sensores
int sensorNivelDeAgua1 = 6;
int sensorNivelDeAgua2 = 7;
int sensorDeTurbidez1 = A0;
int sensorDeTurbidez2 = A3;
int leituraSensorDeTurbidez1, leituraSensorDeTurbidez2;

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
	//Registro do primeiro valor das temperaturas
	temperatura1 = 25;
	temperatura2 = 25;
	AnteriorTemperatura1 = temperatura1;
	AnteriorTemperatura2 = temperatura2;
	
	//Leitura inicial do nivel de água
	leituraSensorNivelDeAgua1 = 1;
	leituraSensorNivelDeAgua2 = 1;
	
	//Leitura inicial sensores de turbidez
	leituraSensorDeTurbidez1 = 1000;
	leituraSensorDeTurbidez2 = 1000;
	
	//Leitura dos tempos iniciais
	horaAnterior = 0;
	hora = 5;
	minutoAnterior = 0;
	minuto = 15;
	segundoAnterior = 0;
	segundo = 23;
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

void ligarLampadaAquecimento1(){
	if(not AnteriorLampadaAquecimento1){
		AnteriorLampadaAquecimento1 = 1;
		digitalWrite(lampadaAquecimento1, HIGH);
		Serial.println("Lampada de aquecimento 1 ligada.");
	}
}

void desligarLampadaAquecimento1(){
	if(AnteriorLampadaAquecimento1){
		AnteriorLampadaAquecimento1 = 0;
		digitalWrite(lampadaAquecimento1, LOW);
		Serial.println("Lampada de aquecimento 1 desligada.");
	}
}

void ligarLampadaAquecimento2(){
	if(not AnteriorLampadaAquecimento2){
		AnteriorLampadaAquecimento2 = 1;
		digitalWrite(lampadaAquecimento2, HIGH);
		Serial.println("Lampada de aquecimento 2 ligada.");
	}
}

void desligarLampadaAquecimento2(){
	if(AnteriorLampadaAquecimento2){
		AnteriorLampadaAquecimento2 = 0;
		digitalWrite(lampadaAquecimento2, LOW);
		Serial.println("Lampada de aquecimento 2 desligada.");
	}
}

void desligarBombaNutrientes1(){
	if(AnteriorBombaNutrientes1){
		AnteriorBombaNutrientes1 = 0;
		digitalWrite(bombaNutrientes1, LOW);
		Serial.println("Bomba de nutrientes 1 desligada.");
	}
}

void ligarBombaNutrientes1(){
	if(not AnteriorBombaNutrientes1){
		AnteriorBombaNutrientes1 = 1;
		digitalWrite(bombaNutrientes1, HIGH);
		Serial.println("Bomba de nutrientes 1 ligada.");
	}
}

void desligarBombaNutrientes2(){
	if(AnteriorBombaNutrientes2){
		AnteriorBombaNutrientes2 = 0;
		digitalWrite(bombaNutrientes2, LOW);
		Serial.println("Bomba de nutrientes 2 desligada.");
	}
}

void ligarBombaNutrientes2(){
	if(not AnteriorBombaNutrientes2){
		AnteriorBombaNutrientes2 = 1;
		digitalWrite(bombaNutrientes2, HIGH);
		Serial.println("Bomba de nutrientes 2 ligada.");
	}
}

void desligarVentoinha1(){
	if(AnteriorVentoinha1){
		AnteriorVentoinha1 = 0;
		digitalWrite(ventoinha1, LOW);
		Serial.println("Ventoinha 1 desligada.");
	}
}

void ligarVentoinha1(){
	if(not AnteriorVentoinha1){
		AnteriorVentoinha1 = 1;
		digitalWrite(ventoinha1, HIGH);
		Serial.println("Ventoinha 1 ligada.");
	}
}

void desligarVentoinha2(){
	if(AnteriorVentoinha2){
		AnteriorVentoinha2 = 0;
		digitalWrite(ventoinha2, LOW);
		Serial.println("Ventoinha 2 desligada.");
	}
}

void ligarVentoinha2(){
	if(not AnteriorVentoinha2){
		AnteriorVentoinha2 = 1;
		digitalWrite(ventoinha2, HIGH);
		Serial.println("Ventoinha 2 ligada.");
	}
}

void alterarSinalEntrada(){
	if(Serial.available() > 0){
		Serial.println("\n1- Nivel de agua 1\n2-Nivel de agua 2\n3- Temperatura1\n4 - Temperatura2\n5 - Turbidez 1\n6- Turbidez 2\n7- Hora \n8- Minuto \nDigite o sinal que deseja alterar: ");
		delay(100);
		int opt = Serial.parseInt();
		if(opt != 0){
			Serial.println(opt);
			if(opt == 1){
				//Sensor de nivel de agua 1
				leituraSensorNivelDeAgua1 = !leituraSensorNivelDeAgua1;
				Serial.print("Sensor de nivel de agua 1 alterado para ");
				Serial.println(leituraSensorNivelDeAgua1);
			} else if(opt == 2){
				//Sensor de nivel de agua 2
				leituraSensorNivelDeAgua2 = !leituraSensorNivelDeAgua2;
				Serial.print("Sensor de nivel de agua 2 alterado para ");
				Serial.println(leituraSensorNivelDeAgua2);
			} else if(opt == 3){
				if(temperatura1 > 23){
					temperatura1 = 20;
				} else {
					temperatura1 = 25;
				}
				Serial.print("Temperatura1 alterado para ");
				Serial.println(temperatura1);
			} else if(opt == 4){
				if(temperatura2 > 23){
					temperatura2 = 20;
				} else {
					temperatura2 = 25;
				}
				Serial.print("Temperatura2 alterado para ");
				Serial.println(temperatura2);
			} else if(opt == 5){
				if(leituraSensorDeTurbidez1 > 710){
					leituraSensorDeTurbidez1 = 500;
				} else {
					leituraSensorDeTurbidez1 = 1000;
				}
				Serial.print("Turbidez 1 alterado para ");
				Serial.println(leituraSensorDeTurbidez1);
			} else if(opt == 6){
				if(leituraSensorDeTurbidez2 > 900){
					leituraSensorDeTurbidez2 = 500;
				} else {
					leituraSensorDeTurbidez2 = 1000;
				}
				Serial.print("Turbidez 2 alterado para ");
				Serial.println(leituraSensorDeTurbidez2);
			} else if(opt == 7){
				/*
				if(hora > 6){
					hora = 0;
				} else {
					hora = 7;
				}*/
				hora = hora + 1;
				if(hora >= 24){
					hora = 0;
				}
				Serial.print("Hora definida para ");
				Serial.println(hora);
			} else if(opt == 8){
				/*
				if(minuto > 20){
					minuto = 15;
				} else {
					minuto = 45;
				}*/
				minuto = minuto + 15;
				if(minuto >= 60){
					minuto = 0;
				}
				Serial.print("Minuto definido para ");
				Serial.println(minuto);
			}
		}
	}
}

void loop(){
	//Definição de sinais de entrada
	alterarSinalEntrada();
	//Trecho de código que só vai funcionar entre 6:00am e 23:59pm
	if(hora >= 6){
		//Liga as lampadas led de cultivo
		if(horaAnterior < 6){
			ligarLampadasDeCultivo();
		}
		
		//Liga as bombas de água por 30 minutos a cada 1h
		if(hora == horaLigar){
			if(minuto <= 20){
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
					ligarBombaCirculacao2();
					desligarLedNivelDeAgua2();
				}
				//Acende as LEDs de sinalização de baixo nível de água se a leitura do nivel for baixa
				else{
					desligarBombaCirculacao2();
					ligarLedNivelDeAgua2();
				}
			}else if(hora == horaLigar){
				horaLigar = horaLigar + 3;
				if(horaLigar > 18){
					horaLigar = 6;
				}
				Serial.print("\nPróximo horário para ligar será às ");
				Serial.print(horaLigar);
				Serial.println("h.\n");
				
			}
			if(minuto > 20){
				desligarBombaCirculacao1();
				desligarBombaCirculacao2();
			}
		}
		//Apaga as LEDs de sinalização de baixo nível de água se a leitura do nivel for alto
		if(leituraSensorNivelDeAgua1){
			desligarLedNivelDeAgua1();
		} else {
			ligarLedNivelDeAgua1();
		}
		if(leituraSensorNivelDeAgua2){
			desligarLedNivelDeAgua2();
		} else {
			ligarLedNivelDeAgua2();
		}
	} else {
		//Desliga as lampadas led de cultivo quando estiver de noite
		desligarLampadasDeCultivo();
	}
	//Executar ações com variação da temperatura
	if(not isnan(temperatura1) and not isnan(temperatura2)){
		if(temperatura1 < 23){
			ligarLampadaAquecimento1();
			desligarVentoinha1();
		} else {
			desligarLampadaAquecimento1();
			ligarVentoinha1();
		}
		if(temperatura2 < 23){
			ligarLampadaAquecimento2();
			desligarVentoinha2();
			
		} else {
			desligarLampadaAquecimento2();
			ligarVentoinha2();
		}
	}
	
	//Leitura dos sensores de turbidez
	if(leituraSensorDeTurbidez1 > 712){
		ligarBombaNutrientes1();
	} else {
		desligarBombaNutrientes1();
	}
	if(leituraSensorDeTurbidez2 > 910){
		ligarBombaNutrientes2();
	} else {
		desligarBombaNutrientes2();
	}
	horaAnterior = hora;
	minutoAnterior = minuto;
	segundoAnterior = segundo;
	AnteriorTemperatura1 = temperatura1;
	AnteriorTemperatura2 = temperatura2;
	delay(100);
	//Turbidez na agua 700, na solução 712
}
//711^712 agua de mesa tratada com nutriente
//711^721 agua de torneira com nutrientes
//715^717^726 agua sistema exterior
//715^716 água torneira

//Sensor turb 2 : 910~912 água pura / 906~908 com nutriente novo 

//20 minutos a cada 3 horas entre 6h e 18h
