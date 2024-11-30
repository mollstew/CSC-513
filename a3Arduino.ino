// digit pins
int a=11; 
int b=12; 
int c=10; 
int d=8; 
int e=6; 
int f=9; 
int g=7; 
int dp=13;

// led pins
int smilePin = 4;
int frownPin = 2;
int breathePin = 3;

int brightness = 0; 
int fadeAmount = 3; 

//display number 1
void display1(void) 
{  
    digitalWrite(b,HIGH);
    digitalWrite(c,HIGH);
} 
//display number2
void
  display2(void) 
{
    digitalWrite(a,HIGH);
    digitalWrite(b,HIGH);

    digitalWrite(g,HIGH);
    digitalWrite(e,HIGH);
    digitalWrite(d,HIGH);
}  
// display number3
void display3(void) 
{ 
    digitalWrite(a,HIGH);

    digitalWrite(b,HIGH);
    
    digitalWrite(c,HIGH);
    digitalWrite(d,HIGH);

    digitalWrite(g,HIGH);
} 
// display number4
void display4(void) 
{
  
    digitalWrite(f,HIGH);
    digitalWrite(b,HIGH);
    digitalWrite(g,HIGH);

    digitalWrite(c,HIGH);
  
} 
// display number5
void display5(void)
  
{ 
    digitalWrite(a,HIGH);
    digitalWrite(f,HIGH);
    digitalWrite(g,HIGH);

    digitalWrite(c,HIGH);
    digitalWrite(d,HIGH);
} 
// display number6
void
  display6(void) 
{ 
    digitalWrite(a,HIGH);
    digitalWrite(f,HIGH);

    digitalWrite(g,HIGH);
    digitalWrite(c,HIGH);
    digitalWrite(d,HIGH);
  
    digitalWrite(e,HIGH);  
} 
// display number7
void display7(void)
  
{   
    digitalWrite(a,HIGH);
    digitalWrite(b,HIGH);
    digitalWrite(c,HIGH);
}
  
// display number8
void display8(void) 
{ 
    digitalWrite(a,HIGH);

    digitalWrite(b,HIGH);
    digitalWrite(g,HIGH);
    digitalWrite(c,HIGH);

    digitalWrite(d,HIGH);  
    digitalWrite(e,HIGH);  
    digitalWrite(f,HIGH);
  
} 
void clearDisplay(void) 
{ 
    digitalWrite(a,LOW);
    digitalWrite(b,LOW);

    digitalWrite(g,LOW);
    digitalWrite(c,LOW);
    digitalWrite(d,LOW);  

    digitalWrite(e,LOW);  
    digitalWrite(f,LOW);  
} 
void display9(void)
  
{ 
    digitalWrite(a,HIGH);
    digitalWrite(b,HIGH);
    digitalWrite(g,HIGH);

    digitalWrite(c,HIGH);
    digitalWrite(d,HIGH);  
    digitalWrite(f,HIGH);
  
} 
void display0(void) 
{ 
    digitalWrite(a,HIGH);
    digitalWrite(b,HIGH);

    digitalWrite(c,HIGH);
    digitalWrite(d,HIGH);  
    digitalWrite(e,HIGH);
  
    digitalWrite(f,HIGH);  
} 

void countdown(void){
  clearDisplay();
  display5(); 
  delay(2000); 
  clearDisplay();

  display4(); 
  delay(2000); 
  clearDisplay();

  display3();
  delay(2000); 
  clearDisplay();

  display2(); 
  delay(2000);
  clearDisplay();

  display1(); 
  delay(2000);
  clearDisplay(); 

  display0(); 
  delay(2000);
  clearDisplay();
}



void setup() 
{ 
  pinMode(a,OUTPUT);
  pinMode(b,OUTPUT);
  pinMode(c,OUTPUT);
  pinMode(d,OUTPUT);
  pinMode(e,OUTPUT);
  pinMode(f,OUTPUT);
  pinMode(g,OUTPUT);
  pinMode(dp,OUTPUT);
  pinMode(smilePin,OUTPUT);
  pinMode(frownPin,OUTPUT);
  pinMode(breathePin,OUTPUT);
  Serial.begin(9600);
} 

void loop() 
{   
    if (Serial.available()) {
      String command = Serial.readStringUntil('\n');
      delay(100);

      if (command == "anxious") {
        for (int i = 0 ; i <= 500; i++) {
          analogWrite(breathePin, brightness);
          brightness = brightness + fadeAmount;
          if (brightness <= 0 || brightness >= 255) {
            fadeAmount = -fadeAmount;
          }
          delay(30);
          }
        analogWrite(breathePin, 0);
      } 
        
      else if (command == "bored") {
        digitalWrite(frownPin, HIGH);
        String smileStatus;
        while (smileStatus != "happy"){
          if (Serial.available()){
            smileStatus = Serial.readStringUntil('\n');
            if (smileStatus == "happy"){
              digitalWrite(frownPin, LOW);
              digitalWrite(smilePin, HIGH);
              delay(2000);
              digitalWrite(smilePin, LOW);
            }
          }
        }
      } 
        
      else if (command == "frustrated"){
        countdown();
      }
    }  
}




