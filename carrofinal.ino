#define b_mtr 2 //motor defu atras conectado al pin 2
#define r_mtr 3 //motor giro derecho conectado al pin 3
#define l_mtr 4 //motor giro izquierdo conectado al pin 4
#define m_mtr 5 //motor giro izquierdo conectado al pin 5
#define f_light 6 //led conectados al pin 6
//sensor1
int trigger = 8;
int echo = 7;
//sensor2
int trigger2 = 9;
int echo2 = 10;
//sensor3
int trigger3 = 11;
int echo3 = 12;

//cantidad de vueltas
int cantidadDeGiros = 0;

float distancia,tiempo, distancia2, tiempo2,distancia3,tiempo3;
bool cerca, cerca1, cerca2;
//fin sensores

char incomingByte = 0;
void setup(){
  pinMode(b_mtr,OUTPUT);
  pinMode(r_mtr,OUTPUT);
  pinMode(l_mtr,OUTPUT);
  pinMode(m_mtr,OUTPUT);
  pinMode(f_light,OUTPUT);
  //sensor
  pinMode(trigger,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(trigger2,OUTPUT);
  pinMode(echo2,INPUT);
  pinMode(trigger3,OUTPUT);
  pinMode(echo3,INPUT);
  //fin sensor
  Serial.begin(9600);
}

void loop() {
  cerca=false;
  cerca1=false;
  cerca2=false;

  //Algoritmo para el ultrasonido  
  digitalWrite(trigger,LOW);
  delayMicroseconds(2);
  digitalWrite(trigger,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger,LOW);
  tiempo=pulseIn(echo,HIGH);
  distancia=(tiempo/2)/29.1;
  Serial.print(distancia);
  Serial.print("cm");
  Serial.println();

//Si la distancia esta entre 10 y 50 cm los motores se apagan
    if ((distancia>=10) && (distancia<=50)){
        digitalWrite(b_mtr,LOW);
        digitalWrite(r_mtr,LOW);
        digitalWrite(l_mtr,LOW);
        digitalWrite(m_mtr,LOW);
        digitalWrite(f_light,HIGH);
        delay(1000);
        cerca=true;
        int direccion =0;
         //Elije la dirección para girar
        direccion == random(2);
        if (direccion==0) {
          incomingByte='a';}
        else {
          incomingByte='d';}        
      }  
      
  //Algoritmo para el ultrasonido2  
  digitalWrite(trigger2,LOW);
  delayMicroseconds(2);
  digitalWrite(trigger2,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger2,LOW);
  tiempo2=pulseIn(echo2,HIGH);
  distancia2=(tiempo2/2)/29.1;
  Serial.print(distancia2);
  Serial.print("cm2");
  Serial.println();
//Si la distancia esta entre 10 y 50 cm los motores se apagan
      if ((distancia2>=10) && (distancia2<=50)){
        digitalWrite(b_mtr,LOW);
        digitalWrite(r_mtr,LOW);
        digitalWrite(l_mtr,LOW);
        digitalWrite(m_mtr,LOW);
        digitalWrite(f_light,HIGH);
        delay(1000);
        cerca1=true;
        int direccion = 0;
         //Elije la dirección para girar
        incomingByte = 'a';
        /*
        direccion == random(2);
        if (direccion==0) {
          incomingByte='a';}
        else {
          incomingByte='a';}*/        
      }
  
   //Algoritmo para el ultrasonido3
  digitalWrite(trigger3,LOW);
  delayMicroseconds(2);
  digitalWrite(trigger3,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger3,LOW);
  tiempo3=pulseIn(echo3,HIGH);
  distancia3=(tiempo3/2)/29.1;
  Serial.print(distancia3);
  Serial.print("cm3");
  Serial.println();
//Si la distancia esta entre 10 y 50 cm los motores se apagan
          if ((distancia3>=10) && (distancia3<=50)){
        digitalWrite(b_mtr,LOW);
        digitalWrite(r_mtr,LOW);
        digitalWrite(l_mtr,LOW);
        digitalWrite(m_mtr,LOW);
        digitalWrite(f_light,HIGH);
        delay(1000);
        cerca2 = true;
        int direccion = 0;
         //Elije la dirección para girar
        incomingByte = 'd';
        /*
        direccion == random(2);
        if (direccion == 0) {
          incomingByte ='d';
        }else {
          incomingByte ='d';
        } 
        */       
      }
  // opciones de direccionamiento
  if (cerca && cerca1 && cerca2){
    incomingByte='f';
  }

  if(cantidadDeGiros >= 3){
    incomingByte = 'f';
    cantidadDeGiros = 0;
  }

  
  if(Serial.available()>0){
    incomingByte=Serial.read();
    }

    switch(incomingByte){
      case 'f'://Detenerse
        Serial.println("detenerse");
        Serial.print(incomingByte);
        digitalWrite(b_mtr,LOW);
        digitalWrite(r_mtr,LOW);
        digitalWrite(l_mtr,LOW);
        digitalWrite(m_mtr,LOW);
        digitalWrite(f_light,HIGH);
        incomingByte='*';
        break;
        case 'd'://Derecha
        Serial.println("derecha");
        Serial.print(incomingByte);
        digitalWrite(b_mtr,HIGH);
        digitalWrite(r_mtr,LOW);
        digitalWrite(l_mtr,HIGH);
        digitalWrite(m_mtr,LOW);
        delay(1000);
        digitalWrite(b_mtr,HIGH);
        digitalWrite(r_mtr,LOW);
        digitalWrite(l_mtr,LOW);
        digitalWrite(m_mtr,HIGH);  
        incomingByte='*';
        cantidadDeGiros++;
        break;
      case 'a'://Izquierda
        Serial.println("izquierda");
        Serial.print(incomingByte);
        digitalWrite(b_mtr,LOW);
        digitalWrite(r_mtr,HIGH);
        digitalWrite(l_mtr,LOW);
        digitalWrite(m_mtr,HIGH);
        delay(1000);
        digitalWrite(b_mtr,HIGH);
        digitalWrite(r_mtr,LOW);
        digitalWrite(l_mtr,LOW);
        digitalWrite(m_mtr,HIGH);  
        incomingByte='*';
        cantidadDeGiros ++;
        break;
      case 'w'://Avanzar
        Serial.println("Avanzar");
        digitalWrite(b_mtr,HIGH);
        digitalWrite(r_mtr,LOW);
        digitalWrite(l_mtr,LOW);
        digitalWrite(m_mtr,HIGH);      
        digitalWrite(f_light,HIGH);
        incomingByte='*';
        cantidadDeGiros = 0;
        break;
    }
}

