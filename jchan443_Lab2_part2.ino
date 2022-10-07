int B[4] = {2, 3, 4, 5};
int PD = 6;
int PU = 7;
enum States {Start, SLOW, MED, MAX} state;
int num = 750;
int delayTime = 250;
int sequenceOrder[9] = {0000, 1000, 1100, 1110, 1111, 1110, 1100, 1000, 0000};
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
  return val && (0x01 << bit);
}
void playLights(int sequence){
  for(int i = 0; i < 4; i++){
    if(getBit(sequenceOrder[sequence], i)){
      digitalWrite(B[i],HIGH);
    }
    else if(!getBit(sequenceOrder[sequence], i)){
      digitalWrite(B[i],LOW);
    }
  }

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

  // put your main code here, to run repeatedly:
  //flash();
  tick();
  int seq = 0;
  playLights(seq);
  if( seq == 9){
    seq = 1;
  }
  seq = seq + 1;
  delay(delayTime);
}