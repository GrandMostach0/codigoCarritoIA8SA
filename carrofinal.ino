#define b_mtr 2 //motor defu atras conectado al pin 2
#define r_mtr 3 //motor giro derecho conectado al pin 3
#define l_mtr 4 //motor giro izquierdo conectado al pin 4
#define m_mtr 5 //motor atras conectado al pin 5
#define f_light 6 //led conectados al pin 6
//sensor frente
int trigger = 8;
int echo = 7;
//sensor derecha
int trigger2 = 9;
int echo2 = 10;
//sensor izquierda
int trigger3 = 11;
int echo3 = 12;

float distancia,tiempo, distancia2, tiempo2,distancia3,tiempo3;
//fin sensores

//ocnfiguración para la red
const int InputNodes= 4; //de entrada mas BIAS
const int HiddenNodes= 4; //oculta mas BIAS
const int OutputNodes= 4; // salida

int i, j;
double Accum;
double Hidden[HiddenNodes];
double motores[OutputNodes];

// pesos de la red neuronal
float HiddenWeights[4][4] = {{-0.9759674734370405, 2.1232305149805035, -1.237806097732913, 1.0574001466744865}, {-3.5861906230188136, -0.7355021143726302, -0.3635774708834264, 4.548039131374539}, {0.3649066797881441, -1.1825052012619977, 0.00872832515181604, 3.8283960850226926}, {0.02582037773390596, 1.2880922507076282, -0.03311861498273724, -2.003547987217645}};
float OutputWeights[4][4] = {{1.3063251950612316, -1.2894996366167844, -0.5444131543142364, 0.08511056122114906}, {-1.211984384868219, 0.00456693301195881, -0.03280836390056583, -0.9571769799773575}, {-2.684487461979238, -0.012481606764312314, -1.3210671771007607, -1.1289121285066601}, {-0.09771831546660519, -1.289869800896117, -1.7698474694921984, -0.06887538350553411}};

int estado[4]={0,0,0,0};
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
  int sensores[] = {0,0,0,0};
  //Algoritmo para el ultrasonido  
  digitalWrite(trigger,LOW);
  delayMicroseconds(2);
  digitalWrite(trigger,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger,LOW);
  tiempo=pulseIn(echo,HIGH);
  distancia=(tiempo/2)/29.1; //convierte el tiempo en la distancia
  Serial.print(distancia);
  Serial.print("cm");
  Serial.println();
//Si la distancia esta entre 10 y 50 cm los motores se apagan
    if ((distancia<25)){
        distancia = 1;
        digitalWrite(b_mtr,LOW);
        digitalWrite(r_mtr,LOW);
        digitalWrite(l_mtr,LOW);
        digitalWrite(m_mtr,LOW);
        digitalWrite(f_light,HIGH);
        delay(2000);
      } else if((distancia<=50)){
        distancia = 0;
    }else{
      distancia =-1;
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
    if ((distancia2<25)){
        distancia2 = 1;
        digitalWrite(b_mtr,LOW);
        digitalWrite(r_mtr,LOW);
        digitalWrite(l_mtr,LOW);
        digitalWrite(m_mtr,LOW);
        digitalWrite(f_light,HIGH);
        delay(2000);    
      } else if((distancia2<=50)){
        distancia2 = 0;
    }else{
      distancia2 =-1;
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
    if ((distancia3<25)){
        distancia3 = 1;
        digitalWrite(b_mtr,LOW);
        digitalWrite(r_mtr,LOW);
        digitalWrite(l_mtr,LOW);
        digitalWrite(m_mtr,LOW);
        digitalWrite(f_light,HIGH);
        delay(2000);       
      } else if((distancia3<=50)){
        distancia3 = 0;
    }else{
      distancia3 =-1;
    }

  sensores[0]= 1;
  sensores[1]= distancia;
  sensores[2]= distancia2;
  sensores[3] = distancia3;

  InputToOutput(sensores[0], sensores[1], sensores[2], sensores[3]);

  // salidas
  estado[0]= round(abs(motores[0]));
  estado[1] = round(abs(motores[1]));
  estado[2] = round(abs(motores[2]));
  estado[3] = round(abs(motores[3]));

  int avanza[4] = {1, 0, 0, 1};
  int detener[4]= {0,0,0,0};
  int derecha[4]={1, 0, 1, 0};
  int izquierda[4]={0, 1, 0, 1};

  if(sonIguales(avanza, estado)){
    incomingByte = 'w'; 
  }

  if(sonIguales(detener, estado)){
    incomingByte = 'f'; 
  }

  if(sonIguales(derecha, estado)){
    incomingByte = 'd'; 
  }

  if(sonIguales(izquierda, estado)){
    incomingByte = 'a'; 
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
        delay(2000);  
        incomingByte='*';
        break;
      case 'a'://Izquierda
        Serial.println("izquierda");
        Serial.print(incomingByte);
        digitalWrite(b_mtr,LOW);
        digitalWrite(r_mtr,HIGH);
        digitalWrite(l_mtr,LOW);
        digitalWrite(m_mtr,HIGH);
        delay(2000); 
        incomingByte='*';
        break;
      case 'w'://Avanzar
        Serial.println("Avanzar");
        digitalWrite(b_mtr,HIGH);
        digitalWrite(r_mtr,LOW);
        digitalWrite(l_mtr,LOW);
        digitalWrite(m_mtr,HIGH);      
        digitalWrite(f_light,HIGH);
        incomingByte='*';
        break;
    }
}

void InputToOutput(int bias, int distancia, int distancia2, int distancia3)
{
  int sensores[] = {0, 0,0};
  sensores[0] = bias;
  sensores[1] = distancia;
  sensores[2] = distancia2;
  sensores[2] = distancia3;
 
  /******************************************************************
    Calcular las activaciones en las capas ocultas
  ******************************************************************/
 
  for ( i = 0 ; i < HiddenNodes ; i++ ) {
    Accum = 0;//HiddenWeights[InputNodes][i] ;
    for ( j = 0 ; j < InputNodes ; j++ ) {
      Accum += sensores[j] * HiddenWeights[j][i] ;
    }
    Hidden[i] = tanh(Accum) ; //tanh
  }
 
  /******************************************************************
    Calcular activacion y error en la capa de Salida
  ******************************************************************/
 
  for ( i = 0 ; i < OutputNodes ; i++ ) {
    Accum = 0;//OutputWeights[HiddenNodes][i];
    for ( j = 0 ; j < HiddenNodes ; j++ ) {
        Accum += Hidden[j] * OutputWeights[j][i] ;
    }
    motores[i] = tanh(Accum) ;//tanh
  }
 
}


bool sonIguales(int arr1[], int arr2[]) {
  int longitud = 4;

  for (int i = 0; i < longitud; i++) {
    if (arr1[i] != arr2[i]) {
      return false;
    }
  }

  return true;
}
