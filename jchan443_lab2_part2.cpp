int B[4] = {2, 3, 4, 5};
int PD = 6;
int PU = 7;
int seq = 0;
enum States {Start, SLOW, MED, MAX} state;
int num = 750;
int delayTime = 250;
int sequenceOrder[9] = {0, 0x08, 0x0C, 0x0E, 0x0F, 0x0E, 0x0C, 0x08, 0x00};
void setup() {

  // put your setup code here, to run once:
  state = Start;
  for (int i = 0; i < 4; i++) {
    pinMode(B[i], OUTPUT);
  }
  pinMode(PD,INPUT);
  pinMode(PU,INPUT_PULLUP);
  Serial.begin(9600);
}

void tick(){
  switch(state){
    case Start:
      state = SLOW;
      break;
    case SLOW:
      if(!digitalRead(PU)){
        state = MED;
      }
      else{
        state = SLOW;
      }
      break;
    case MED:
      if(digitalRead(PD)){
        state = SLOW;
      }
      else if(!digitalRead(PU)){
        state = MAX;
      }
      else{
        state = MED;
      }
      break;
    case MAX:
      if(digitalRead(PD)){
        state = MED;
      }
      else{
        state = MAX;
      }
      break;
    default:
      Serial.print("Error");
      break;
  }
  switch(state){
    case SLOW:
      delayTime = 250;
      break;
    case MED:
      delayTime = 750;
      break;
    case MAX:
      delayTime = 1250;
      break;
    default:
      Serial.print("error");
      break;
  }
}
int getBit(int val, int bit){
  return ((val & (0x01 << bit)) != 0);
}


void playLights(){
  //tick();
  seq++;
  char cur = sequenceOrder[seq];
  for(int i = 0; i < 4; i++){
    tick();
    Serial.print(delayTime);
    Serial.print("\n");
    if(getBit(cur, i)){      
      digitalWrite(B[i],HIGH);
      delay(delayTime);
    }
    else if(!getBit(cur,i)){
      digitalWrite(B[i],LOW);
      delay(delayTime);
    }
  }
  //tick();
  if(seq >= 8){
    seq = 0;
  }  // for(int i = 0; i < 4; i++){
  //   digitalWrite(B[i],HIGH);
  // }
  // delay(delayTime);
  // for(int i = 0; i < 4; i++){
  //   digitalWrite(B[i],LOW);
  // }
}
// void flash() {
//     for (int i = 0; i < 4; i++) {
//       digitalWrite(B[i], HIGH);
//     }
//     delay(500);
//     for (int i = 0; i < 4; i++) {
//       digitalWrite(B[i], LOW);
//     }
//     delay(500);
//     Serial.println(analogRead(A0));
// }
void loop() {
  //tick();

  // put your main code here, to run repeatedly:
  //flash();
  
  //tick();
  playLights();
  //tick();
}
