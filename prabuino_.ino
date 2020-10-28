
/* Vending Machine (also known as the prabuino, less formally) 
    Author: Prabha Singh
    Ardunio Mega 2560
*/

//libraries
#include <LiquidCrystal.h>
#include <Servo.h>
#include <SR04.h>
#include <Keypad.h>

//LCD display pin initialization
LiquidCrystal lcd(27, 28, 29, 30, 31, 32);

//Ultrasonic pin intialization
#define trigPin 6
#define echoPin 7

/*keypad array and info*/
//keypad dimensions
const byte ROWS = 4;
const byte COLS = 4;

//define array for keypad
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}

};

//row col pins
byte rowPins[ROWS] = {52, 51, 50, 49}; // connects to zero --> up 9 8 7 6
byte colPins[COLS] = {48, 47, 46, 45};

//define NewKeyPad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

//autoscroll msg to be fancy
char message[] = {'P', 'L', 'E', 'A', 'S', 'E', ' ', 'I', 'N', 'S', 'E', 'R', 'T', ' ', 'C', 'O', 'I', 'N', ' '};

//other variables
int prevMillis = 0;
int intervalTime = 500;
bool signalRead = false;
String servoActivate = "Null";
const int servo1 = 9;
const int servo2 = 8;
const int servo3 = 10; 
const int servo4 = 11;
const int clockwise = 1700;
int Contrast=75;


void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT); //ULT
  pinMode(echoPin, INPUT);  //ULT
  lcd.begin(16, 2);
  pinMode(servo1, OUTPUT); 
    pinMode(servo2, OUTPUT); 
    pinMode(servo3, OUTPUT);
    pinMode(servo4, OUTPUT); 

        analogWrite(6,Contrast);
}


// ------- MASTER LOOP --------- //
void loop() {

  signalRead = false; //restart

  waitSignal();
  if (signalRead == true) {
    String key = keypadEntry();
    if (key == "A1") {
      //activate respective servo
      lcd.clear();
      lcd.print("Vending...");
      serv1(); // activate servo
      delay(2000);
      lcd.clear();
      //put multiple srvo ifs here later
    }
    else if (key == "A2") {
            lcd.clear();
      lcd.print("Vending...");
      serv2(); // activate servo
      delay(2000);
      lcd.clear();
    }
    else if (key == "B1") {
            lcd.clear();
      lcd.print("Vending...");
      serv3(); // activate servo
      delay(2000);
      lcd.clear();
    }
    else if (key == "B2") {
            lcd.clear();
      lcd.print("Vending...");
      serv4(); // activate servo
      delay(2000);
      lcd.clear();
    }
    
  }

}

// ---- waiting for signal func ---- //

void waitSignal () {

  //lcd waiting state autoscroll
  lcd.autoscroll();
  while (signalRead == false) {
    lcd.setCursor(16, 0);

    /* theory to make sensor faster - NOT TESTED - */
    /* unsigned long currentMillis = millis(); //runtime
    if (currentMillis - prevMillis == intervalTime) {
    prevMillis = currentMillis;  ~ save state of current runtime
     *  say interval 1 = 1000 mills and interval 2 = <100 milis 
     *  if (currentMillis - prevMillis == interval 2) {
     *  activate ultra 
     *  
     *  
     *  
     */
    for (int x = 0; x < sizeof(message) ; x++) {
      lcd.print(message[x]);
      coinSensor(); // if the machien isnt picking up coins, just delete delay
      if (signalRead == true) {
        break;
      }
      delay(200); 
      //maybe leds turned on?
    }
  }
  lcd.noAutoscroll();
  lcd.clear();
  lcd.print("Please Select");
  lcd.setCursor(0,1);
  lcd.print("An Item.");
}




// ---- Ultrasonic Method ---- //
void coinSensor () { // can set return bool to check evry iteration

  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(1);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;

  //coin detected chek (20 cm)
  if (distance >= 20 || distance <= 0) {
    //new LCD prompt and wait for keypad input (make another func or write in here ?)
    //increment certain variable that can be checked  ?  yes
  }
  else {
    signalRead = true;
  }
  //set signal variable back to false
}


// ---- Userinput ---- //
String keypadEntry () {
  char keyPress = customKeypad.waitForKey();
  //checking for 4 possible combinations A1, A2, B1, B2
  switch (keyPress) {
    case 'A': {
        lcd.clear();
        lcd.print(keyPress);
        char keyPress2 = customKeypad.waitForKey();
        switch (keyPress2) {
          case '1':
            lcd.print(keyPress2);
            return ("A1");
            //Servo A activates
            break;
          case '2':
            lcd.print(keyPress2);
            return ("A2");
            //Servo B activates
            break;
        }
        break;
      }
    case 'B': {
        lcd.clear();
        lcd.print(keyPress);
        char keyPress3 = customKeypad.waitForKey();
        switch (keyPress3) {
          case '1':
            lcd.print(keyPress3);
            return ("B1");
            //Servo C activates
            break;
          case '2':
            lcd.print(keyPress3);
            return ("B2");
            //Servo D activates
            break;
        }
        break;
      }
    default: {
        lcd.clear();
        lcd.print("Invalid Option.");
        delay(1000);
        lcd.clear();
        lcd.print("Please try again.");
        delay(2000);
        lcd.clear();
        return ("X");
        break;
      }
  }
}

void serv1 () {  
  for(int i=0; i<57; i++)
    {
    digitalWrite(servo1,HIGH);
    delayMicroseconds(clockwise); 
    digitalWrite(servo1,LOW);
    delay(18.5); // 18.5ms 
    //delay(50); 
    }
    delay(1000); }

void serv2 () {  
  for(int i=0; i<57; i++)
    {
    digitalWrite(servo2,HIGH);
    delayMicroseconds(clockwise); 
    digitalWrite(servo2,LOW);
    delay(18.5); // 18.5ms 
    //delay(50); 
    }
    delay(1000); }
    
void serv3 () {  
  for(int i=0; i<57; i++)
    {
    digitalWrite(servo3,HIGH);
    delayMicroseconds(clockwise); 
    digitalWrite(servo3,LOW);
    delay(18.5); // 18.5ms 
    //delay(50); 
    }
    delay(1000); }


void serv4 () {  
  for(int i=0; i<57; i++)
    {
    digitalWrite(servo4,HIGH);
    delayMicroseconds(clockwise); 
    digitalWrite(servo4,LOW);
    delay(18.5); // 18.5ms 
    //delay(50); 
    }
    delay(1000); }
  
