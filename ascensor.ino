// los valores del rack son 1 si esta ocupado o 0 si esta libre


//se define SALIDA como el nombre del puerto serial a utilizar. si se usa el fisico
//dejar Serial, si no poner el nombre del softwareserial creado.

#include <SoftwareSerial.h>
#define VELOCIDADSUBIR 120
#define VELOCIDADBAJAR 120
const byte rPin = 4;
const byte tPin = 5;
SoftwareSerial miSalida (rPin, tPin);

#define SALIDA Serial

int estadoPiso;
int pinPiso;
int destino;
int actual = 0;

//Para que el codigo funcione los pisos deben tener sus sensores en orden creciente, uno despues del otro
int piso0 = 10;
int piso1 = 11;
int piso2 = 12;

int motor = 9;
int izq = 8;
int der = 7;


//Posicion de los sensores IR. Estan adelante del carro, numerados de izquierda a derecha

#define ZONACARGA 3



//pines de control de giro de los motores


//Estos dos tienen que ser PWM
#define DEFECTO 1
#define NEGRO 0
#define BLANCO 1
String mensaje;

int horizontalActual = DEFECTO;
int horizontalDestino;

char codigoAuto;
int mensajeValido = 0;

int colorCaja;
int filaDestino;
int columnaDestino;
int colorRecibido;
int negro;
int blanco;

int rack[3][2] = { {0,0},{0,0},{0,0} };

int i = 0;
void setup() {
  Serial.begin(9600);
  miSalida.begin(9600);
  pinMode(motor, OUTPUT);
  pinMode(izq, OUTPUT);
  pinMode(der, OUTPUT);
  pinMode(piso0, INPUT);
  pinMode(piso1, INPUT);
  pinMode(piso2, INPUT);




}

void loop() {
 /* int i = 0;
  while (0==0){
    if (i = 0){
      moverse(2);
        
    }
    i=i+1;
  }
*/
  
  recibirMensajeUno(mensaje);
  enviarMensajeUno();
  movimientoVertical(actual, 0);
  moverse(horizontalDestino);
  enviarMensajeDos();
  recibirMensajeDos(mensaje);
  proximoLugarEnRack(colorCaja, rack);
  ponerCaja(filaDestino, columnaDestino); 
}

void moverse(char destino){
  miSalida.write(horizontalDestino);
 
  while (miSalida.available() <= 0){
  delay(500);
  }
  // Serial.println("leo el mensaje");
  while (miSalida.available() > 0)
  {
  // Procesa el mensaje cuando un nuevo byte es recibido en el serial      
  char recieved = miSalida.read();
    
  break;  
 
  }
}

void recibirMensajeUno(String &mensaje){
mensajeValido = 0;
String inData;
//  Serial.println("Esperando mensaje");
//  Serial.println(Serial.available());
//  Serial.flush();
//  Serial.println(Serial.available());
  while (mensajeValido == 0){
    while (Serial.available() <= 0){
  //    Serial.print(".");
      delay(500);
    }
    Serial.println("leo el mensaje");
    while (Serial.available() > 0)
    {
        // Procesa el mensaje cuando un nuevo byte es recibido en el serial      
        char recieved = Serial.read();
        if (recieved == '@'){
          inData += recieved;
          while (Serial.available() > 0)
          {
            recieved = Serial.read();
            if (recieved == '!'){
              inData += recieved;
              break;
               
            }else {
              inData += recieved;
            }
         
          }
          mensaje=inData;
          verificarMensajeUno(mensaje);  
          break;  
        }
    }
   }  
}

void verificarMensajeUno(String &mensaje){
  String data = mensaje;
  mensajeValido = 0;
  int largo = data.length();
  if ((largo == 10) && (data[7] == 'G') && (data[8] == '3') && (data[4] == '1')){
  mensajeValido = 1;
  if (data[3] == '1' || data[3] == '2'){
    colorCaja = NEGRO;
    codigoAuto = mensaje[2];
    horizontalDestino = ZONACARGA;
    enviarMensajeUno;
  } else if (data[3] == '3' || data[3] == '4'){
    colorCaja = BLANCO;
    codigoAuto = mensaje[2];
    horizontalDestino = ZONACARGA;
    enviarMensajeUno;
  } else {
    mensajeValido = 0;
  }
  } else {
  //no es valido
  mensajeValido = 0;
  }
}

void enviarMensajeUno(){
  String carta = "@G3x0xxA";
  carta = carta + codigoAuto;
  carta = carta + '!';
  Serial.print(carta);
}

void recibirMensajeDos(String &mensaje){

mensajeValido = 0;
String inData;
//  Serial.println("Esperando mensaje");
//  Serial.println(Serial.available());
//  Serial.flush();
//  Serial.println(Serial.available());
  while (mensajeValido = 0){
    while (Serial.available() <= 0){
  //    Serial.print(".");
      delay(500);
    }
    Serial.println("leo el mensaje");
    while (Serial.available() > 0)
    {
        // Procesa el mensaje cuando un nuevo byte es recibido en el serial      
        char recieved = Serial.read();
        if (recieved == '@'){
          inData += recieved;
          while (Serial.available() > 0)
          {
            recieved = Serial.read();
            if (recieved == '!'){
              inData += recieved;
              break;
               
            }else {
              inData += recieved;
            }
         
          }
          mensaje=inData;
          verificarMensajeDos(mensaje);  
          break;  
        }
    }
   }  
}

void verificarMensajeDos(String &mensaje){
  String data = mensaje;
  mensajeValido = 0;
  int largo = data.length();
  if ((largo == 10) && (data[7] == 'G') && (data[8] == '3') && (data[4] == '3') && (data[2] == codigoAuto)){
  mensajeValido = 1;
  } else {
  //no es valido
  mensajeValido = 0;
  }
}

void enviarMensajeDos(){
 
  String carta = "@G3x2xxA";
  char codigoAuto = mensaje[2];
  carta = carta + codigoAuto;
  carta = carta + '!';
  Serial.print(carta);  
}

void ponerCaja(int fila, int columna){
 horizontalDestino = columnaDestino;
 moverse(horizontalDestino);
 movimientoVertical(actual, filaDestino);
 
}  

void proximoLugarEnRack(int color, int estanteria[3][2]){
  int existeDestino = 0;
 
  if (colorCaja == NEGRO){
  columnaDestino = 2;
  } else if (colorCaja == BLANCO){
  columnaDestino = 1;
  }
  for (int i; i < 3; i++){
  if (estanteria[i][columnaDestino] == 0){
    filaDestino = i;
    existeDestino = 1;
    break;
  }
  }
  if (existeDestino == 1){
  Serial.print("Yendo a destino: Fila ");
  Serial.print(filaDestino);
  Serial.print(" Columna: ");
  Serial.println(columnaDestino);
  estanteria[filaDestino][columnaDestino] = 1;
    
   // ponerCaja(filaDestino, columnaDestino);
    
  } else if (existeDestino == 0){
  SALIDA.println("No hay lugar disponible en la columna deseada");
  }

}

// void ponerCaja(int fila, int columna) {
 
// }

void subir(){
 
digitalWrite(izq, LOW);
digitalWrite(der, HIGH);


analogWrite(motor, VELOCIDADSUBIR);
}
void frenar(){
 
digitalWrite(izq, LOW);
digitalWrite(der, LOW);


analogWrite(motor, 0);
}

void superBajar(){
 
digitalWrite(izq, HIGH);
digitalWrite(der, LOW);


analogWrite(motor, 250);
}

void bajar(){
 
digitalWrite(izq, HIGH);
digitalWrite(der, LOW);


analogWrite(motor, VELOCIDADBAJAR);
}


void movimientoVertical(int pisoActual, int pisoDestino){
 
  if (2 >= pisoDestino && pisoDestino > pisoActual && pisoActual >= 0){
   
  Serial.println("Subiendo");
  pinPiso = pisoDestino+piso0;   
  estadoPiso = digitalRead(pinPiso);
  Serial.println(estadoPiso);
   
  while(estadoPiso == HIGH){
    subir();
    estadoPiso = digitalRead(pinPiso);
  }
    
  frenar();
  actual = pisoDestino;
 
  }
 
  else if (0 <= pisoDestino && pisoDestino < pisoActual && pisoActual <= 2){
    
  //Serial.println("Bajando");
  pinPiso = pisoDestino+piso0;
  int estadoPiso = digitalRead(pinPiso);
  //Serial.println(estadoPiso);
  superBajar();
  delay(100); 
  while(estadoPiso == HIGH){
    bajar();
    estadoPiso = digitalRead(pinPiso);
  }
    
  frenar();
  actual = pisoDestino;
   
  }
 
  else if (pisoDestino == pisoActual){
 
  //Serial.println("Ya estas en ese piso");
 
  }
   
  else if (pisoDestino < 0 || pisoDestino > 2){
   
  Serial.println("Ese piso no existe");
 
  }

}
