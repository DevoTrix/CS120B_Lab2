int B[4] = {2, 3, 4, 5};
int PD = 6;
int PU = 7;
enum States {Start, OFF, ON} state;
int num = 750;
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
      state = OFF;
      break;
    case OFF:
      if(!digitalRead(PU)){
        state = ON;
      }
      else{
        state = OFF;
      }
      break;
    case ON:
      if(digitalRead(PD)){
        state = OFF;
      }
      else{
        state = ON;
      }
      break;
    default:
      Serial.print("Error");
      break;
  }
  switch(state){
    case OFF:
      turnOff();
      break;
    case ON:
      turnOn();
      break;
    default:
      Serial.print("error");
      break;
  }
}
void turnOn(){
  for(int i = 0; i < 4; i++){
    digitalWrite(B[i], HIGH);
  }
}
void turnOff(){
  for(int i = 0; i < 4; i++){
    digitalWrite(B[i], LOW);
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
}