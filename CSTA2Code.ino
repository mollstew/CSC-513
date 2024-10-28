
int needle4mm2 = 2;
int needle6mm3 = 3;
int needle5mm4 = 4;
int fineYarn5 = 5;
int bulkyYarn6 = 6;
int mediumYarn7 = 7;
int stockinette8 = 8;
int moss9 = 9;
int basketWeave10 = 10;
int andalusian11 = 11;

int led0 = A5; // scarf   
int led1 = A4; // bag
int led2 = A3; // hat
int led3 = A2; // mitt
int led4 = A1; //sock
int led5 = A0; //shirt
int led6 = 12; //sweater
int led7 = 13; //bear

// Dataset
// {4mm, 5mm, 6mm, fine, medium, bulky, stockinette, moss, basket, andalusian}
// 1 means the pattern contains, 0 means it does not contain

int patterns[8][10] = {
  {0, 1, 0, 0, 0, 1, 0, 0, 0, 1},
  {0, 0, 1, 1, 0, 0, 0, 1, 0, 0},
  {0, 0, 1, 0, 1, 0, 0, 0, 0, 1},
  {0, 1, 0, 0, 1, 0, 0, 0, 1, 0},
  {0, 1, 0, 0, 1, 0, 1, 0, 0, 0},
  {1, 0, 0, 0, 0, 1, 0, 1, 0, 0},
  {0, 0, 1, 1, 0, 0, 0, 0, 1, 0},
  {1, 0, 0, 0, 0, 1, 1, 0, 0, 0}
  };

void setup() {
  pinMode(andalusian11, INPUT_PULLUP);
  pinMode(needle4mm2, INPUT_PULLUP);
  pinMode(needle6mm3, INPUT_PULLUP);
  pinMode(needle5mm4, INPUT_PULLUP);
  pinMode(fineYarn5, INPUT_PULLUP);
  pinMode(bulkyYarn6, INPUT_PULLUP);
  pinMode(mediumYarn7, INPUT_PULLUP);
  pinMode(stockinette8, INPUT_PULLUP);
  pinMode(moss9, INPUT_PULLUP);
  pinMode(basketWeave10, INPUT_PULLUP);

  pinMode(led0, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  pinMode(led7, OUTPUT);
}

void loop() {
  int needle4mm = digitalRead(needle4mm2);
  int needle6mm = digitalRead(needle6mm3);
  int needle5mm = digitalRead(needle5mm4);
  int fineYarn = digitalRead(fineYarn5);
  int bulkyYarn = digitalRead(bulkyYarn6);
  int mediumYarn = digitalRead(mediumYarn7);
  int stockinette = digitalRead(stockinette8);
  int moss = digitalRead(moss9);
  int basketWeave = digitalRead(basketWeave10);
  int andalusian = digitalRead(andalusian11);

  int needleSize[3] = {0, 0, 0};
  int yarnWeight[3] = {0, 0, 0};
  int stitchType[4] = {0, 0, 0, 0};
  int lightMatrix[8] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW};
  int needleActivated = 0;
  int yarnActivated = 0;
  int stitchActivated = 0;
  
  
  // Updating array of needle sizes that are activated
  if (needle4mm == LOW){
    needleSize[0] = 1;
    needleActivated = 1;
  }
  if (needle5mm == LOW){
    needleSize[1] = 1;
    needleActivated = 1;
  }
  if (needle6mm == LOW){
    needleSize[2] = 1;
    needleActivated = 1;
  }

    
  // Updating array of yarn weights that are activated
  if (fineYarn == LOW){
    yarnWeight[0] = 1;
    yarnActivated = 1;
  }
  if (mediumYarn == LOW){
    yarnWeight[1] = 1;
    yarnActivated = 1;
  }
  if (bulkyYarn == LOW){
    yarnWeight[2] = 1;
    yarnActivated = 1;
  }

  // Updating array of stitch types that are activated
  if (stockinette == LOW){
    stitchType[0] = 1;
    stitchActivated = 1;
  }
  if (moss == LOW){
    stitchType[1] = 1;
    stitchActivated = 1;
  }
  if (basketWeave == LOW){
    stitchType[2] = 1;
    stitchActivated = 1;
  }
  if (andalusian == LOW){
    stitchType[3] = 1;
    stitchActivated = 1;
  }

  int activations = 0;
  int matches = 0;

  for (int pattern = 0; pattern < 8; pattern++){
    if (needleActivated == 1){
      activations += 1;
      for (int needle = 0; needle < 3; needle++){
        if (needleSize[needle] == 1 && patterns[pattern][needle] == 1){
          matches += 1;
        }
      }
    }
    if (yarnActivated == 1){
      activations += 1;
      for (int yarn = 0; yarn < 3; yarn++){
        if (yarnWeight[yarn] == 1 && patterns[pattern][yarn+3] == 1){
          matches += 1;
        }
      }
    }
    if (stitchActivated == 1){
      activations += 1;
      for (int stitch = 0; stitch < 4; stitch++){
        if (stitchType[stitch] == 1 && patterns[pattern][stitch+6] == 1){
          matches += 1;
        }
      }
    }
    if (matches == activations && activations > 0){
      lightMatrix[pattern] = HIGH;
    }
    activations = 0;
    matches = 0;
  }    

  digitalWrite(led0, lightMatrix[0]);
  digitalWrite(led1, lightMatrix[1]);
  digitalWrite(led2, lightMatrix[2]);
  digitalWrite(led3, lightMatrix[3]);
  digitalWrite(led4, lightMatrix[4]);
  digitalWrite(led5, lightMatrix[5]);
  digitalWrite(led6, lightMatrix[6]);
  digitalWrite(led7, lightMatrix[7]);
}
