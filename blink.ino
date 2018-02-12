/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman
  modified 17 Jan 2018
  by Antoine Tran Tan

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink

/* Constantes pour les broches */
const byte TRIGGER_DROITE = 2; // Broche TRIGGER DROITE
const byte ECHO_DROITE = 3;    // Broche ECHO DROITE
const byte TRIGGER_AVANT = 4;  // Broche TRIGGER AVANT
const byte ECHO_AVANT = 5;     // Broche ECHO AVANT
const byte TRIGGER_GAUCHE = 7; // Broche TRIGGER GAUCHE
const byte ECHO_GAUCHE = 6;    // Broche ECHO GAUCHE

/* Moteur A */
int ENA=9;  //Connecté à Arduino pin 9(sortie pwm)
int IN1=8;  //Connecté à Arduino pin 8
int IN2=12; //Connecté à Arduino pin 12

/* Moteur B */
int ENB=10;  //Connecté à Arduino pin 10(Sortie pwm)
int IN3=11;  //Connecté à Arduino pin 11
int IN4=13;  //Connecté à Arduino pin 13

/* Constantes pour le timeout */
const unsigned long MEASURE_TIMEOUT = 25000UL; // 25ms = ~8m à 340m/s

/* Vitesse du son dans l'air en mm/s */
const float SOUND_SPEED = 340.0 / 1000;

/** Fonction setup() */
void setup() {
   
  /* Initialise le port série */
  Serial.begin(115200);
 
   
  /* Initialise les broches */
  pinMode(TRIGGER_DROITE, OUTPUT);
  digitalWrite(TRIGGER_DROITE, LOW);
  pinMode(ECHO_DROITE, INPUT);
  pinMode(TRIGGER_AVANT, OUTPUT);
  digitalWrite(TRIGGER_AVANT, LOW);
  pinMode(ECHO_AVANT, INPUT);
  pinMode(TRIGGER_GAUCHE, OUTPUT);
  digitalWrite(TRIGGER_GAUCHE, LOW);
  pinMode(ECHO_GAUCHE, INPUT);
 
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  digitalWrite(ENA,HIGH);// Moteur A - Ne pas tourner (désactivation moteur)
  digitalWrite(ENB,HIGH);// Moteur B - Ne pas tourner (désactivation moteur)
 
 /* Direction du Moteur A */
 digitalWrite(IN1,LOW);
 digitalWrite(IN2,HIGH);
 
 /* Direction du Moteur B */
 digitalWrite(IN3,LOW);
 digitalWrite(IN4,HIGH);
}

/** Fonction loop() */
void loop() {
  
 /* 1. Lance une mesure de distance en envoyant une impulsion HIGH de 10µs sur la broche TRIGGER */
  digitalWrite(TRIGGER_DROITE, HIGH);
  digitalWrite(TRIGGER_AVANT, HIGH);
  digitalWrite(TRIGGER_GAUCHE, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_DROITE, LOW);
  digitalWrite(TRIGGER_AVANT, LOW);
  digitalWrite(TRIGGER_GAUCHE, LOW);

 
  /* 2. Mesure le temps entre l'envoi de l'impulsion ultrasonique et son écho (si il existe) */
  long mesure_droite = pulseIn(ECHO_DROITE, HIGH, MEASURE_TIMEOUT);
  long mesure_avant = pulseIn(ECHO_AVANT, HIGH, MEASURE_TIMEOUT);
  long mesure_gauche = pulseIn(ECHO_GAUCHE, HIGH, MEASURE_TIMEOUT);

 
  /* 3. Calcul la distance à partir du temps mesuré */
  float distance_droite = mesure_droite / 2.0 * SOUND_SPEED;
  float distance_avant = mesure_avant / 2.0 * SOUND_SPEED;
  float distance_gauche = mesure_gauche / 2.0 * SOUND_SPEED;

  /* 4. Contrôle des moteurs */
  analogWrite(ENA,128);
  analogWrite(ENB,128);
  if (distance_avant <= 300);
  {
    if (distance_droite <= 20);
    {
       analogWrite(ENB,255);
       delay(1500);
       analogWrite(ENB,128);
    }
    if (distance_gauche <= 20);
    {
      analogWrite(ENA,255);
      delay(1500);
      analogWrite(ENA,128);
    }
    if (distance_gauche <= 20 && distance_droite <=20);
    {
      analogWrite(ENA,0);
      analogWrite(ENB,0);
    }
      }
  delay(300);

}