int B[4] = {2, 3, 4, 5};
int PD = 6;
int PU = 7;

int num = 750;
void setup() {

  // put your setup code here, to run once:

  for (int i = 0; i < 4; i++) {
    pinMode(B[i], OUTPUT);
  }
  Serial.begin(9600);
}
int getBit(int val, int k){
  return ((val & (0x01 << k)) != 0);
}
void display(){
  int val = analogRead(A0);
  val = map(val, 0, 1022, 0, 15);
  for(int i = 0; i < 4; i++){
    if(getBit(val, i)){
      digitalWrite(B[i], HIGH);
    } else if(!getBit(val, i)){
      digitalWrite(B[i], LOW);
    }
  }

}
void loop() {

  // put your main code here, to run repeatedly:
  display();
}
