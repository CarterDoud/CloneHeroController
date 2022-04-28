#include <Keyboard.h>
#include <Joystick.h>
Joystick_ Joystick;

const char greenKey = 'u';
const char redKey = 'v';
const char yellowKey = 'a';
const char blueKey = 'q';
const char orangeKey = 'e';
const char strum0Key = 'z';
const char strum1Key = 'x';
const char starKey = 's';
const char startKey = 'f';
typedef struct LED
{
  const int pin;
  int state = LOW;
};

typedef struct button
{
  int pin; 
  int state;
  int lastState; 
  int ledPin; //pin number for LED, set to -1 if button does not have LED
  char key; //output key
  unsigned long lastDebounce = 0;
};

const unsigned long debounceDelay = 50;
button buttonArray[9];
int stateArray[9];

void setup() 
{
  Serial.begin(9600);
  //while(!Serial);
  Joystick.begin();
  button button0 = createButton(2,3,'u');
  button button1 = createButton(4,5,'v');
  button button2 = createButton(7,6,'a');
  button button3 = createButton(8,10,'q');
  button button4 = createButton(12,11,'e');
  button buttonStrum0 = createButton(0,-1,strum0Key);
  button buttonStrum1 = createButton(1,-1,strum1Key);
  button buttonStar = createButton(9,-1,starKey);
  button buttonStart = createButton(13,-1,startKey);
  
  buttonArray[0] = button0;
  buttonArray[1] = button1;
  buttonArray[2] = button2;
  buttonArray[3] = button3;
  buttonArray[4] = button4;
  buttonArray[5] = buttonStrum0;
  buttonArray[6] = buttonStrum1;
  buttonArray[7] = buttonStar;
  buttonArray[8] = buttonStart;
}

void loop() 
{
  int whammyPot = analogRead(A0);
  for (int i=0; i<9;i++)
  {
    stateArray[i] = debounce(buttonArray[i]);
  }
  for (int i=0;i<9;i++)
  {
    if(stateArray[i] == HIGH)
    {
      if (getLedPin(buttonArray[i]) != -1)
      {
        digitalWrite(getLedPin(buttonArray[i]), HIGH);
      }
      Keyboard.press(getKey(buttonArray[i]));
    }
    else
    {
      if (getLedPin(buttonArray[i]) != -1)
      {
        digitalWrite(getLedPin(buttonArray[i]), LOW);
      }
      Keyboard.release(getKey(buttonArray[i]));
    }
  }
  Joystick.setYAxis(whammyPot);
}
