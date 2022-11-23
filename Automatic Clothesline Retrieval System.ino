#include <SoftwareSerial.h>
SoftwareSerial sim800l(10,11); // Tx,Rx pins

// stepper motor pins
int stepPin=3;
int dirPin=7;
const int stepsPerRevolution = 3200;

//function to send sms when raining
   void  SendSMSrain()
{
  sim800l.print("AT+CMGF=1\r");                   //Set the module to SMS mode
  delay(100);
  sim800l.print("AT+CMGS=\"+94778176997\"\r");  //Your phone number don't forget to include your country code, example +212123456789"
  delay(500);
  sim800l.print("Raining,clothesline is sent to shelter");       //This is the text to send to the phone number, don't make it too long or you have to modify the SoftwareSerial buffer
  delay(500);
  sim800l.print((char)26);// (required according to the datasheet)
  delay(500);
  sim800l.println();
}

//function to send sms when drying is complete
  void  SendSMSdry()
{
  sim800l.print("AT+CMGF=1\r");                   //Set the module to SMS mode
  delay(100);
  sim800l.print("AT+CMGS=\"+94778176997\"\r");  //Your phone number don't forget to include your country code, example +212123456789"
  delay(500);
  sim800l.print("Clothesline is dry,sent to shelter");       //This is the text to send to the phone number, don't make it too long or you have to modify the SoftwareSerial buffer
  delay(500);
  sim800l.print((char)26);// (required according to the datasheet)
  delay(500);
  sim800l.println();
}


void setup() { 
 
  pinMode(4,INPUT);      //Manual switch
  pinMode(2,INPUT) ;            // LDR CONFIGURATION
  pinMode(A0,INPUT);            // Rain sensor Configuration
  pinMode(A1,INPUT);            // Dryer Moisture Sensor
  pinMode(8,INPUT_PULLUP);      // limitswitch
  pinMode(7,OUTPUT);            //direction pin
  pinMode(3,OUTPUT);            //step pin
 
  sim800l.begin(9600); 
  Serial.begin(9600);
} 




void loop() {

  // read inputs

int ldrState = digitalRead(2);
int rainState=analogRead(A0);
int dryState=analogRead(A1);
int bswitch =digitalRead(4);
int limits=digitalRead(8);

//write limit state
Serial.print("limit State is ");
Serial.println(limits);

 
 if (limits==1){                                                      //CLOTHESLINE IS INSIDE
  
if(ldrState==0 && rainState>500 && dryState>100 && bswitch==0  )       //day,no user,not raining,wet 
{  // write inputs
Serial.print("LDR State is ");
Serial.println(ldrState);
Serial.print("RAIN State is ");
Serial.println(rainState);
Serial.print("DRY State is ");
Serial.println(dryState);
Serial.print("SWICTH State is ");
Serial.println(bswitch);


    digitalWrite(dirPin,LOW);                                // rotate clkwise   // BRING OUT                    
      // Spin the stepper motor 30 revolutions :
  for (int i = 0; i < 30*stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(200);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(200);}
     // Spin the stepper motor 30 revolutions :
  for (int i = 0; i < 30*stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(200);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(200);}
     do {digitalWrite(stepPin, LOW);      //stop motor
    ldrState = digitalRead(2);            // read inputs
    rainState=analogRead(A0);
    dryState=analogRead(A1);
    bswitch =digitalRead(4);
}while(ldrState==0 && rainState>500 && dryState>100 && bswitch==00 ) ;
   }
 }

//read and write limit state
limits=digitalRead(8);
Serial.print("limit State is ");
Serial.println(limits);

 
 
  if (limits==0){                                                    //CLOTHELINE IS OUTSIDE
if(ldrState==0 && rainState<500 && dryState>100 && bswitch==0 )        //day,no user,raining,wet 
  { //write inputs
Serial.print("LDR State is ");
Serial.println(ldrState);
Serial.print("RAIN State is ");
Serial.println(rainState);
Serial.print("DRY State is ");
Serial.println(dryState);
Serial.print("SWICTH State is ");
Serial.println(bswitch);

    digitalWrite(7,HIGH);                                         //anticlkwise          BRING in
// Spin the stepper motor 30 revolutions :
  for (int i = 0; i < 30*stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(200);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(200);} 
    // Spin the stepper motor 30 revolutions :
  for (int i = 0; i < 30*stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(200);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(200);}    
    do
    { digitalWrite(stepPin, LOW);   //stopmotor
    ldrState = digitalRead(2);      //read inputs
 rainState=analogRead(A0);
 dryState=analogRead(A1);
 bswitch =digitalRead(4);}
     while(ldrState==0 && rainState<500 && dryState>100  && bswitch==0);
     SendSMSrain();
  }
  }
    
    
//read and write limit state    
limits=digitalRead(8);
Serial.print("limit State is ");
Serial.println(limits);


      if (limits==0){                                                 //CLOTHELINE IS OUTSIDE
    if(ldrState==0 && rainState>500 && dryState<100 && bswitch==0)       //day,no user,not raining,dry
   { //write inputs
Serial.print("LDR State is ");
Serial.println(ldrState);
Serial.print("RAIN State is ");
Serial.println(rainState);
Serial.print("DRY State is ");
Serial.println(dryState);
Serial.print("SWICTH State is ");
Serial.println(bswitch);

digitalWrite(dirPin,HIGH);                                               //Anticlkwise    BRING IN                  
      // Spin the stepper motor 30 revolutions :
  for (int i = 0; i < 30*stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(200);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(200);}
    // Spin the stepper motor 30 revolutions :
  for (int i = 0; i < 30*stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(200);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(200);}
    SendSMSdry();
    do
     {digitalWrite(stepPin, LOW);
  ldrState = digitalRead(2);
 rainState=analogRead(A0);
 dryState=analogRead(A1);
 bswitch =digitalRead(4);
}while(ldrState==0 && rainState>500 && dryState<100 && bswitch==0);  
 
  }  }
   
   
//read and write limit state  
limits=digitalRead(8);
Serial.print("limit State is ");
Serial.println(limits);
  
    if (limits==0){                                                    //CLOTHELINE IS OUTSIDE
   if(ldrState==0 && rainState<500 && dryState<100 && bswitch==0)       //day,nouser,raining, clothline is dry
   {//write inputs
Serial.print("LDR State is ");
Serial.println(ldrState);
Serial.print("RAIN State is ");
Serial.println(rainState);
Serial.print("DRY State is ");
Serial.println(dryState);
Serial.print("SWICTH State is ");
Serial.println(bswitch);
 digitalWrite(dirPin,HIGH);                                              //Anticlkwise    BRING IN                 
      // Spin the stepper motor 30 revolutions :
  for (int i = 0; i < 30*stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(200);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(200);}
       // Spin the stepper motor 30 revolutions :
  for (int i = 0; i < 30*stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(200);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(200);}
    SendSMSrain(); 
  SendSMSdry(); 
  do
    {digitalWrite(stepPin, LOW);               //stop motor till next condiiton
  ldrState = digitalRead(2);
 rainState=analogRead(A0);
 dryState=analogRead(A1);
 bswitch =digitalRead(4);
}
   while(ldrState==0 && rainState<500 && dryState<100 && bswitch==0);
 
 }}



//read and write limit state
limits=digitalRead(8);
Serial.print("limit State is ");
Serial.println(limits);

    if(limits==00)        {                                                            //CLOTHLINE IS OUT
    if(ldrState==0 &&  bswitch==1)                                                     //day and USER 

  { //write inputs
Serial.print("LDR State is ");
Serial.println(ldrState);
Serial.print("RAIN State is ");
Serial.println(rainState);
Serial.print("DRY State is ");
Serial.println(dryState);
Serial.print("SWICTH State is ");
Serial.println(bswitch);
digitalWrite(dirPin,HIGH);                                                        //Anticlkwise    BRING IN                 
      // Spin the stepper motor 30 revolutions :
  for (int i = 0; i < 30*stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(200);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(200);}
     // Spin the stepper motor 30 revolutions :
  for (int i = 0; i < 30*stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(200);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(200);}
    do {digitalWrite(stepPin, LOW);
   ldrState=digitalRead(2);
   bswitch=digitalRead(4);}
   while(ldrState==0 && bswitch==1 );
   
    
  }}
  


//read and write limit state

limits=digitalRead(8);
Serial.print("limit State is ");
Serial.println(limits);

if (limits==0){                         //CLOTHLINE IS OUTSIDE
  if(ldrState==1)                       //night
   {//write inputs
Serial.print("LDR State is ");
Serial.println(ldrState);
Serial.print("RAIN State is ");
Serial.println(rainState);
Serial.print("DRY State is ");
Serial.println(dryState);
Serial.print("SWICTH State is ");
Serial.println(bswitch);
 digitalWrite(dirPin,HIGH);                        //Anticlkwise    BRING IN                   
      // Spin the stepper motor 30 revolutions :
  for (int i = 0; i < 30*stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(200);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(200);}
     // Spin the stepper motor 30 revolutions :
  for (int i = 0; i < 30*stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(200);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(200);}
     
  do
    {digitalWrite(stepPin, LOW);
    ldrState = digitalRead(2);
 
}
   while(ldrState==1);
   
  }  }


//read and write limit state
limits=digitalRead(8);
Serial.print("limit State is ");
Serial.println(limits);

if(limits==0)                                                           //CLOTHLINE IS OUTSIDE
 {   
  if(ldrState==0 && bswitch==0 && rainState>500  && bswitch==0  )       //day,no user,not raining,wet 
{  Serial.print("LDR State is ");
Serial.println(ldrState);
Serial.print("RAIN State is ");
Serial.println(rainState);
Serial.print("DRY State is ");
Serial.println(dryState);
Serial.print("SWICTH State is ");
Serial.println(bswitch);            
  //NO ACTION STOP MOTOR
do {digitalWrite(stepPin, LOW);      //stop motor
    ldrState = digitalRead(2);         // read inputs
    rainState=analogRead(A0);
    dryState=analogRead(A1);
    bswitch =digitalRead(4);
}
     
    while(ldrState==0 && rainState>500 && dryState>100 && bswitch==0) ;


} }
   
limits=digitalRead(8);
Serial.print("limit State is ");
Serial.println(limits);

if(limits==1) {    //CLOTHLINE IS INSIDE 
  
  if(ldrState==0 && rainState<500 && dryState>0 && bswitch==0)        //day,no user,raining,wet 
  { Serial.print("LDR State is ");
Serial.println(ldrState);
Serial.print("RAIN State is ");
Serial.println(rainState);
Serial.print("DRY State is ");
Serial.println(dryState);
Serial.print("SWICTH State is ");
Serial.println(bswitch);

    //NO ACTION STOP MOTOR
      
    do
    { digitalWrite(stepPin, LOW);   //stopmotor
    ldrState = digitalRead(2);      //read inputs
 rainState=analogRead(A0);
 dryState=analogRead(A1);
 bswitch =digitalRead(4);}
     while(ldrState==0 && rainState<500 && dryState>100 && bswitch==0);
     SendSMSrain();
    
    } }
  
  
   limits=digitalRead(8);
Serial.print("limit State is ");
Serial.println(limits);

if(limits==1) {    //CLOTHLINE IS INSIDE 
  if(ldrState==0 && rainState>500 && dryState<100 && bswitch==0 )       //day,no user,not raining,dry
   { Serial.print("LDR State is ");
Serial.println(ldrState);
Serial.print("RAIN State is ");
Serial.println(rainState);
Serial.print("DRY State is ");
Serial.println(dryState);
Serial.print("SWICTH State is ");
Serial.println(bswitch);
digitalWrite(stepPin, LOW);
//NOACTION STOPMOTOR
    SendSMSdry();
    do
     { 
  digitalWrite(stepPin, LOW);
  
  
 ldrState = digitalRead(2);
 rainState=analogRead(A0);
 dryState=analogRead(A1);
 bswitch =digitalRead(4);
}
  while(ldrState==0 && rainState>500 && dryState<100 && bswitch==0);  
 
}}


    limits=digitalRead(8);
Serial.print("limit State is ");
Serial.println(limits);
if(limits==1) {    //CLOTHLINE IS INSIDE 

if(ldrState==0 && rainState<500 && dryState<100 && bswitch==0)       //day,nouser,raining, clothline is dry
   {Serial.print("LDR State is ");
Serial.println(ldrState);
Serial.print("RAIN State is ");
Serial.println(rainState);
Serial.print("DRY State is ");
Serial.println(dryState);
Serial.print("SWICTH State is ");
Serial.println(bswitch);
 //NOACTION STOPMOTOR
    SendSMSrain(); 
  SendSMSdry(); 
  do
    {
   digitalWrite(stepPin, LOW);
  ldrState = digitalRead(2);
 rainState=analogRead(A0);
 dryState=analogRead(A1);
 bswitch =digitalRead(4);
}
   while(ldrState==0 && rainState<500 && dryState<100 && bswitch==0);}}
 

 limits=digitalRead(8);
Serial.print("limit State is ");
Serial.println(limits);
if(limits==1) {    //CLOTHLINE IS INSIDE 
    if(ldrState==0 && bswitch==1)                                                     //day and USER 

  {Serial.print("LDR State is ");
Serial.println(ldrState);
Serial.print("RAIN State is ");
Serial.println(rainState);
Serial.print("DRY State is ");
Serial.println(dryState);
Serial.print("SWICTH State is ");
Serial.println(bswitch);
digitalWrite(dirPin,LOW);          //NO ACTION STOPMOTOR            
      
    do {
   digitalWrite(stepPin, LOW);
   
   ldrState=digitalRead(2);
   bswitch=digitalRead(4);}
   while(ldrState==0 && bswitch==1);
   
    
  }}
  
  limits=digitalRead(8);
Serial.print("limit State is ");
Serial.println(limits);

if (limits==1){                 //CLOTHLINE IS INSIDE
  if(ldrState==1)                    //night
   {Serial.print("LDR State is ");
Serial.println(ldrState);
Serial.print("RAIN State is ");
Serial.println(rainState);
Serial.print("DRY State is ");
Serial.println(dryState);
Serial.print("SWICTH State is ");
Serial.println(bswitch);
 digitalWrite(dirPin,LOW);          //NO ACTION STOP MOTOR
     
  do
    {
   digitalWrite(stepPin, LOW);
 
  ldrState = digitalRead(2);
 
}
   while(ldrState==1);
   
  }  }

}    

  
  

    
   
 




   
