#include <Servo.h>  // Compatible ESP32

// === Déclaration des objets servo (5 doigts) ===
Servo servoPouce;
Servo servoIndex;
Servo servoMajeur;
Servo servoAnnulaire;
Servo servoAuriculaire;

// === Pins ===
int emgPin = 34;          // Entrée analogique EMG (ESP32 ADC)
int servoPin1 = 13;       // Servo Pouce
int servoPin2 = 14;       // Servo Index
int servoPin3 = 27;       // Servo Majeur
int servoPin4 = 26;       // Servo Annulaire
int servoPin5 = 25;       // Servo Auriculaire

// === Variables ===
int emgValue = 0;
int servoAngle = 90;      // Position neutre
int minEMG = 200;         // Seuil bas (repos) -> à calibrer selon ton capteur
int maxEMG = 2000;        // Seuil haut (contraction max) -> à calibrer

// === Initialisation ===
void setup() {
  Serial.begin(115200);

  // Attache des 5 servos
  servoPouce.attach(servoPin1);
  servoIndex.attach(servoPin2);
  servoMajeur.attach(servoPin3);
  servoAnnulaire.attach(servoPin4);
  servoAuriculaire.attach(servoPin5);

  // Position neutre au démarrage
  servoPouce.write(90);
  servoIndex.write(90);
  servoMajeur.write(90);
  servoAnnulaire.write(90);
  servoAuriculaire.write(90);

  Serial.println("=== Exo-Hand proportionnelle au signal EMG ===");
}

// === Boucle principale ===
void loop() {
  // Lecture brute EMG
  emgValue = analogRead(emgPin);

  // Limiter et calibrer le signal
  emgValue = constrain(emgValue, minEMG, maxEMG);

  // Mapping proportionnel → angle servo (60° à 120° par ex.)
  servoAngle = map(emgValue, minEMG, maxEMG, 60, 120);

  // Envoi aux servos (fermeture proportionnelle des doigts)
  servoPouce.write(servoAngle);
  servoIndex.write(servoAngle);
  servoMajeur.write(servoAngle);
  servoAnnulaire.write(servoAngle);
  servoAuriculaire.write(servoAngle);

  // Debug série
  Serial.print("EMG = ");
  Serial.print(emgValue);
  Serial.print("  |  Angle Servo = ");
  Serial.println(servoAngle);

  delay(20);  // petit délai pour stabilité
}
