int ledPin = 13;
int sPin = A0;
int read1;


void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(sPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  read1= analogRead(sPin);
  Serial.println(read1);
  if(read1>150){
    digitalWrite(ledPin, 200);
  }
  else{
    digitalWrite(ledPin, 0);
  }
    
}
