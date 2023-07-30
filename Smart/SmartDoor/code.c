
ML BASED DOOR LOCK SECURITY SYSTEM
CODE :

#include <Keypad.h>
#define buzzpin 11
#define led 13
#define DEBUG
#include <LiquidCrystal.h>

#include<LiquidCrystal.h>
LiquidCrystal lcd(A0,A1,A2,A3,A4,A5);
////////////////////////////////////////////////////////////////////////////////
int sensor = 10; // Pir Sensor 
const byte ROWS =4;
const byte COLS = 4;
char hexakeys[ROWS][COLS]={
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS]={9,8,7,6};
byte colPins[COLS]={5,4,3};
Keypad customkeypad =Keypad(makeKeymap(hexakeys),rowPins,colPins,ROWS,COLS);
char data[] = "    ";  
int sequenceNum = 0;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() 
{
    #ifdef DEBUG
    Serial.begin(9600);
    #endif
    pinMode(buzzpin, OUTPUT);
    pinMode(sensor, INPUT);
    pinMode(led,OUTPUT);
    lcd.begin(16,2);
    lcd.print("DoorlockSecurity");
    delay(2000);
    lcd.clear();
    Serial.println("-----------------------------------------This is keypad Connected Door Lock Security System------------------------------------------ ");
    Serial.println("---------------------------------------------------------LET'S  START---------------------------------------------------------------");
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int flag=1;
int f=1;
int fg=1;
void loop() 
  {
    if(digitalRead(sensor)==HIGH)
    {
       if(flag==1){
       lcd.print("SOMEONE IS HERE");
       delay(100);
       lcd.clear();
       Serial.println("-------------------------------------------------------SOMEONE IS HERE-------------------------------------------------------------"); 
       flag=0;
       }
       digitalWrite(led,HIGH);
       delay(20);
       digitalWrite(led,LOW);
       digitalWrite(buzzpin,HIGH);
       delay(20);
       digitalWrite(buzzpin,LOW);
       
       
       
       if(sensor ==HIGH)
          sensor=LOW;
       digitalWrite(buzzpin,LOW);
    }
     char key = customkeypad.getKey();
    
     if (key != NO_KEY)
     {
          if(f==1)
          {
            Serial.print("ENTER PASSWORD -- ");
            lcd.print("ENTER PASSWORD -- ");
            delay(1000);
            lcd.clear();
            f=0;
          }
          Serial.print(key);
          //delay (10);
     }
     if (key)
     {
        data[sequenceNum] = key;
        sequenceNum++;

        if (sequenceNum == 4){
            #ifdef DEBUG
            Serial.println("  ");
            Serial.println(F("PASSWORD ENTERED --  "));
            Serial.println(data);
            #endif
            if(strcmp(data, "2341") == 0)
            { 
              
              Serial.println("-------------------------------------------------PASSWORD IS CORRECT-----------------------------------------------------------");
              
              lcd.print("CORRECT PASSWORD ");
              delay(1000);
              lcd.clear();
              digitalWrite(led,LOW);
              if(fg==1)
              {
                digitalWrite(buzzpin,LOW);  
              }           
              Serial.println("-------------------------------------------------BUZZER IS DISABLED------------------------------------------------------------");
              Serial.println("------------------------------------------------------DOOR OPEN----------------------------------------------------------------");
              lcd.print("DOOR OPENED ");
              delay(2000);
              lcd.clear();
              Serial.println("---------------------------------------------------YOU CAN STEP IN--------------------------------------------------------------");
              lcd.print("LET'S GO");
              delay(2000);
              lcd.clear();
              lcd.print(" THANK YOU ");
              delay(20000);
              lcd.clear();
              
            }
            else 
            {
            Serial.println("WRONG PASSWORD--   ");
            
            Serial.println("------------------------------------------------YOUR PASSWORD IS INCORRECT---------------------------------------------------------");
            digitalWrite(led,HIGH);
            digitalWrite(buzzpin,HIGH);
            lcd.print("WRONG PASSWORD ");
            delay(1000);
            Serial.println("ENTER PIN AGAIN --    ");
            lcd.clear();
            lcd.print("ENTER PIN AGAIN ");
            delay(2000);
            lcd.clear();
            
       }
        
      memset(data, 0, sizeof(data));
      sequenceNum = 0;
    }
    }   
}
