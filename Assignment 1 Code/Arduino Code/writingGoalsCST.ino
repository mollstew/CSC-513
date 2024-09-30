
int redLed = 9;
int yellowLed = 6;
int greenLed = 3;

float wordCount = -1;  // current words typed
float wordGoal = -1;   // word goal set by user
float percentage = 0 ;
float pythonNum;

int brightness = 255;
int brightnessChange = 80; 

void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    String pythonStr = Serial.readString();

    if (pythonStr.substring(0, 1) == "G") {  // G notifies that the value from serial is the word goal
      wordGoal = pythonStr.substring(1).toInt();
    } else if (pythonStr == "B") {  // Brighten light to reward meeting wpm
      if (brightness < 255) {
        brightness += brightnessChange;
      }
    } else if (pythonStr == "D") {  // Dim light to signfy failure to meet wpm
      if (brightness > 80) {
        brightness -= brightnessChange;
      }
    } else {
      wordCount = pythonStr.toInt();
    }
  }

  if (wordGoal != -1 && wordCount != -1) {  // only turn on lights once user input has been collected

    percentage = (wordCount / wordGoal) * 100;  // percentage of goal that is complete
    
    //Display a different colour depending on percentage
    if (percentage <= 33) {
      analogWrite(redLed, brightness);
      analogWrite(yellowLed, 0);
      analogWrite(greenLed, 0);
    } else if (percentage <= 66) {
      analogWrite(yellowLed, brightness);
      analogWrite(redLed, 0);
      analogWrite(greenLed, 0);
    } else if (percentage < 100) {
      analogWrite(greenLed, brightness);
      analogWrite(yellowLed, 0);
      analogWrite(redLed, 0);
    } else {
      // goal is complete
      int brightness1 = 255;
      int brightness2 = 100;
      int brightness3 = 50;
      analogWrite(redLed, brightness1);
      analogWrite(yellowLed, brightness1);
      analogWrite(greenLed, brightness3);
      delay(200);
      analogWrite(redLed, brightness2);
      analogWrite(yellowLed, brightness2);
      analogWrite(greenLed, brightness3);
      delay(200);
      }
  }
}
