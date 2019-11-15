
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

void at_cmd1(String msg)
{
  go = 0;

  Serial.println("__1__");
  Serial.println(msg);
  Serial1.println(msg);
  
  while(!go){
    tnow = millis();
    if(tnow-onesec > 1000){
      onesec = tnow;
      if(Serial1.available()>0){
        ret = Serial1.readString();
        Serial.println(ret);
        go = 1;
      }
    } 
  }    
}

void at_cmd1_loop(String msg)
{
  go = 0;

  Serial1.print("+++");
  delay(1200);   
  if(Serial1.available()>0){
    ret = Serial1.readString();
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
  

  at_cmd1(msg);
  at_cmd1("ATCN");

}

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(100);
  Serial1.begin(115200);
  Serial1.setTimeout(100);
  
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
      Serial1.print("+++");
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
      if(Serial1.available()>0){
        ret = Serial1.readString();
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


  at_cmd1("ATCE");
  //at_cmd1("ATDH0");
  //at_cmd1("ATDLFFFF"); // BROADCAST
  at_cmd1("ATDH13A200");
  at_cmd1("ATDL415C956F");
  at_cmd1("ATRO0");
  at_cmd1("ATRO3");
  at_cmd1("ATPL0");
  at_cmd1("ATPM0");
  at_cmd1("ATCN");

  while(!digitalRead(ButtonPin));
  delay(2000);
}


char txBuffer[256];

void loop() {
  


  while(digitalRead(intPin));
  tnow = millis();
  sprintf(txBuffer, "%dX", tnow);
  Serial1.print(txBuffer);





  /*
  if(tnow-onesec > 1)
  {
    onesec = tnow;

    sprintf(txBuffer, "%d %dX", cnt++, onesec);
    //sprintf(txBuffer, "%dX", cnt++);

    
    if(digitalRead(intPin)){
      sprintf(txBuffer, "CTS hitX");
      //Serial.print(txBuffer);
      while(digitalRead(intPin));
    }

    while(digitalRead(intPin));
    
    //Serial.print(txBuffer);
    Serial1.print(txBuffer);
    //Serial1.print(cnt, DEC);
    //Serial.println(cnt, DEC);

    //cnt = cnt+1;
  }*/
  

}


