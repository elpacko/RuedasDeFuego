#include <SoftwareSerial.h>
SoftwareSerial configBT(0,1); //RX,TX
int i=0;
int cmd=0;
char entrada[129],salida[129];
//const int pinPowBT=6;
int carritoRun = 0;

int pinMotorEmpuje=10;
int pinMotorIzquierda=6;
int pinMotorDerecha=7;

int pinSensorDerecha=4;
int pinSensorIzquierda=5;
 
#define proximidadTrigPin 13
#define proximidadEchoPin 12




void setup(){

  pinMode(pinMotorEmpuje,OUTPUT);
  pinMode(pinMotorIzquierda,OUTPUT);
  pinMode(pinMotorDerecha,OUTPUT);
  
  pinMode(proximidadTrigPin, OUTPUT);
  pinMode(proximidadEchoPin, INPUT);

  

//Bluetooth Setup  
  //pinMode(pinPowBT,OUTPUT);
  //digitalWrite(pinPowBT,HIGH);
  configBT.begin(38400);
  Serial.begin(9600);
  Serial.print("Iniciando Ruedas de Fuego a 38400 baudios\r\n");
  
}
void mantenerRecto(){
  
  digitalWrite(pinMotorIzquierda,LOW);
  digitalWrite(pinMotorDerecha,LOW);
}
void girarIzquierda(){
  Serial.println("Gira Izquierda\r\n");
  digitalWrite(pinMotorIzquierda,HIGH);
  digitalWrite(pinMotorDerecha,LOW);
}
void girarDerecha(){
  Serial.println("Gira Derecha\r\n");
  digitalWrite(pinMotorIzquierda,LOW);
  digitalWrite(pinMotorDerecha,HIGH);
}
void pararCarro(){
  
  
  
  carritoRun =0;
  digitalWrite(pinMotorEmpuje,LOW);
  digitalWrite(pinMotorIzquierda,LOW);
  digitalWrite(pinMotorDerecha,LOW);
  
}
void arrancarCarro(){
  
  Serial.println("Arrancando Carro\r\n");
  carritoRun =1;
  digitalWrite(pinMotorEmpuje,HIGH);
}
 

void recibirComandoBT(){
  
  //Setear las variables en Null
  for(i=0;i<129;i++){
    entrada[i]=NULL;
    salida[i]=NULL;
  }
  delay(100);
  if(Serial.available()){
      cmd=1;
  }
  if(cmd==1){
  cmd=0;
   for(i=0;Serial.available();i++){
      if(i==0) delay(100);
      entrada[i]=Serial.read();
    }
    
  Serial.println(entrada);
 
  } 
  if(entrada=="p"){
    pararCarro();
  }
  if(entrada=="a"){
   Serial.println("-------------Avanzando-------------");
 
    arrancarCarro();
  }


  
  /*
  Serial.print("esperando comando\r\n");
  while(cmd==0){
    
  }
  cmd=0;
  Serial.print("recibiendo comando\r\n");
 
  Serial.print("imprimiendo Comando\r\n");
  
  //configBT.print(entrada);
  configBT.print("Listo...");
  configBT.print("\r\n");
  delay(1000);
  for(i=0;configBT.available();i++){
    salida[i]=configBT.read();
  }
  Serial.print("Respuesta:\r\n");
  if(salida[0]!=NULL) 
  {
    Serial.println(salida);
  }else
  {
    Serial.print("salida 0 is null\r\n");
  }*/
}
int objetoEnfrente(){
  long duration, distance;
  
  Serial.println("Checando objeto");
 
    digitalWrite(proximidadTrigPin, LOW);  // Added this line
    delayMicroseconds(2); // Added this line
    digitalWrite(proximidadTrigPin, HIGH);
  //  delayMicroseconds(1000); - Removed this line
    delayMicroseconds(10); // Added this line
    digitalWrite(proximidadTrigPin, LOW);
    duration = pulseIn(proximidadEchoPin, HIGH);
    distance = (duration/2) / 29.1;
    Serial.println(distance );
    if (distance < 4) {  // This is where the LED On/Off happens
      
 
     return 1;
  }
    else {
      return 0;
    }
    if (distance >= 200 || distance <= 0){
      Serial.println("Out of range");
    }
    else {
      Serial.print(distance);
      Serial.println(" cm"); 
    }
    delay(500);

  
}
void loop(){
  start: 
 delay(500);

 
  recibirComandoBT();
  if(carritoRun==1){

    if(0==0)//si ninguno detecta la linea mantener recto{
    {
      mantenerRecto();
    }
    else{
    
      if(0==1)//si el sensor derecho detecta la linea girar a la derecha
      {
        girarDerecha();
      }
      if(0==1)//si el sensor izquierdo detecta la linea girar a la izquierda
      {
  
        girarIzquierda();      
      }
    }
   
    if(objetoEnfrente()==1)//si el sensor de proximidad detecta una posible colision, parar el carro
    {
          pararCarro();
    }
  
  
  }

  
}





