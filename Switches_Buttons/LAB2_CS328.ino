// LEDS
#define GREEN_LED 9
const int led_builtin = LED_BUILTIN; // AKA pin 13  / red LED
int greenled_state = LOW; // TO::DO change to greenled statr

// TOGGLE FUNCTION
int toggle_button = 10; // Toggle button connected to digital pin 7
int toggleButtonState;
int lastToggleButtonState = HIGH; // Always assume button starts unpressed
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50; // Delay time for all debounces

// HOLD FUNCTION
int hold_button = 5; // Hold button connected to digital pin 5
int holdButtonState;
int lastHoldButtonState = HIGH; // Always assume button starts unpressed
unsigned long lastHoldDebounceTime = 0;

// REST OF THE BUTTONS + SWITCHES
int delay_button = 3; // Delay button connected to digital pin 3
int light_switch = 2; // Light switch connected to digital pin 2

//************************************************************
// Method: setup
// Input: toggle button, hold button, delay button, light switch
// Description: Configure buttons and switch as input, configure
// LEDS as output. Also do the 15 blinks in three seconds startup
// requirement after initial configs. 
//***
void setup() {
  // Delay at start to stabilize board or else the blinking glitches
  delay(1000);
  // configures button pins as input_pullup
  pinMode(toggle_button, INPUT_PULLUP);
  pinMode(hold_button, INPUT_PULLUP);
  pinMode(delay_button, INPUT_PULLUP);
  pinMode(light_switch, INPUT_PULLUP);
  // configures LED pins as output
  pinMode(GREEN_LED, OUTPUT);
  pinMode(led_builtin, OUTPUT);

  // Every reset, check LED
  // at the start, LEDS must flash repeatedly for three seconds at 5 blinks a second
  // total of 15 blinks
  for(int i = 0; i < 15; i++) // 15 * 200 = 3000, this will occur over the span of three seconds
  {
    digitalWrite(GREEN_LED, HIGH); 
    digitalWrite(led_builtin, HIGH);
    delay(100); // five blinks every 1000 seconds
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(led_builtin, LOW);
    delay(100);
  }
}
//************************************************************
// Method: loop
// Input: buttons and switch
// Description: All functions that receive inputs must go here
//***
void loop() {
  processToggleButton(toggle_button);
  processHoldButton(hold_button);
  processDelayButton(delay_button);
  processLightSwitch(light_switch);
}
//************************************************************
// Method: Toggle Button
// Input: toggle button
// Description: When button is pressed, turn green led to the 
// opposite of it's current state. Debouncing is necessary
//***
void processToggleButton(int toggleButton) {
// read the state of toggle button 
  int reading = digitalRead(toggleButton); 
  if (reading != lastToggleButtonState) {    // if the state changed (noise/pressing) start timer
    lastDebounceTime = millis();  
  }
// if longer than set delay, then it'll check the state
  if ((millis() - lastDebounceTime) > debounceDelay) { 
    // if button state has change in that time:
    if (reading != toggleButtonState) {
      toggleButtonState = reading; // set button state back to reading
    // use that state to check if button pressed
    if (toggleButtonState == LOW){           
      greenled_state = !greenled_state; // if button is pressed, update LED state to be opposite
      }
    }
  }
  digitalWrite(GREEN_LED, greenled_state); // write LED with new state
  lastToggleButtonState = reading;           // next iteration will have our button state
} 
//************************************************************
// Method: Hold Button
// Input: hold button
// Description: Read button state, if button is pressed down
// then red LED turns on. When button is let go then red LED
// turns off. Added a debounce to prevent flickering from noise
//***
void processHoldButton(int holdButton){
  // read the state of hold button 
  int reading = digitalRead(holdButton);
  if (reading != lastHoldButtonState){ // if the state changed (noise/pressing) start timer
    lastHoldDebounceTime = millis();  
  }
  // if longer than set delay, then it'll check the state
  if ((millis() - lastHoldDebounceTime) > debounceDelay) { 
    holdButtonState = reading; // set button state back to reading
    // if button state has change in that time:
    if (reading != toggleButtonState) {
      toggleButtonState = reading;
      // Normal Hold button logic
      if(holdButtonState == LOW){ // if button pressed then led turns on
        digitalWrite(led_builtin, HIGH);
      }
      else if(holdButtonState == HIGH){ // else if button let go led turns off
        digitalWrite(led_builtin, LOW);
      }
    }
  }
  lastHoldButtonState = reading;  // next iteration will have our button state
}
//************************************************************
// Method: Delay Button
// Input: None
// Description: If button pressed, turn on lights for five seconds
// Before shutting them off
//***
void processDelayButton(int delayButton){
  int buttonState = digitalRead(delayButton);
  if(buttonState == LOW){ // If button pressed turn LEDS on for five seconds
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(led_builtin, HIGH);
    delay(5000);
    digitalWrite(GREEN_LED, LOW); // after five seconds shut leds off
    digitalWrite(led_builtin, LOW);
  }
}
//************************************************************
// Method: Light Switch
// Input: light switch
// Description: Read the switch state, if switch is flicked on
// turn the LEDS on, if switch is flicked off then turn them off.
//***
void processLightSwitch(int lightSwitch){
  int switchState = digitalRead(lightSwitch);
  if (switchState == LOW){ // if switch turned on
    digitalWrite(GREEN_LED, HIGH); // turn on leds
    digitalWrite(led_builtin, HIGH);
  }
  else{ // else if switch off turn off leds
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(led_builtin, LOW);
  }
}