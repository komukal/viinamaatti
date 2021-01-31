int enablePin[] = {0,2,4,6,8,10,12};
int stepPin[] =   {0,3,5,7,9,11,13};
int caseVal;
int endstop;
int carriagePosition=0;
String commandLength;
String command;
const int statusLed = A5;
int x;


// CARRIAGE PINS
const int carriageEnable = A0;
const int carriageDir = A1;
const int carriageStep = A2;

// PUMP 0
const int pump0enable = 2;
const int pump0step = 3;
// PUMP 1 
const int pump1enable = 4;
const int pump1step = 5;
// PUMP 2
const int pump2enable = 6;
const int pump2step = 7;
// PUMP 3
const int pump3enable = 8;
const int pump3step = 9;
// PUMP 4
const int pump4enable = 10;
const int pump4step = 11;
// PUMP 5
const int pump5enable = 12;
const int pump5step = 13;

void setup() {
    
    Serial.begin(9600); 
    delay(2000);  
 
    Serial.println("Viinamaatti online!");


  
 // // Status led
 pinMode(statusLed, OUTPUT);

  
  // CARRIAGE 
  
  pinMode(carriageEnable, OUTPUT);
  pinMode(carriageDir, OUTPUT);
  
 pinMode(carriageStep, OUTPUT);
 
  // PUMP 1 SETUP
  pinMode(pump0enable, OUTPUT);
  pinMode(pump0step, OUTPUT);
  
  // PUMP 2 SETUP
  pinMode(pump1enable, OUTPUT);
  pinMode(pump1step, OUTPUT);
  
  // PUMP 3 SETUP
  pinMode(pump2enable, OUTPUT);
  pinMode(pump2step, OUTPUT);
  
  // PUMP 4 SETUP
  pinMode(pump3enable, OUTPUT);
  pinMode(pump3step, OUTPUT);

  // PUMP 5 SETUP
  pinMode(pump4enable, OUTPUT);
  pinMode(pump4step, OUTPUT);

    // PUMP 6 SETUP
  pinMode(pump5enable, OUTPUT);
  pinMode(pump5step, OUTPUT);
  
  
}


void loop() {
        
        command = Serial.readStringUntil('\n');

        if(command.length()>=2 && command.length() <=12 && command.length()%2==0){
          Serial.println("valid");
          int pours = command.length();
          createDrink(pours,command);
          

          
          command="";
          

        }else{

          if(command.equals("clean")){
             
            clean();
        
          }else if(command.equals("move")){
            moveCarriage(4300);
          }
          
        
            command="";

           }
    
    }



        
     /*/     if(command.length){
              dispenseDrink(0,4);
              Serial.println("200");

              
        }else if(command.equals("move")){
          //4300 max steps for ranges
          moveCarriage(530);
        }
        else{
            Serial.println("Invalid command");
        }
        */
    





// FUNCTIONS !!!!!!
void homecarriage(){
  int movehome=0-carriagePosition;
  Serial.print(movehome);
  Serial.println(" steps to home");
  moveCarriage(movehome);
  carriagePosition=0;
  Serial.println("Home");
}

void clean(){
  homecarriage();
  createDrink(12,"162636465666");
  homecarriage();
  
}


void createDrink(int pours, String recipe){

  for(int x=0; x<pours;x+=2){
     
      //move carriage to drink position      
      int pos = (int) recipe.charAt(x);
      pos=pos-48;
      
      carriagePos(pos);
      delay(1000);
      //dispense the drink
      int cl = (int) recipe.charAt((x+1));
      cl = cl-48;
      dispenseDrink(pos,cl);
      
      
    
  }

  homecarriage();

  
}


void dispenseDrink(int pumpNo, int centiliters){
  int steps = centiliters * 3000;
  Serial.print("dispensing : ");
  Serial.println(centiliters);
  
  digitalWrite(statusLed,LOW);
  digitalWrite(enablePin[pumpNo],HIGH);
  delay(1000);

     for(int x = 0; x < steps; x++)  {
    digitalWrite(stepPin[pumpNo],HIGH); 
    delayMicroseconds(590); 
    digitalWrite(stepPin[pumpNo],LOW); 
    delayMicroseconds(590); 
  }
  digitalWrite(enablePin[pumpNo],LOW);
  delay(1000);
  digitalWrite(statusLed,HIGH);
}

void carriagePos(int position){
  
  int positions[] = {0, 1230, 1845, 2460, 3075, 3690, 4300};
  

  int steps = positions[position]-carriagePosition;
  Serial.print("Moving to position: ");
  Serial.print(position);
  moveCarriage(steps);
  carriagePosition=positions[position];
}


void moveCarriage(int steps){
      digitalWrite(A0,HIGH);
    digitalWrite(statusLed,LOW);
    if(steps<0){
      digitalWrite(A1,HIGH);
      steps=steps*-1;

    }else{
       digitalWrite(A1,LOW);
    }
    steps=steps*4;


     for(int x = 0; x < steps; x++) {
    digitalWrite(A2,HIGH); 
    delayMicroseconds(400); //1000 original
    digitalWrite(A2,LOW); 
    delayMicroseconds(400); 
  }
  digitalWrite(A0 ,LOW);
  delay(500);
  digitalWrite(statusLed,HIGH);
}
