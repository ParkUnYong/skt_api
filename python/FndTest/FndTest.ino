#include <Servo.h>

Servo myservo;

// 숫자 표시용 LED 연결 정보
#define SEG_A 2 // 11
#define SEG_B 3 // 7
#define SEG_C 4 // 4
#define SEG_D 5 // 2
#define SEG_E 6 // 1
#define SEG_F 7 // 10
#define SEG_G 8 // 5
#define SEG_DP A3 // 5

// 자릿수 구동 LED 공통단자 연결 정보
#define FND_01 10 // 6
#define FND_02 11 // 8
#define FND_03 12 // 9
#define FND_04 13 // 12

#define DELAY_TIME 5
#define OPEN_ANGLE -90
#define CLOSE_ANGLE 90

void seglight(byte number);
byte numbers[] = {
  B0111111,  // MSB   --  LSB
  B0000110,
  B1011011,
  B1001111,
  B1100110,
  B1101101,
  B1111101,
  B0000111,
  B1111111,
  B1101111
};

int FND[] = {SEG_A, SEG_B, SEG_C, SEG_D, SEG_E, SEG_F, SEG_G, SEG_DP };
int FND_NO[] = {FND_01, FND_02, FND_03, FND_04};
void setup() {

  Serial.begin(9600);
  
  // put your setup code here, to run once:
  for (int i = 0 ; i < 8; i++) {
    pinMode(FND[i], OUTPUT);
  }
  for (int i = 0 ; i < 5; i++) {
    pinMode(FND_NO[i], OUTPUT);
    digitalWrite(FND_NO[i], HIGH);
  }

  pinMode(A0, OUTPUT);
  pinMode(A2, OUTPUT);
  
  myservo.attach(9);
}
int ON = OUTPUT;
double value_dust = 0;
int current_angle = 0;
String value_read = "1234";

void loop() {
    // Dynamic 구동
    // FND가 공통 캐소드 방식이어서 자릿수 LED를 켜기 위해 HIGH 신호를 보내야 한다
    // 1의 자리 표시
  unsigned long start = millis();
  for (unsigned long j = 0 ; j < 10 ; j = millis() - start) { // 600 밀리초 마다 실행
    // Dynamic 구동
    // FND가 공통 캐소드 방식이어서 자릿수 LED를 켜기 위해 HIGH 신호를 보내야 한다
    // 1의 자리 표시
  if(value_dust < 100){
      // 1의 자리 표시
      digitalWrite(FND_01, HIGH); // 켜기
      seglight(numbers[(int)(value_dust * 100) % 10]);
  
      delay(DELAY_TIME);
      digitalWrite(FND_01, LOW); // 끄기
  
      // 10의 자리 표시
      digitalWrite(FND_02, HIGH); // 켜기
      seglight(numbers[((int)(value_dust * 100) / 10) % 10]);
  
      delay(DELAY_TIME); 
      digitalWrite(FND_02, LOW); // 끄기
  
      // 100의 자리 표시
      digitalWrite(FND_03, HIGH); // 켜기
      digitalWrite(FND[7], LOW);
      seglight(numbers[((int)(value_dust * 100) / 100) % 10]);
  
      delay(DELAY_TIME);
      digitalWrite(FND_03, LOW); // 끄기
      digitalWrite(FND[7], HIGH);
  
      // 1000의 자리 표시
      digitalWrite(FND_04, HIGH); // 켜기
      seglight(numbers[((int)(value_dust * 100) / 1000) % 10]);
  
      delay(DELAY_TIME);
      digitalWrite(FND_04, LOW); // 끄기
      
    } else if(value_dust > 100){
      // 1의 자리 표시
      digitalWrite(FND_01, HIGH); // 켜기
      seglight(numbers[(int)(value_dust * 10) % 10]);
  
      delay(DELAY_TIME);
      digitalWrite(FND_01, LOW); // 끄기
  
      // 10의 자리 표시
      digitalWrite(FND_02, HIGH); // 켜기
      digitalWrite(FND[7], LOW);
      seglight(numbers[((int)(value_dust * 10) / 10) % 10]);
  
      delay(DELAY_TIME); 
      digitalWrite(FND_02, LOW); // 끄기
      digitalWrite(FND[7], HIGH);
  
      // 100의 자리 표시
      digitalWrite(FND_03, HIGH); // 켜기
      seglight(numbers[((int)(value_dust * 10) / 100) % 10]);
  
      delay(DELAY_TIME);
      digitalWrite(FND_03, LOW); // 끄기
  
      // 1000의 자리 표시
      digitalWrite(FND_04, HIGH); // 켜기
      seglight(numbers[((int)(value_dust * 10) / 1000) % 10]);
  
      delay(DELAY_TIME);
      digitalWrite(FND_04, LOW); // 끄기
    }
    
  }

  if(value_dust > 80 && current_angle < CLOSE_ANGLE){
    current_angle += 5;
    myservo.write(current_angle);
  
    digitalWrite(A0, HIGH);
    digitalWrite(A2, LOW); 
  } else if(value_dust <= 80 && current_angle >= OPEN_ANGLE){
    current_angle -= 5;
    myservo.write(current_angle);

    digitalWrite(A0, LOW);
    digitalWrite(A2, HIGH);
  }
}


// Bit값으로 FND 각 LED 점등
void seglight(byte number) {
  for (int i = 0 ; i < 7 ; i++) {
    int bit = bitRead(number, i) ;
    digitalWrite(FND[i], not(bit));
  }
}

void serialEvent(){
  int ch_temp = 0;
  char str_data[10];

  value_read = "";
   
   while((ch_temp = Serial.read()) != -1) {
     value_read.concat((char)ch_temp);
   }
   
  int len_str = value_read.length() + 1;
  
  if(len_str < 5 || len_str > 6){
    return;
  }
  
  value_read.toCharArray(str_data, len_str);
   
  value_dust = atof(str_data);
}
