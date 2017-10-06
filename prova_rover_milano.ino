#include <Servo.h>
#include <SoftwareSerial.h>
#define TX 2//TX 1
#define RX 3//RX 0

//SoftwareSerial bt = SoftwareSerial(RX, TX);
SoftwareSerial bt = SoftwareSerial(RX, TX);
Servo myServo;
int distance;
long duration;
int obs = 0;
int stato = 0;

int ligth = 7;
int IN1 = 10;
int IN2 = 11;
int IN3 = 12;
int IN4 = 13;
int echoPin = 9;
int trigPin = 8;
int servo = 6;//servo = 3;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:

  pinMode(ligth, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  bt.begin(9600);
  Serial.begin(9600); // se no funziona mettere Serial.begin(38400);
  myServo.attach(6);
  myServo.write(90); // facciamo un loop più giù in modo che giri  in base al grado
  digitalWrite(ligth, HIGH);
  brake();
  delay(400);
}

// the loop routine runs over and over again forever:
void loop() {
  while (bt.available() > 0) {
    char c = bt.read();
    if (c == 'w') {
      obs = 0;
      forward();
    } else if (c == 's') {
      obs = 0;
      backward();
    } else if (c == 'd') {
      obs = 0;
      right();
    } else if (c == 'a') {
      obs = 0;
      left();
    } else if (c == 'q') {
      obs = 1; //obs = 0;
      brake();
    } else if (c == 'l') {
      if (stato == 1) {
        stato = 0;
        digitalWrite(ligth, HIGH);
      } else if (stato == 0) {
        stato = 1;
        digitalWrite(ligth, LOW);
      }
    }
    if (obs == 0) {
     for (int i = 0; i <= 180; i = i + 60) {
      myServo.write(i);
      delay(400); // se li togli entrambi (anche quello sotto) inizia a fare il matto
      distance = calculateDistance();
      bt.print(i);//Serial.println(i);
      bt.print(" , ");
      bt.println(distance);
      // Serial.println(".");
      if (distance < 5) {
         obs = 1;
        brake();
      }else{
        
      }
      Serial.print(i); //Serial.println(i);
      Serial.print(" , ");
      Serial.println(distance);
    }
    if (obs == 1) {
     // backward();
      delay(200);
      brake();
    }
  } 
  }
//distance = calculateDistance(); rimettilo se non funziona
  
  /* if (obs == 0) {
    for (int i = 180; i > 0; i = i - 5) {
      myServo.write(i);
      delay(100);
      distance = calculateDistance();
      bt.print(i); //Serial.println(i);
      bt.print(" , ");
      bt.println(distance);
      // Serial.println(".");
      if (distance < 5) {
         obs = 1;
        brake();
      }
      Serial.print(i); //Serial.println(i);
      Serial.print(" , ");
      Serial.println(distance);
    }
    if (obs == 1) {
     // backward();
      delay(200);
      brake();
    }
  } */
   /* if (obs == 0) { questo secondo giro forse non lo facciamo.
    for (int i = 150; i >= 30; i = i - 30) {
      myServo.write(i);
      delay(100);
      distance = calculateDistance();
      //Serial.print(i);//Serial.println(i);
      //Serial.print(",");
      Serial.print(distance);
      Serial.print(".");
      if (distance < 20) {
        obs = 1;
        brake();
      }
    } 
    if (obs == 1) {
     // backward();
      delay(2000);
      brake();
    } 
  } */
}

int calculateDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  return distance;

}

void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void backward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void right() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void left() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void brake() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}



