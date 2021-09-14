#include <Servo.h>
#include <LiquidCrystal.h> //include LCD library (standard library)
#include <Keypad.h> //include keypad library - first you must install library (library link in the video description)

#define redLED 10 //define the LED pins
#define greenLED 11
Servo myservo;
int pos = 0; 

char* password ="1234"; //create a password
int pozisyon = 0; //keypad position

const byte rows = 4; //number of the keypad's rows and columns
const byte cols = 4;

char keyMap [rows] [cols] = { //define the cymbols on the buttons of the keypad

    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

byte rowPins [rows] = {7,6,5,4}; //pins of the keypad
byte colPins [cols] = {3,2,1,0};

Keypad myKeypad = Keypad( makeKeymap(keyMap), rowPins, colPins, rows, cols);

LiquidCrystal lcd (A0, A1, A2, A3, A4, A5); // pins of the LCD. (RS, E, D4, D5, D6, D7)

void setup(){

    int pos = 0; 
    lcd.begin(16, 2);
    pinMode(redLED, OUTPUT);  //set the LED as an output
    pinMode(greenLED, OUTPUT);
    setLocked (true); //state of the password
}

void loop(){

    char whichKey = myKeypad.getKey(); //define which key is pressed with getKey

    lcd.setCursor(0, 0);
    lcd.print("    Welcome");
    lcd.setCursor(0, 1);
    lcd.print(" Enter Password");

    if(whichKey == '*' || whichKey == '#' || whichKey == 'A' || whichKey == 'B' || whichKey == 'C' || whichKey == 'D'){
        pozisyon=0;
        setLocked (true);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("  Invalid Key!");
        delay(1000);
        lcd.clear();
    }

    if(whichKey == password [pozisyon]){
        pozisyon ++;
    }

    if(pozisyon == 4){
        setLocked (false);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("*** Verified ***");
        delay(3000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("    Welcome");
        lcd.setCursor(0, 1);
        lcd.print("    Vishank");
        delay(70000);
        lcd.clear();
    }

    delay(100);
}

void setLocked(int locked){
    if(locked){
        for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
            // in steps of 1 degree
            myservo.write(pos);              // tell servo to go to position in variable 'pos'
            delay(15);                       // waits 15ms for the servo to reach the position
        }
        digitalWrite(redLED, HIGH);
        digitalWrite(greenLED, LOW);
    }

    else{
        for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
            myservo.write(pos);              // tell servo to go to position in variable 'pos'
            delay(15);                       // waits 15ms for the servo to reach the position
        }
        digitalWrite(redLED, LOW);
        digitalWrite(greenLED, HIGH);
    }
}

