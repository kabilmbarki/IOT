int val ;
/* Constantes pour les broches */
#define echo 4
#define trig 2   // Broche ECHO
 
/* Constantes pour le timeout */
const unsigned long MEASURE_TIMEOUT = 25000UL; // 25ms = ~8m à 340m/s

/* Vitesse du son dans l'air en mm/us */
const float SOUND_SPEED = 340.0 / 1000;


// Moteur 1
int IN1 = 6;
int IN2 = 7;
int pinPWMA = 3; //Speed

// Moteur 2
int IN3 = 10;
int IN4 = 11;
int pinPWMB = 5; //Speed

int analog_pin=A0;

void setup() {
   
  /* Initialise le port série */
  Serial.begin(115200);

  pinMode(8, OUTPUT);// Définir l'interface de la buzzer en sortie
  pinMode(13, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(pinPWMA, OUTPUT);

  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(pinPWMB, OUTPUT);
   
  /* Initialise les broches */
  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
  digitalWrite(trig, LOW);
}

void loop() {
  int temp;

temp=analogRead(analog_pin);

  val = digitalRead (13) ;
    if ((val == LOW)||(temp>512)) // Quand le capteur détecte une flamme, la led s'allume
  {
    digitalWrite (8, HIGH);
    Serial.println("Flamme");  
  }
  else
  {
    digitalWrite (8, LOW);
    Serial.println("Pas de flamme");
  }
  digitalWrite(trig, LOW);

  delayMicroseconds(2);
  
  /* 1. Lance une mesure de distance en envoyant une impulsion HIGH de 10µs sur la broche TRIGGER */
  digitalWrite(trig, HIGH);

  delayMicroseconds(10);

  digitalWrite(trig, LOW); // Reads the echoPin, returns the sound wave travel time in microseconds

  float duration = pulseIn(echo, HIGH); // Calculating the distance

  float distance = duration * 0.034 / 2; // Prints the distance on the Serial Monitorss

  Serial.print("Distance: ");

  Serial.println(distance);

  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  analogWrite(pinPWMA, 90);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
  analogWrite(pinPWMB, 110);
   
  /* Affiche les résultats en mm, cm et m */
  if(distance<= 60){
    digitalWrite(IN1, 0);
    digitalWrite(IN2, 0);
    analogWrite(pinPWMA, 0);
    digitalWrite(IN3, 1);
    digitalWrite(IN4, 0);
    analogWrite(pinPWMB, 90);
    delay(200);
  }
  
  if(distance<=40){
    digitalWrite(IN1, 0);
    digitalWrite(IN2, 1);
    analogWrite(pinPWMA, 80);
    digitalWrite(IN3, 0);
    digitalWrite(IN4, 1);
    analogWrite(pinPWMB, 90);
    delay(300);
  }
  
   
  /* Délai d'attente pour éviter d'afficher trop de résultats à la seconde */
  
}
