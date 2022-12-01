
#include <LiquidCrystal.h>
#define  a3f    208     
#define  b3f    233     
#define  b3     247     
#define  c4     261     
#define  c4s    277     
#define  e4f    311         
#define  f4     349     
#define  a4f    415     
#define  b4f    466     
#define  b4     493 
#define  c5     523     
#define  c5s    554 
#define  e5f    622     
#define  f5     698     
#define  f5s    740 
#define  a5f    831     

#define rest    -1
int piezo = 7; 
int song = 1;
volatile int beatlength = 100; 
float beatseparationconstant = 0.2;
int threshold;
int a; // part index
int b; // song index
int c; // lyric index

// Parts 1 and 2 (Intro)

int song1_intro_melody[] =
{c5s, e5f, e5f, f5, a5f, f5s, f5, e5f, c5s, e5f, rest, a4f, a4f};

int song1_intro_rhythmn[] =
{6, 10, 6, 6, 1, 1, 1, 1, 6, 10, 4, 2, 10};

// Parts 3 or 5 (Verse 1)

int song1_verse1_melody[] =
{ rest, c4s, c4s, c4s, c4s, e4f, rest, c4, b3f, a3f,
  rest, b3f, b3f, c4, c4s, a3f, a4f, a4f, e4f,
  rest, b3f, b3f, c4, c4s, b3f, c4s, e4f, rest, c4, b3f, b3f, a3f,
  rest, b3f, b3f, c4, c4s, a3f, a3f, e4f, e4f, e4f, f4, e4f,
  c4s, e4f, f4, c4s, e4f, e4f, e4f, f4, e4f, a3f,
  rest, b3f, c4, c4s, a3f, rest, e4f, f4, e4f
};

int song1_verse1_rhythmn[] =
{ 2, 1, 1, 1, 1, 2, 1, 1, 1, 5,
  1, 1, 1, 1, 3, 1, 2, 1, 5,
  1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 3,
  1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 4,
  5, 1, 1, 1, 1, 1, 1, 1, 2, 2,
  2, 1, 1, 1, 3, 1, 1, 1, 3
};

// Parts 4 or 6 (Chorus)

int song1_chorus_melody[] =
{ b4f, b4f, a4f, a4f,
  f5, f5, e5f, b4f, b4f, a4f, a4f, e5f, e5f, c5s, c5, b4f,
  c5s, c5s, c5s, c5s,
  c5s, e5f, c5, b4f, a4f, a4f, a4f, e5f, c5s,
  b4f, b4f, a4f, a4f,
  f5, f5, e5f, b4f, b4f, a4f, a4f, a5f, c5, c5s, c5, b4f,
  c5s, c5s, c5s, c5s,
  c5s, e5f, c5, b4f, a4f, rest, a4f, e5f, c5s, rest
};

int song1_chorus_rhythmn[] =
{ 1, 1, 1, 1,
  3, 3, 6, 1, 1, 1, 1, 3, 3, 3, 1, 2,
  1, 1, 1, 1,
  3, 3, 3, 1, 2, 2, 2, 4, 8,
  1, 1, 1, 1,
  3, 3, 6, 1, 1, 1, 1, 3, 3, 3, 1, 2,
  1, 1, 1, 1,
  3, 3, 3, 1, 2, 2, 2, 4, 8, 4
};

/* Special Characters */
byte buttonNoPress1[] = {
  0x00,0x00,0x00,0x07,0x04,0x04,0x04,0x0F
};

byte buttonNoPress2[] = {
  0x00,0x00,0x00,0x1C,0x04,0x04,0x04,0x1E
};

byte buttonPress1[] = {
  0x00,0x02,0x12,0x08,0x00,0x07,0x04,0x0F
};

byte buttonPress2[] = {
  0x00,0x08,0x09,0x02,0x00,0x1C,0x04,0x1E
};


//declaring variables
const int LED_BLUE = 2;
const int LED_YELLOW = 3;
const int LED_RED = 4;
const int LED_GREEN = 5;
const int PIN_BUZZER = 7;
const int RS = 8;
const int E = 9;
const int D4 = 10;
const int D5 = 11;
const int D6 = 12;
const int D7 = 13;
const int GREEN_PRESSED = A0;
const int RED_PRESSED = A1;
const int YELLOW_PRESSED = A2;
const int BLUE_PRESSED = A3;
const int START_BUTTON = A5;
const int GREEN_SOUND = 550;
const int RED_SOUND = 500;
const int YELLOW_SOUND = 450;
const int BLUE_SOUND = 400;
const int SOUND_DURATION = 100;
const int POTENCIOMETRO = A4;
const int MAX_ROUNDS = 100;//I want to just have a high score and not a winning screen-simar
int level = 1;
  
int speed = 300;        

int OriginalSequence[MAX_ROUNDS];
int UsernameSequence[MAX_ROUNDS];
int GreenRead = -1;         
int RedRead = -1;          
int YellowRead = -1;      
int BlueRead = -1;          
int PotencyRead = -1;        
const int OFF = -99;    
int buttonPressed = OFF; 
int colourPressed = OFF;                      
int ReadConditionButtonPressed = OFF;
int leerPotenc = -1;
bool someButtonPressed = false;                  
bool leave = false;
bool gameOver = false;



LiquidCrystal lcd(RS, E, D4, D5, D6, D7);

void setup() {
  
  a = 4;
  b = 0;
  c = 0;
  
  

     lcd.begin(16, 2);
  
  lcd.createChar(0, buttonNoPress1);
  lcd.createChar(1, buttonNoPress2);
  lcd.createChar(2, buttonPress1);
  lcd.createChar(3, buttonPress2);
  
  
  lcd.clear();
  lcd.print("Made by Simar:) ");
 
  
  Serial.begin(9600);

  pinMode(GREEN_PRESSED, INPUT);
  pinMode(RED_PRESSED, INPUT);
  pinMode(YELLOW_PRESSED, INPUT);
  pinMode(BLUE_PRESSED, INPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_BLUE, LOW);

  for (int n = LED_GREEN; n >= LED_BLUE; n--) {
    digitalWrite(n, HIGH);
    delay(80);
    digitalWrite(n, LOW);
  }
  delay(400);
  for (int n = LED_BLUE; n <= LED_GREEN; n++) {
    digitalWrite(n, HIGH);
    delay(80);
    digitalWrite(n, LOW);
  }
  Serial.print(" # SIMAR SAYS #");
  
  
  lcd.clear();
  lcd.print(" # SIMAR SAYS #");
  while(digitalRead(START_BUTTON) == HIGH){
    
    lcd.setCursor(0, 1);
    lcd.print(" PUSH START  ");
  
  }
  generateSequence();
}
void loop()
{ 
    
  lcd.clear();
  lcd.print("# SIMAR SAYS #");
  lcd.setCursor(0, 1);
  lcd.print("    ROUND:" + String(level));
  delay(750);

  showSequence();
  
  buttonPressed = OFF;
  
  while(!leave)
    compareSequence();
  if(gameOver){
    
    finalizePlay();
    while(1){
      
      delay(1000);
      lcd.setCursor(0, 1); 
    }
  }

  if(level == MAX_ROUNDS) {
       lcd.clear();
    
    while(1){
      finalizePlayGain();
    }
  }
  level++;
  leave = false;
}
void generateSequence() {
  randomSeed(millis());
  for (int i = 0; i < MAX_ROUNDS; i++){
    OriginalSequence[i] = random(LED_BLUE, LED_GREEN+1);
  }
  Serial.print("Sequence complete: \n[");
  for (int i = 0; i < MAX_ROUNDS-1; i++){
    if(OriginalSequence[i] == LED_GREEN)
      Serial.print("G ");
    else if(OriginalSequence[i] == LED_RED)
      Serial.print("R ");
    else if(OriginalSequence[i] == LED_YELLOW)
      Serial.print("Y ");
    else if(OriginalSequence[i] == LED_BLUE)
      Serial.print("B ");
  }
  if(OriginalSequence[MAX_ROUNDS-1] == LED_GREEN)
    Serial.print("G]\n\n");
  else if(OriginalSequence[MAX_ROUNDS-1] == LED_RED)
    Serial.print("R]\n\n");
  else if(OriginalSequence[MAX_ROUNDS-1] == LED_YELLOW)
    Serial.print("Y]\n\n");
  else if(OriginalSequence[MAX_ROUNDS-1] == LED_BLUE)
    Serial.print("B]\n\n");
}
void showSequence() {
  leerPotenc = analogRead(POTENCIOMETRO);
  if(level < 9){
  lcd.print(" ");
  }
 
  speed = calculateVelocity(PotencyRead);
  for (int i = 0; i < level; i++){
    if(OriginalSequence[i] == LED_GREEN)
      tone(PIN_BUZZER, GREEN_SOUND, SOUND_DURATION);
    else if(OriginalSequence[i] == LED_RED)
      tone(PIN_BUZZER, RED_SOUND, SOUND_DURATION);
    else if(OriginalSequence[i] == LED_YELLOW)
      tone(PIN_BUZZER, YELLOW_SOUND, SOUND_DURATION);
    else if(OriginalSequence[i] == LED_BLUE)
      tone(PIN_BUZZER, BLUE_SOUND, SOUND_DURATION);
    digitalWrite(OriginalSequence[i], HIGH);
    delay(500);
    digitalWrite(OriginalSequence[i], LOW);
    delay(500);
  }
}
int calculateVelocity (int valorP) {
  valorP = map(valorP, 0, 1023, 0, 3);
  if (valorP >= 2) {
    delay(1000);
    return 300;
  } else if (valorP == 1) {
    delay(1000);
    return 200;
  } else if (valorP == 0) {
    delay(1000);
    return 100;
  }
  return 300;
}
void compareSequence() {
  for(int i = 0; i < level;){
    someButtonPressed = false;
    GreenRead = digitalRead(GREEN_PRESSED);
    RedRead = digitalRead(RED_PRESSED);
    YellowRead = digitalRead(YELLOW_PRESSED);
    BlueRead = digitalRead(BLUE_PRESSED);
    if(GreenRead == LOW) {
    tone(PIN_BUZZER, GREEN_SOUND, SOUND_DURATION);
      ReadConditionButtonPressed = GreenRead;
      buttonPressed = GREEN_PRESSED;
      colourPressed = LED_GREEN;
      digitalWrite(LED_GREEN, HIGH);
      someButtonPressed = true;
    }
    else if(RedRead == LOW) {
    tone(PIN_BUZZER, RED_SOUND, SOUND_DURATION);
      ReadConditionButtonPressed = RedRead;
      buttonPressed = RED_PRESSED;
      colourPressed = LED_RED;
      digitalWrite(LED_RED, HIGH);
      someButtonPressed = true;
    }
    else if (YellowRead == LOW) {
    tone(PIN_BUZZER, YELLOW_SOUND, SOUND_DURATION);
      ReadConditionButtonPressed = YellowRead;
      buttonPressed = YELLOW_PRESSED;
      colourPressed = LED_YELLOW;
      digitalWrite(LED_YELLOW, HIGH);
      someButtonPressed = true;
    }
    else if (BlueRead == LOW) {
    tone(PIN_BUZZER, BLUE_SOUND, SOUND_DURATION);
      ReadConditionButtonPressed = BlueRead;
      buttonPressed = BLUE_PRESSED;
      colourPressed = LED_BLUE;
      digitalWrite(LED_BLUE, HIGH);
      someButtonPressed = true;
    } 
    if((millis()%1000) == 0) {
     
      delay(50);
    }
  
    else if(someButtonPressed) {
      UsernameSequence[i] = colourPressed;
      if(colourPressed == LED_GREEN)
      Serial.print("G");
      else if(colourPressed == LED_RED)
        Serial.print("R");
      else if(colourPressed == LED_YELLOW)
        Serial.print("Y");
      else if(colourPressed == LED_BLUE)
        Serial.print("B");
      while(ReadConditionButtonPressed == LOW){
        ReadConditionButtonPressed = digitalRead(buttonPressed);
      }
      digitalWrite(colourPressed, LOW);
      if(OriginalSequence[i] != UsernameSequence[i]) {
        leave = true;
        gameOver = true;
        Serial.print("\n\n        --- GAME OVER ---");
      }
      i++;
    }
    if(gameOver) {
      break;
    }
  }
  leave = true;
}
void finalizePlay() {
    lcd.clear();
  lcd.print("   GAME OVER!");
 

  for(int flicker = 0; flicker < 3; flicker++) {
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_YELLOW, HIGH);
    digitalWrite(LED_BLUE, HIGH);
    delay(100);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_BLUE, LOW);
    delay(100);
  }
  //rick roll-simar
  while(song){
  int notelength;
  if (a == 1 || a == 2) {
    // intro
    notelength = beatlength * song1_intro_rhythmn[b];
    if (song1_intro_melody[b] > 0) {
     
      tone(piezo, song1_intro_melody[b], notelength);
    }
    b++;
    if (b >= sizeof(song1_intro_melody) / sizeof(int)) {
      a++;
      b = 0;
      c = 0;
    }
  }
  else if (a == 3 || a == 5) {
    // verse
    notelength = beatlength * 2 * song1_verse1_rhythmn[b];
    if (song1_verse1_melody[b] > 0) {
      
      
      tone(piezo, song1_verse1_melody[b], notelength);
      c++;
    }
    b++;
    if (b >= sizeof(song1_verse1_melody) / sizeof(int)) {
      a++;
      b = 0;
      c = 0;
    }
  }
  else if (a == 4 || a == 6) {
    
    // chorus
    notelength = beatlength * song1_chorus_rhythmn[b];
    if (song1_chorus_melody[b] > 0) {
      
      
      tone(piezo, song1_chorus_melody[b], notelength);
      c++;
    }
    b++;
    if (b >= sizeof(song1_chorus_melody) / sizeof(int)) {
     
      a++;
      b = 0;
      c = 0;
    }
  }
  delay(notelength);
  noTone(piezo);
  
  delay(notelength * beatseparationconstant);
  if (a == 7) { // loop back around to beginning of song
    song = 0;
    //a = 1;
  }
 }
  
}

void finalizePlayGain() {
  for(int n = 0; n < 3; n++){
   
  }
  for (int n = LED_GREEN; n >= LED_BLUE; n--) {
    digitalWrite(n, HIGH);
    delay(80);
    digitalWrite(n, LOW);
  }
  delay(400);
  for (int n = LED_BLUE; n <= LED_GREEN; n++) {
    digitalWrite(n, HIGH);
    delay(80);
    digitalWrite(n, LOW);
  }
}
