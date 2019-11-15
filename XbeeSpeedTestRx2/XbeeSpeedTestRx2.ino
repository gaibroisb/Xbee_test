
// two maple mini,  serial 1


int cnt = 2;
int timer = 0;
int inc = 1;
int tnow = 0;
int onesec = 100;
int halfsec = 100;
String ret = "";
String okstr = "OK";
int go = 0;


// Pin definitions
int intPin = 12;  // These can be changed, 2 and 3 are the Arduinos ext int pins
int myLed  = 13;  // Set up pin 13 led for toggling
int ButtonPin = 32;

void at_cmd2(String msg)
{
  go = 0;

  Serial.println("__1__");
  Serial.println(msg);
  Serial2.println(msg);
  
  while(!go){
    tnow = millis();
    if(tnow-onesec > 1000){
      onesec = tnow;
      if(Serial2.available()>0){
        ret = Serial2.readString();
        Serial.println(ret);
        go = 1;
      }
    } 
  }    
}

void at_cmd2_loop(String msg)
{
  go = 0;

  Serial2.print("+++");
  delay(1200);   
  if(Serial2.available()>0){
    ret = Serial2.readString();
    Serial.println(ret);
    go = 1;
    if(ret.equals(okstr)){
      Serial.println("Error - not in command mode");
      return;
    }
  }
  else
  {
    Serial.println("Error2 - not in command mode");
    return;
  }
  

  at_cmd2(msg);
  at_cmd2("ATCN");

}

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(100);
  Serial2.begin(115200);
  Serial2.setTimeout(100);
  
  delay(2000);
  
  Serial.println("Begin");

    
  // Set up the interrupt pin, its set as active high, push-pull
  pinMode(intPin, INPUT);
  digitalWrite(intPin, LOW);
  pinMode(myLed, OUTPUT);
  digitalWrite(myLed, HIGH);

  pinMode(ButtonPin, INPUT);

  
  //Serial.println("Waiting for button");
  //while(!digitalRead(ButtonPin));

  while(!go){
    tnow = millis();
    if(tnow-onesec > 1200){
      onesec = tnow;
      Serial2.print("+++");
      delay(1200);   
      go = 1;
      Serial.println("End setup 1");
      onesec = millis();
    } 
  }
  
  go = 0;

  while(!go){
    tnow = millis();
    if(tnow-onesec > 1000){
      onesec = tnow;
      if(Serial2.available()>0){
        ret = Serial2.readString();
        Serial.println(ret);
        go = 1;
        if(ret.equals(okstr)){
          Serial.println("Error - not in command mode");
          while(1);
        }
      }
    } 
  }

  go = 0;


  at_cmd2("ATCE");
  //at_cmd2("ATDH0");
  //at_cmd2("ATDLFFFF"); // BROADCAST
  at_cmd2("ATDH13A200");
  at_cmd2("ATDL4155F52C");
  at_cmd2("ATRO0");
  at_cmd2("ATBD");
  at_cmd2("ATCN");

  
}

char rxBuffer[256];
uint8_t rxTail = 0;

void loop() {
  
  tnow = millis();
  while(true) {
    int b = Serial2.read();
    
    if (b == -1) {
      break;
    }
    //Serial.println((char)b);
    
    rxBuffer[rxTail++] = b;
    
    if (b == 'X') {
      rxBuffer[rxTail-1] = '\0';
      Serial.println("Read one:");
      Serial.println(rxBuffer);
      rxTail = 0;
    }
  }

}

