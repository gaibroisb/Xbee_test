
// one maple mini, two xbee's, serial 1 and serial 2


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

void at_cmd2(String msg)
{
  go = 0;

  Serial.println("__2__");
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
  Serial.begin(9600);
  Serial.setTimeout(100);
  Serial1.begin(9600);
  Serial1.setTimeout(100);
  Serial2.begin(9600);
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



  //at_cmd1("ATCE 1");
  at_cmd1("ATCE");
  at_cmd1("ATDH0");
  at_cmd1("ATDLFFFF");
  //at_cmd1("ATDH 13A200");
  //at_cmd1("ATDL 415C956F");
  //at_cmd1("ATRO 0");
  at_cmd1("ATCN");




  go = 0;


  while(!go){
    tnow = millis();
    if(tnow-onesec > 1200){
      onesec = tnow;
      Serial2.print("+++");
      delay(1200);   
      go = 1;
      Serial.println("End setup 2");
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


  //at_cmd2("ATRO 0");
  at_cmd2("ATAI");
  
  at_cmd2("ATDH0");
  at_cmd2("ATDLFFFF");
  //at_cmd2("ATDH 13A200");
  //at_cmd2("ATDL 415C956F");
  at_cmd2("ATCN");


  
/*
  at_cmd1("ATCE 1");
  at_cmd1("ATCE");
  
  at_cmd1("ATSH");
  at_cmd1("ATSL");
  at_cmd1("ATAI");
  at_cmd1("ATDH");
  at_cmd1("ATDL");
  at_cmd1("ATMY");
  at_cmd1("ATSM");

  at_cmd2("ATSH");
  at_cmd2("ATSL");
  at_cmd2("ATAI");
  at_cmd2("ATDH");
  at_cmd2("ATDL");
  at_cmd2("ATMY");
  at_cmd2("ATSM");
*/
  
}



int devicenum = 1;


void loop() {
  tnow = millis();
  
  if(tnow-onesec > 2000){
    onesec = tnow;
    
    Serial1.print(cnt, DEC);
    //Serial2.print(cnt, DEC);
    //Serial.println(cnt, DEC);

    
    //Serial.println("Read one:");
    //ret = Serial1.readString();
    //Serial.println(ret);

    
    //Serial.println("Read two:");
    //ret = Serial2.readString();
    //Serial.println(ret);

    cnt = cnt+1;
  }


  if(tnow-halfsec > 500)
  {
    halfsec = tnow;
  }


  if(Serial1.available()>0){
    Serial.println("Read one:");
    ret = Serial1.readString();
    Serial.println(ret);
  }


  if(Serial2.available()>0){
    Serial.println("Read two:");
    ret = Serial2.readString();
    Serial.println(ret);
  }

  if(Serial.available()>0){

    ret = Serial.readString();
    
    if(ret.equals("1") == 1){
      Serial.println("devicenum 1");
      devicenum = 1;
    }
    else if(ret.equals("2") == 1){
      Serial.println("devicenum 2");
      devicenum = 2;
    }
    else if(devicenum == 1)
    {
      at_cmd1_loop(ret);
    }
    else if(devicenum == 2)
    {
      at_cmd2_loop(ret);
    }

  }
}


