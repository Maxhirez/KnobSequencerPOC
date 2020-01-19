//TODO: TEST THIS.
const byte clockPin = 2;
const byte writePin = 3;
int sensorValue, lastsensorValue;
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  //RESET is connect-to-low 
  //writePin is all on-board, so we can take it low to trigger
  pinMode(writePin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(writePin), writeRoutine,  FALLING);
  //clockPin will take a Eurorack rising voltage, so it doesn't use 
  //INPUT_PULLUP and it triggers on the rising voltage
  attachInterrupt(digitalPinToInterrupt(clockPin), clockRoutine, RISING);
}

// the loop routine runs over and over again forever:
void loop() {
  sensorValue = analogRead(A0);
  // print out the value you read:
  if(sensorValue!=lastsensorValue){
    Serial.println(sensorValue);
    lastsensorValue=sensorValue;
  }
  delay(1);        // delay in between reads for stability
}
void clockRoutine(){
  Serial.println("Clock Recieved.");
}

void writeRoutine(){
  Serial.println("Write Recieved.");
}
