#include <SoftwareSerial.h>
SoftwareSerial configBT(2,3); //RX,TX
int i=0;
int cmd=0;
int serialVerbose =0; //1 manda al serial los mensajes mas a detalle
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
  Serial.begin(9600);
  Serial.print("Iniciando Ruedas de Fuego a 38400 baudios\r\n");
  
  configBT.begin(9600);
  configBT.print("Iniciando Bluetooth");

  
}
void mantenerRecto(){
  
  digitalWrite(pinMotorIzquierda,LOW);
  digitalWrite(pinMotorDerecha,LOW);
}
void girarIzquierda(){
  imprimeMensaje("Gira Izquierda",1);
  
  digitalWrite(pinMotorIzquierda,HIGH);
  digitalWrite(pinMotorDerecha,LOW);
}
void girarDerecha(){
  imprimeMensaje("Gira Derecha",1);
   
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
  imprimeMensaje("Arrancando Carro",1);
  carritoRun =1;
  digitalWrite(pinMotorEmpuje,HIGH);
}
 

void recibirComandoBT_pin01(){
  
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
  imprimeMensaje(entrada,0);
  
 
  } 
 

}
void recibirComandoBT(){
   imprimeMensaje("Esperando comando BT",0); 
 
  //configBT.print("mensaje a bluetooth");
 
  for(i=0;configBT.available();i++){
    salida[i]=configBT.read();
  }
  
  if(salida[0]!=NULL) 
  {
      imprimeMensaje(salida,1);
       if(String(salida)=="p"){
        imprimeMensaje("-------------Parando-------------",0);
          pararCarro();
        }
        if(String(salida)=="a"){
          imprimeMensaje("-------------Avanzando-------------",0);
          arrancarCarro();
        }
      salida[0]=NULL;
  }
  
  
}
int objetoEnfrente(){
  long duration, distance;
  int returnme=1; // el valor default es 1 por que si no podemos sensar hay que parar el carro
    imprimeMensaje("Checando proximidad",0);
    digitalWrite(proximidadTrigPin, LOW);  
    delayMicroseconds(2); 
    digitalWrite(proximidadTrigPin, HIGH);
    delayMicroseconds(10);   //PENDIENTE: quitar y probar funcionamiento del sensor
    digitalWrite(proximidadTrigPin, LOW);
    duration = pulseIn(proximidadEchoPin, HIGH);
    distance = (duration/2) / 29.1;
    imprimeMensaje(String(distance),0);
     
    if (distance < 7) {
        
      imprimeMensaje(" Objeto en menos de 5 cm",1); 
      returnme= 1;
    }
    else {
        returnme= 0;
      }
 
    //delay(500); //PENDIENTE: quitar y probar funcionamiento del sensor
  return returnme;
  
}
void imprimeMensaje(String mensaje ,int level){//level =0 muestra si verbose=1, level =1 siempre muestra
 if(serialVerbose==1 || level==1){
      Serial.println(mensaje);
      
    } 
  
}
void loop(){
  start: 
  //carritoRun=1;//debug
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





