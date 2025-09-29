//************************************************************
// Week 3 Assignment/Lab 3
// 
// Purpose: To learn how to program a seven-segment display
// as well as writing in parallel
// Name: Audrey Saidel
//************************************************************

// DEFINE SEGMENTS on PORTA
const byte SEG_A  = B00000001;  // D22
const byte SEG_B  = B00000010;  // D23
const byte SEG_C  = B00000100;  // D24
const byte SEG_D  = B00001000;  // D25
const byte SEG_E  = B00010000;  // D26
const byte SEG_F  = B00100000;  // D27
const byte SEG_G  = B01000000;  // D28

// DEFINE BUTTON
int toggle_button = 12; // Button to toggle LED set to pin 12 
int lastToggleButtonState = HIGH; // Assume it starts unpressed
int toggleButtonState;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50; // Delay time for all debounces

// NUMBER OF PRESSES
int num = 0;

// WORD DISPLAYED
String wordChoice = "ASSESS";

//************************************************************
// Method: setup
// Input: toggle_button
// Description: Begin parallel port manipulations
//   using 7 pins in PORT A DD22-D28
//************************************************************
void setup() {
  DDRA = B01111111; // Set ports D22-D28 as outputs for all segments besides decimal
  PORTA = 0; // Display should start off

  // Initialize button
  pinMode(toggle_button, INPUT_PULLUP);
}

//************************************************************
// Method: loop
// Input: toggle_button
// Description: Get toggle button input via function
//   
//************************************************************
void loop() {
  processToggleButton(toggle_button); // Read button input to begin
}

//************************************************************
// Method: displayNumber
// Input: None
// Description: Switch statement that reads the global variable 
//    num and displays correlating number
//    
//************************************************************
void displayNumber()  {
  switch(num){ // increment num as it is a counter for button presses, display up to 9 
    case 0:
    PORTA =  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F; // Display 0
    num++;
    break;

    case 1:
    PORTA = SEG_B | SEG_C; // Display 1
    num++;
    break;

    case 2:
    PORTA = SEG_A | SEG_B | SEG_G | SEG_E | SEG_D; // Display 2
    num++;
    break;

    case 3:
    PORTA = SEG_A | SEG_B | SEG_G | SEG_C| SEG_D; // Display 3
    num++;
    break;

    case 4:
    PORTA = SEG_F | SEG_G | SEG_B | SEG_C; // Display 4
    num++;
    break;

    case 5:
    PORTA = SEG_A | SEG_F | SEG_G | SEG_C | SEG_D; // Display 5
    num++;
    break;

    case 6:
    PORTA = SEG_A | SEG_F | SEG_E | SEG_G | SEG_C | SEG_D; // Display 6
    num++;
    break;

    case 7:
    PORTA = SEG_A | SEG_B | SEG_C; // Display 7
    num++;
    break;

    case 8:
    PORTA = SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G; // Display 8
    num++;
    break;

    case 9:
    PORTA = SEG_F | SEG_G | SEG_B | SEG_C | SEG_A; // Display 9
    num++;
    break;
  }

}

//************************************************************
// Method: displayLetter
// Input: None
// Description: Display letter that is passed into function.
//    Only A, S, and E because of ASSESS
//    Add more letters as needed
//************************************************************
void displayLetter(char letter) {
  switch(letter){
    case 'A':
      PORTA = SEG_A | SEG_F | SEG_B | SEG_C | SEG_G | SEG_E; // display capital A
      break;
    case 'S':
      PORTA = SEG_A | SEG_F | SEG_G | SEG_C | SEG_D; // display capital S
      break;
    case 'E':
      PORTA = SEG_A | SEG_F | SEG_E | SEG_G | SEG_D; // display capital E
      break;
  }
}

//************************************************************
// Method: displayWord
// Input: None
// Description: Iterate through the word and pass each char
//    to display letter. Then add a blank so that viewers can
//    see seperation between letters
//************************************************************
void displayWord(String word) {
  for (int i = 0; word[i] != '\0'; i++) {
    displayLetter(word[i]);   // show letter for one second
    delay(1000);              
    PORTA = 0;                // blank space between letters
    delay(400);               
  }
}

//************************************************************
// Method: processToggleButton
// Input: toggleButton
// Description: Debounce toggle button. If button pressed
//    and verified not noise, either display a number
//    or run through displaying the word
//************************************************************
void processToggleButton(int toggleButton){
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
    if (toggleButtonState == LOW && num < 10){       // if button is pressed and num times pressed less than ten    
        displayNumber(); // display a number 0-9 depending on num times button has been pressed
      }
    else if(toggleButtonState == LOW && num > 9){ // if button is pressed and num times pressed greater than nine
      displayWord(wordChoice); // display word
      num = 0; // reset button presses so user can go again
    }
  }
}
  lastToggleButtonState = reading;           // next iteration will have our button state
} 
