#include<Wire.h>
#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
int pos = 115;    // 舵机校准值
int posRead = 115;
int MOTORA_go = 50;  //电机速度_工作时 0-150
int MOTORA = 0;
//电机驱动引脚控制
int AIN1 = 6;  //PWMA
int AIN2 = 5;  //DIRA

////蜂鸣器用到的音调
//int melody[]={330,330,330,262,392,200,280};
//int noteDurations[]={8,4,4,8,4,4,5};
void setup(){                   //初使化
  delay(500);
  Serial.begin(9600);            //通信速率选择9600，与蓝牙模块保持一致
  pinMode(AIN1,OUTPUT);
  pinMode(AIN2,OUTPUT);
  pinMode(13, OUTPUT);
  myservo.attach(4);  // attaches the servo on pin 9 to the servo object 
  
//  //函数实现了播放一段音乐，播放完成后表示初使化已经完成 
// for(int thisNote = 0;thisNote < 7;thisNote ++){
//    tone(12,melody[thisNote],1000/noteDurations[thisNote]);
//    delay(1300/noteDurations[thisNote]);
//    noTone(12);
//  }
}
void setMotor(int MOTORA) //电机驱动函数
{
  if(MOTORA>=0)
  {
    digitalWrite(AIN2,HIGH);
    analogWrite(AIN1,255-MOTORA);
  }
  else
  {
   digitalWrite(AIN1,HIGH);
    analogWrite(AIN2,MOTORA+255);
  } 
}
void setRead()
{
 if(Serial.available() > 0){      //判断缓冲器状态
   switch (Serial.read()){       //对接收到的字符进行判断 
      case 'L':               
        posRead = pos-15;
        delay(15); 
        myservo.write(posRead);
         MOTORA = MOTORA_go;   
        setMotor(MOTORA);
       // MOTORA = MOTORA_go;         
        break;
      case 'b':               
        posRead = pos-15;
        delay(15); 
//        MOTORA = MOTORA_go;  
        break;
      case 'F':   
//        posRead = pos;
//        delay(15); 
        MOTORA = MOTORA_go;   
        setMotor(MOTORA);
        break;
      case 'd':              
        posRead = pos+15;
        delay(15); 
        MOTORA = MOTORA_go;   
        break;
      case 'R':              
        posRead = pos+15;
        delay(15); 
        myservo.write(posRead);
         MOTORA = MOTORA_go;   
        setMotor(MOTORA);
//        MOTORA = MOTORA_go;   
        break;
      case 'S':             
        posRead = pos;
        delay(15); 
        MOTORA = 0;  
        setMotor(MOTORA);
        break;
    }
  }  
}
void loop()
{
  setRead();
//  myservo.write(posRead);
//  Serial.println(posRead);
  delay(15); 
//  setMotor(MOTORA);    //设置“向前”行驶  
}
