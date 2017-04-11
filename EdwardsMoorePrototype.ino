#include <Streaming.h>

#include "Wire.h"
#include "BlinkM_funcs.h"


int pirSensorA = 2;
int pirSensorB = 5;
int pirSensorC = 6;

int sensorValueA = 0;
int sensorValueB = 0;
int sensorValueC = 0;

int sensorBHits = 0;

boolean isPlaying = false;
boolean isPlayingB = false;
boolean isPlayingC = false;
boolean playingBonus = false;

int scriptIndex = 0;
int activeColor[3];
int colors1[]= {0x00, 0x96, 0xFF};
int colors2[]= {0xFF, 0xFF, 0x00};
int colors3[]= {255, 75,  0};
int colors4[]= {255, 130,  0};
int numberOfHits = 0;


int blinkm_addr = 0x09;
unsigned long startTime;
unsigned long endTime;
unsigned long totalTime;



void setup()
{
  Serial.begin(19200);
  Serial.println("Warming up....");
  BlinkM_beginWithPower();
  delay(100);
  Serial.println("BlinkMSensor ready");
  Serial.println("Scanning I2C bus from 1-100:");
  BlinkM_scanI2CBus(1,5, scanfunc);
  Serial.println(); 
 
  delay(100);
  resetLEDs();
}

void scanfunc( byte addr, byte result ) {
  Serial.print("BlinkM at Channel: ");
  Serial.print(addr,DEC);
  Serial.print( (result==0) ? " found!":"       ");
  Serial.print( (addr%5) ? "\t":"\n");
}

void initLEDControler(int blinkm_addr)
{
  BlinkM_off(blinkm_addr);
  BlinkM_setFadeSpeed(blinkm_addr, 0x09);
  Serial << "Initalized controller at Channel " << blinkm_addr << " complete." <<endl;
}

void resetLEDs()
{
  BlinkM_stopScript(1);
  BlinkM_stopScript(2);
  BlinkM_stopScript(3);
  BlinkM_stopScript(4);
  BlinkM_stopScript(5);
  BlinkM_setRGB(1, 0,0,0);
  BlinkM_setRGB(2, 0,0,0);
  BlinkM_setRGB(3, 0,0,0);
  BlinkM_setRGB(4, 0,0,0);
  BlinkM_setRGB(5, 0,0,0);
  BlinkM_setFadeSpeed(1, 0x09);
  BlinkM_setFadeSpeed(2, 0x09);
  BlinkM_setFadeSpeed(4, 0x09);
  BlinkM_setFadeSpeed(3, 0x09);
  BlinkM_setFadeSpeed(5, 0x09);   
}


void loop()
{
  sensorValueA = digitalRead(pirSensorA);
  sensorValueB = digitalRead(pirSensorB);
  sensorValueC = digitalRead(pirSensorC);  
  
  if (sensorValueA == 1)
  { 
    if (playingBonus)
    {
      return;
    }    
    if (numberOfHits >= 100)
    {
      resetLEDs(); 
      startScriptD();  
    }
    else
    {
       resetLEDs(); 
       startScriptA();  
    }
  }
  if (sensorValueB == 1)
  {
    resetLEDs();
    startScriptB();                 
  }

  
  if (sensorValueC == 1)
  {
    resetLEDs();
    startScriptC();                 
  }
 
}

void startScriptA()
{
 
  if (isPlaying == false)
  {
      startTime = millis();  
      isPlaying = true;
      numberOfHits ++;  
      BlinkM_fadeToRGB(1, 248, 156, 28);  //1  - 1 Start Orange
      delay(750);
      BlinkM_fadeToRGB(1, 0, 0, 0);
      BlinkM_fadeToRGB(2, 255, 165, 10); //2   - 2
      delay(750);
      BlinkM_fadeToRGB(2, 0, 0, 0);
      BlinkM_fadeToRGB(3, 255, 175, 15); //3    - 3
      delay(750);
      BlinkM_fadeToRGB(3, 0, 0, 0);
      BlinkM_fadeToRGB(4, 255, 190, 10); //4    - 4  
      delay(750);
      BlinkM_fadeToRGB(4, 0, 0, 0);
      BlinkM_fadeToRGB(5, 255, 202, 5);//5    - 5 Yellow
      delay(750);
      BlinkM_fadeToRGB(5, 0, 0, 0);
      BlinkM_fadeToRGB(4, 204, 192, 20); //6   - 4
      delay(750);
      BlinkM_fadeToRGB(4, 0, 0, 0);
      BlinkM_fadeToRGB(3, 153, 182, 45); //7   - 3
      delay(750);
      BlinkM_fadeToRGB(3, 0, 0, 0);
      BlinkM_fadeToRGB(2, 102, 175, 60); // 8    - 2 
      delay(750);
      BlinkM_fadeToRGB(2, 0, 0, 0);
      BlinkM_fadeToRGB(3, 61, 175, 73); // 9  - 3 Green
      delay(750);
      BlinkM_fadeToRGB(3, 0, 0, 0);
      BlinkM_fadeToRGB(4, 0, 192, 63); // 10  - 4
      delay(750);
      BlinkM_fadeToRGB(4, 0, 0, 0);
      BlinkM_fadeToRGB(5, 0, 187, 129); // 11  - 5
      delay(750);
      BlinkM_fadeToRGB(5, 0, 0, 0);
      BlinkM_fadeToRGB(4, 0, 185, 192); // 12   - 4 
      delay(750);
      BlinkM_fadeToRGB(4, 0, 0, 0);
      BlinkM_fadeToRGB(3, 0, 182, 237); // 12   - 3 Blue
      delay(750);
      BlinkM_fadeToRGB(3, 0, 0, 0);
      BlinkM_fadeToRGB(4, 66, 187, 192); // 14  - 4
      delay(750);
      BlinkM_fadeToRGB(4, 0, 0, 0);
      BlinkM_fadeToRGB(5, 129, 192, 129); // 15  - 5
      delay(750);
      BlinkM_fadeToRGB(5, 0, 0, 0);
      BlinkM_fadeToRGB(4, 192, 197, 66); // 16   - 4
      delay(750);
      BlinkM_fadeToRGB(4, 0, 0, 0);
      BlinkM_fadeToRGB(5, 255, 202, 5); // 17   - 5 Yellow
      delay(750);
      BlinkM_fadeToRGB(5, 0, 0, 0);      
      isPlaying = false; 
      Serial << "Number of hits: " << numberOfHits << endl;
      
  }
  else
  {
      endTime = millis();
      totalTime = endTime - startTime;
      int numOfSeconds = totalTime / 1000;
      Serial << "Number of Seconds: " << numOfSeconds << endl; 
      if (numOfSeconds >= 13) 
      {
          Serial << "Sequence Complete after: " << numOfSeconds << "seconds" << endl;
          isPlaying = false;
      }
  }  
}

void startScriptB()
{
  if (isPlayingB == false)
  {
    isPlayingB = true;
    int r ;
    int g ;
    int b ;
    
    switch(sensorBHits)
    {
      case 0:
          r = colors1[0];
          g = colors1[1];
          b = colors1[2];
      break; 
      case 1:
          r = colors2[0];
          g = colors2[1];
          b = colors2[2];
      break;
      case 2:
          r = colors3[0];
          g = colors3[1];
          b = colors3[2];      
          break; 
      case 4:
          r = colors4[0];
          g = colors4[1];
          b = colors4[2];      
          break;    
    }

    resetLEDs();
    
    blinkm_script_line sequence3[] = 
    {
      
      { 30, {'n', r, g, b}},          // color
      { 15, {'c', 0x00,0x00,0x00}},   // Fade Off 
      { 135, {'c', 0x00,0x00,0x00}},   // OFF
      { 30, {'n', r, g, b}},          // color
      { 15, {'c', 0x00,0x00,0x00}},    // Fade Off
      { 1, {'c', 0x00,0x00,0x00}},    // off   
    };
    
    blinkm_script_line sequence2_4[] = 
    {
 
      { 45, {'n', 0x00,0x00,0x00}},  // OFF
      { 30, {'n', r, g, b}},  // blue
      { 15, {'c', 0x00,0x00,0x00}},  // fade off
      { 45, {'c', 0x00,0x00,0x00}},  // off
      { 30, {'n', r, g, b}},  // BLUE
      { 15, {'c', r, g, b}},  // fade off
      { 1, {'c', 0x00,0x00,0x00}},  // off   
    };
    
    blinkm_script_line sequence1_5[] = 
    { 
      { 90, {'c', 0x00,0x00,0x00}},  // OFF
      { 30, {'n', r, g, b}},         // blue
      { 15, {'c', 0x00,0x00,0x00}},  // Fade Off
      { 1, {'c', 0x00,0x00,0x00}},   // off   
    };
    
    BlinkM_writeScript( 1, 0, 4, 1,  sequence1_5 ); 
    BlinkM_writeScript( 2, 0, 7, 1,  sequence2_4 ); 
    BlinkM_writeScript( 3, 0, 6, 1,  sequence3 ); 
    BlinkM_writeScript( 4, 0, 7, 1,  sequence2_4 ); 
    BlinkM_writeScript( 5, 0, 4, 1,  sequence1_5 );
  
    delay(100);
    
    BlinkM_playScript(3, 0, 1, 0);
    BlinkM_playScript(2, 0, 1, 0);
    BlinkM_playScript(4, 0, 1, 0);
    BlinkM_playScript(1, 0, 1, 0);
    BlinkM_playScript(5, 0, 0, 0);
    delay(5000);
    isPlayingB = false;
    sensorBHits ++;
    if (sensorBHits >=4)
    {
      sensorBHits = 0;
    }
  }
}

void startScriptC()
{
  blinkm_script_line sequence1[] = 
    {
      { 1, {'f', 100, 0, 0}}, 
      { 30, {'c', 255, 202, 5}},          // color
      { 30, {'c', 243, 134, 32}},
      { 30, {'c', 0,116,150}},
      { 30, {'c', 0,182,237}}, 
      { 30, {'c', 248,156,28}},   // Fade Off 
      { 30, {'c', 0,140,61}},
      { 30, {'c', 61,175,73}},   // OFF
      { 30, {'c', 0x00,0x00,0x00}},    // Fade Off
      { 1, {'c', 0x00,0x00,0x00}},    // off   
    };
    
    blinkm_script_line sequence2[] = 
    {
      { 1, {'f', 100, 0, 0}}, 
      { 30, {'c', 248,156,28}},   // Fade Off 
      { 30, {'c', 0,140,61}},
      { 30, {'c', 255, 202, 5}},          // color
      { 30, {'c', 243, 134, 32}}, 
      { 30, {'c', 61,175,73}},   // OFF
      { 30, {'c', 0,116,150}},
      { 30, {'c', 0,182,237}},
      { 30, {'c', 0x00,0x00,0x00}},    // Fade Off
      { 1, {'c', 0x00,0x00,0x00}},    // off   
    };
    
     blinkm_script_line sequence3[] = 
    {
      { 1, {'f', 100, 0, 0}}, 
      { 30, {'c', 0,116,150}},
      { 30, {'c', 0,182,237}},
      { 30, {'c', 248,156,28}},   // Fade Off 
      { 30, {'c', 0,140,61}},
      { 30, {'c', 255, 202, 5}},          // color
      { 30, {'c', 243, 134, 32}}, 
      { 30, {'c', 61,175,73}},   // OFF
      { 30, {'c', 0x00,0x00,0x00}},    // Fade Off
      { 1, {'c', 0x00,0x00,0x00}},    // off   
    };
    
    
  if (isPlayingC == false)
  {
     BlinkM_writeScript( 1, 0, 9, 1,  sequence1 ); 
     BlinkM_writeScript( 2, 0, 9, 1,  sequence3 ); 
     BlinkM_writeScript( 3, 0, 9, 1,  sequence2 ); 
     BlinkM_writeScript( 4, 0, 9, 1,  sequence1 ); 
     BlinkM_writeScript( 5, 0, 9, 1,  sequence2 );
     isPlayingC = true;
     BlinkM_playScript(3, 0, 1, 0);
     BlinkM_playScript(2, 0, 1, 0);
     BlinkM_playScript(4, 0, 1, 0);
     BlinkM_playScript(1, 0, 1, 0);
     BlinkM_playScript(5, 0, 1, 0); 
     delay(8000);
     resetLEDs();
     isPlayingC = false;   
  }    
}

void  startScriptD()
{
  playingBonus = true;
  blinkm_script_line sequence1[] = 
    {
      { 1, {'f', 50, 0x00, 0x00}}, 
      { 15, {'n', 255, 0x00, 255}},        // color
      { 150, {'c', 0x00,0x00,0x00}},   // Fade Off 
      { 1, {'c', 0x00,0x00,0x00}},    // off   
    };
    BlinkM_writeScript( 1, 0, 3, 1,  sequence1 ); 
    BlinkM_writeScript( 2, 0, 3, 1,  sequence1 ); 
    BlinkM_writeScript( 3, 0, 3, 1,  sequence1 ); 
    BlinkM_writeScript( 4, 0, 3, 1,  sequence1 ); 
    BlinkM_writeScript( 5, 0, 3, 1,  sequence1 );
    delay(100);
    BlinkM_playScript(3, 0, 1, 0);
    BlinkM_playScript(2, 0, 1, 0);
    BlinkM_playScript(4, 0, 1, 0);
    BlinkM_playScript(1, 0, 1, 0);
    BlinkM_playScript(5, 0, 1, 0);
    
    numberOfHits = 0; 
    delay(5000); 
    resetLEDs();
    playingBonus = false;  
}
