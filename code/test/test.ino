// Khai báo công tắt hành trình
const int CTHT_close = 4;
const int CTHT_open = 7;

// khai báo chân động cơ
const int MT_IN1 = 9;
const int MT_IN2 = 10;

// khai báo chân sensor rain
//const int Sen_rain = 13;
int readSensor = 1;
String TT = "Thoi tiet hom nay: ";

// Khai báo biến dùng millis()
typedef unsigned long ul;
ul time_gan = 0;

// Biến khóa
bool TG_senRain = 0; bool TG_giuCheDoClose = 0;

void setup() {
  Serial.begin(9600);
  pinMode(CTHT_close, INPUT_PULLUP);
  pinMode(CTHT_open, INPUT_PULLUP);
  //pinMode(Sen_rain, INPUT);
  pinMode(MT_IN1, OUTPUT);
  pinMode(MT_IN2, OUTPUT);
  
}

void loop() {
  Serial.print("Thoi tiet hom nay: ");
  while(Serial.available()==0){
    
  }
  readSensor = Serial.parseInt();
  useSensorRain();
}



//------------------------------------------------------------------//
void useSensorRain(){
  //int readSensor = digitalRead(Sen_rain);
  int readCTHTClose = digitalRead(CTHT_close);
  int readCTHTOpen = digitalRead(CTHT_open);
  
  // Có mưa
  if((readSensor == 2 && TG_senRain == 0)||TG_giuCheDoClose == 1){
    TG_giuCheDoClose = 1;
    digitalWrite(MT_IN1,1);
    digitalWrite(MT_IN2,0);
    if(digitalRead(CTHT_close) == 0){
      TG_senRain = 1;
      TG_giuCheDoClose = 0;
    }
    Serial.println("dang mua");
    delay(200);
  }
  // Tạnh mưa
  if(readSensor == 1 && TG_senRain == 1){
    digitalWrite(MT_IN1,0);
    digitalWrite(MT_IN2,1);
    if(digitalRead(CTHT_open) == 0) TG_senRain = 0;
    Serial.println("het mua");
    delay(200);
  }
  
//  Serial.print(readSensor); Serial.print(" - "); 
    Serial.print(TG_giuCheDoClose);
    Serial.print(TG_senRain);
    Serial.print(" CTHT: "); Serial.print(readCTHTClose); Serial.print(" - "); Serial.println(readCTHTOpen);

}
