
button createButton(int inputPin,int ledPin, char outputKey)
{
  button newButton;
  newButton.pin = inputPin;
  newButton.key = outputKey;
  newButton.ledPin = ledPin;
  newButton.state = LOW;
  newButton.lastState = LOW;
  newButton.lastDebounce = 0;
  return newButton;
  
}
void displayPinNumber(button Button)
{
  Serial.println(Button.pin);
}
/*
 * Returns buttonState to buttonState array in main
 * probably won't work for LED state yet
 */
int debounce(button Button)
{
  int Reading = digitalRead(Button.pin);
  if (Reading != Button.lastState)
  {
    Button.lastDebounce = millis();
  
  }
  if((millis() - Button.lastDebounce)> debounceDelay)
  {
    if(Reading !=Button.state)
    {
      Button.state = Reading;
    }
  }
  Button.lastState = Reading;
  return Button.state;
}
char getKey(button Button)
{
  char outputKey = Button.key;
  return outputKey;
}
int getLedPin(button Button)
{
  return Button.ledPin;
}
