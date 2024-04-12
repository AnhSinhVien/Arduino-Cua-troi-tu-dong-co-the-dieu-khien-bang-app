
// Khai báo công tắt hành trình
const int CTHT_close = 4;
const int CTHT_open = 7;

// khai báo chân động cơ
const int MT_IN1 = 9;
const int MT_IN2 = 10;

// khai báo chân sensor rain
const int Sen_rain = 13;

// Biến khóa
bool TG_senRain = 1;
bool TG_giuCheDoClose = 0;
bool TG_open = 0;
bool TG_close = 0;
bool TG_resetOpen = 0;
bool TG_resetClose = 0;

bool TG_batCheDoTay = 0;
bool TG_khoatay = 0;

void setup() {
  Serial.begin(9600);
  pinMode(CTHT_close, INPUT_PULLUP);
  pinMode(CTHT_open, INPUT_PULLUP);
  pinMode(Sen_rain, INPUT);
  pinMode(MT_IN1, OUTPUT);
  pinMode(MT_IN2, OUTPUT);
  digitalWrite(MT_IN1,0);
  digitalWrite(MT_IN2,0);
}

void loop() {
  int readSensor = digitalRead(Sen_rain);
  int readCTHTClose = digitalRead(CTHT_close);
  int readCTHTOpen = digitalRead(CTHT_open);
  
  // Có mưa
  if((readSensor == 0 && TG_senRain == 0 && TG_khoatay == 0)||TG_giuCheDoClose == 1){
    TG_giuCheDoClose = 1;
    digitalWrite(MT_IN1,1);
    digitalWrite(MT_IN2,0);
    if(readCTHTClose == 0){
      digitalWrite(MT_IN1,0);
      digitalWrite(MT_IN2,0);
      delay(10);
      TG_senRain = 1;
      TG_giuCheDoClose = 0;
    }
    Serial.println("dang mua");
    //delay(200);
  }
  // Trời mát
  if(readSensor == 1 && TG_senRain == 1 && TG_khoatay == 0){
    digitalWrite(MT_IN1,0);
    digitalWrite(MT_IN2,1);
    if(readCTHTOpen == 0){
      delay(10);
      digitalWrite(MT_IN1,0);
      digitalWrite(MT_IN2,0);
      TG_senRain = 0;
    }
    Serial.println("het mua");
    //delay(200);
  }
  
//  Serial.print(readSensor); Serial.print(" - "); Serial.print(TG_senRain);
//  Serial.print(" CTHT: "); Serial.print(readCTHTClose); Serial.print(" - "); Serial.println(readCTHTOpen);


}
