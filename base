#define SENSOR0 4
#define SENSOR1 3
#define SENSOR2 2
#define SENSOR3 5

#define LINEA LOW
#define PISO HIGH

#define MOTOR1I 8
#define MOTOR1D 9
#define MOTOR2I 12
#define MOTOR2D 13

#define VELOCIDAD1 10
#define VELOCIDAD2 11

#define DEFECTO 1

int destinoMovimiento;
int estadoCruz;
int estadoIzq;
int estadoDer;
int estadoMedioDer;
int estadoMedioIzq;
int Velocidad = 90;

int horizontalActual = DEFECTO;
int horizontalDestino;

void setup() {
  Serial.begin(9600);
  pinMode(SENSOR0, INPUT);
  pinMode(SENSOR1, INPUT);
  pinMode(SENSOR2, INPUT);
  pinMode(SENSOR3, INPUT);
  pinMode(VELOCIDAD2, OUTPUT);
  pinMode(VELOCIDAD1, OUTPUT);
  pinMode(MOTOR1I, OUTPUT);
  pinMode(MOTOR1D, OUTPUT);
  pinMode(MOTOR2I, OUTPUT);
  pinMode(MOTOR2D, OUTPUT);

}

void loop() {
 /*
  int i = 0;
  while(0 == 0){
    if (i == 0){
      Serial.println("Andando");
        movimientoHorizontal(3);
      i = 1;
    }
  }
*/
  
 recibirDestino(horizontalDestino);
 movimientoHorizontal(horizontalDestino);
 enviarVerificacion();
 
}

void enviarVerificacion(){
  Serial.print('1');
}

void recibirDestino(int &destino){

    while (Serial.available() <= 0){
      delay(500);
    }
   // Serial.println("leo el mensaje");
    while (Serial.available() > 0)
    {
        // Procesa el mensaje cuando un nuevo byte es recibido en el serial        
          char recieved = Serial.read();
          destino = recieved;  
          break;  
        
    }  
}


void movimientoHorizontal(int destino){
 
 while (horizontalActual != destino) {
    
  if (horizontalActual < destino){
    horizontalAdelante();
  } else if (horizontalActual > destino){
    horizontalAtras();
  }
  //aca se puede meter un print de "Llegaste!"
 }
 horizontalActual = destino;
}

void horizontalAdelante(){
  estadoCruz = 0;
  adelante();
  delay(400);
//  while (estadoCruz == 1){
//    adelante();
//    estadoCruz = digitalRead(SENSORCRUZ);
//  }
  while (estadoCruz == 0){
    avanzar();
  }
  frenar();
  horizontalActual = horizontalActual + 1;
}

void horizontalAtras(){
  estadoCruz = 0;
  atras();
  delay(400);
//  while (estadoCruz == LINEA){
//    atras();
//    estadoCruz = digitalRead(SENSORCRUZ);
//  }
  while (estadoCruz == 0){
    retroceder();
  }
  frenar();
  
  horizontalActual = horizontalActual - 1;
}

void avanzar(){

  actualizarSensores();

  if (estadoIzq == LINEA && estadoMedioIzq == LINEA && estadoMedioDer == LINEA && estadoDer == LINEA) {
  //efrenar();
  cruz();
  }

  else if (estadoIzq == PISO && estadoMedioIzq == PISO && estadoMedioDer == PISO && estadoDer == PISO) {
  frenar();
  }
 
  else if (estadoIzq == PISO && estadoMedioIzq == LINEA && estadoMedioDer == LINEA && estadoDer == PISO) {
  adelante();
  }
 
  else if (estadoIzq == PISO && estadoMedioIzq == PISO && estadoMedioDer == LINEA && estadoDer == PISO) {
  superDerecha();
  }
 
  else if (estadoIzq == PISO && estadoMedioIzq == PISO && estadoMedioDer == LINEA && estadoDer == LINEA) {
  superDerecha();
  }
 
  else if (estadoIzq == PISO && estadoMedioIzq == LINEA && estadoMedioDer == PISO && estadoDer == PISO) {
  superIzquierda();
  }
 
  else if (estadoIzq == LINEA && estadoMedioIzq == LINEA && estadoMedioDer == PISO && estadoDer == PISO) {
  superIzquierda();
  }
 
  else if (estadoIzq == PISO && estadoMedioIzq == PISO && estadoMedioDer == PISO && estadoDer == LINEA) {
  superDerecha();
  }
 
  else if (estadoIzq == LINEA && estadoMedioIzq == PISO && estadoMedioDer == PISO && estadoDer == PISO) {
  superIzquierda();
  }

}

void retroceder(){

  actualizarSensores();

  if (estadoIzq == LINEA && estadoMedioIzq == LINEA && estadoMedioDer == LINEA && estadoDer == LINEA) {
  cruz();
  }

  else if (estadoIzq == PISO && estadoMedioIzq == PISO && estadoMedioDer == PISO && estadoDer == PISO) {
  frenar();
  }
 
  else if (estadoIzq == PISO && estadoMedioIzq == LINEA && estadoMedioDer == LINEA && estadoDer == PISO) {
  atras();
  }
 
  else if (estadoIzq == PISO && estadoMedioIzq == PISO && estadoMedioDer == LINEA && estadoDer == PISO) {
  superIzquierda();
  }
 
  else if (estadoIzq == PISO && estadoMedioIzq == PISO && estadoMedioDer == LINEA && estadoDer == LINEA) {
  superIzquierda();
  }
 
  else if (estadoIzq == PISO && estadoMedioIzq == LINEA && estadoMedioDer == PISO && estadoDer == PISO) {
  superDerecha();
  }
 
  else if (estadoIzq == LINEA && estadoMedioIzq == LINEA && estadoMedioDer == PISO && estadoDer == PISO) {
  superDerecha();
  }
 
  else if (estadoIzq == PISO && estadoMedioIzq == PISO && estadoMedioDer == PISO && estadoDer == LINEA) {
  superIzquierda();
  }
 
  else if (estadoIzq == LINEA && estadoMedioIzq == PISO && estadoMedioDer == PISO && estadoDer == PISO) {
  superDerecha();
  }

}

void actualizarSensores() {
 
  estadoIzq = digitalRead(SENSOR0);
  estadoDer = digitalRead(SENSOR3);
  estadoMedioDer = digitalRead(SENSOR2);
  estadoMedioIzq = digitalRead(SENSOR1);

}
void adelante(){
  digitalWrite(MOTOR1I, HIGH);
  digitalWrite(MOTOR1D, LOW);
  digitalWrite(MOTOR2I, HIGH);
  digitalWrite(MOTOR2D, LOW);
  analogWrite(VELOCIDAD1, Velocidad);
  analogWrite(VELOCIDAD2, Velocidad);
}
 
void atras(){
  digitalWrite(MOTOR1I, LOW);
  digitalWrite(MOTOR1D, HIGH);
  digitalWrite(MOTOR2I, LOW);
  digitalWrite(MOTOR2D, HIGH);
  analogWrite(VELOCIDAD1, Velocidad);
  analogWrite(VELOCIDAD2, Velocidad);
}

void superDerecha(){
  digitalWrite(MOTOR1I, HIGH);
  digitalWrite(MOTOR1D, LOW);
  digitalWrite(MOTOR2I, HIGH);
  digitalWrite(MOTOR2D, LOW);
  analogWrite(VELOCIDAD1, 0);
  analogWrite(VELOCIDAD2, Velocidad);
}

void superIzquierda(){
  digitalWrite(MOTOR1I, HIGH);
  digitalWrite(MOTOR1D, LOW);
  digitalWrite(MOTOR2I, HIGH);
  digitalWrite(MOTOR2D, LOW);
  analogWrite(VELOCIDAD1, Velocidad);
  analogWrite(VELOCIDAD2, 0);
}


void frenar(){
  digitalWrite(MOTOR1I, HIGH);
  digitalWrite(MOTOR1D, LOW);
  digitalWrite(MOTOR2I, HIGH);
  digitalWrite(MOTOR2D, LOW);
  analogWrite(VELOCIDAD1, 0);
  analogWrite(VELOCIDAD2, 0);
}
 
void cruz(){
  estadoCruz = 1;
}
