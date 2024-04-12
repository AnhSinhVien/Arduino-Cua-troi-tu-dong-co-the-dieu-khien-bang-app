// Khai báo công tắt hành trình
const int CTHT_close = 4;
const int CTHT_open = 7;

// khai báo chân động cơ
const int MT_IN1 = 9;
const int MT_IN2 = 10;

// khai báo chân sensor rain
const int Sen_rain = 13;

// Khai báo biến dùng millis()
typedef unsigned long ul;
ul time_gan = 0;


// Biến khóa
bool TG_senRain = 1;
bool TG_giuCheDoClose = 0;
bool TG_open = 0;
bool TG_close = 0;
bool TG_resetOpen = 0;
bool TG_resetClose = 0;

bool TG_batCheDoTay = 0;
bool TG_khoatay = 0;
bool resetbit = 0;

// khai báo hàm
void cheDoMo();
void cheDoDong();
void resetOpen();
void resetClose();


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
  if(Serial.available() > 0){   //Kiểm tra nếu có giá trị đang đợi để đọc
    char cmd = Serial.read();
    // Chọn chế độ
    if(cmd == 'e'){                                                 // chế độ điều khiển bằng tay
      TG_batCheDoTay = 1;
    }
    if(cmd == 'f'){                                                 // chế độ Auto
      resetbit = 0;
      TG_batCheDoTay = 0;
    }
    
    // Chế độ tay
    if(TG_batCheDoTay == 1){
      if(cmd == 'a' || TG_resetOpen == 1){                          // Chế độ mở cửa
        TG_resetOpen = 1;
        resetOpen();
      }
      else if(cmd == 'b' || TG_resetClose == 1){                    // Chế độ đóng cửa
        TG_resetClose = 1;
        resetClose();
      }
      else{
        digitalWrite(MT_IN1,0);
        digitalWrite(MT_IN2,0);
      }
      resetbit = 0;
    }
    
    // Chế độ tự động
    if(TG_batCheDoTay == 0){
      if(resetbit == 0){
        // Biến khóa
        TG_senRain = 1;
        TG_giuCheDoClose = 0;
        TG_open = 0;
        TG_close = 0;
        TG_resetOpen = 0;
        TG_resetClose = 0;
        TG_batCheDoTay = 0;
        TG_khoatay = 0;
        resetbit = 1;
      }
      
      //useSensorRain();
    }
  }
  // Chế độ tự động
  else{
    useSensorRain();
  }
}



//----------------------Chế độ cảm biến--------------------------------------------//
void useSensorRain(){
  int readSensor = digitalRead(Sen_rain);
  int readCTHTClose = digitalRead(CTHT_close);
  int readCTHTOpen = digitalRead(CTHT_open);
  
  // Có mưa
  if((readSensor == 0 && TG_senRain == 0 && TG_khoatay == 0)||TG_giuCheDoClose == 1){
    TG_giuCheDoClose = 1;
    digitalWrite(MT_IN1,1);
    digitalWrite(MT_IN2,0);
    if(digitalRead(CTHT_close) == 0){
      digitalWrite(MT_IN1,0);
      digitalWrite(MT_IN2,0);
      delay(10);
      TG_senRain = 1;
      TG_giuCheDoClose = 0;
    }
    //Serial.println("dang mua");
    //delay(200);
  }
  // Trời mát
  if(readSensor == 1 && TG_senRain == 1 && TG_khoatay == 0){
    digitalWrite(MT_IN1,0);
    digitalWrite(MT_IN2,1);
    if(digitalRead(CTHT_open) == 0){
      delay(10);
      digitalWrite(MT_IN1,0);
      digitalWrite(MT_IN2,0);
      TG_senRain = 0;
    }
    //Serial.println("het mua");
    //delay(200);
  }
  
//  Serial.print(readSensor); Serial.print(" - "); Serial.print(TG_senRain);
//  Serial.print(" CTHT: "); Serial.print(readCTHTClose); Serial.print(" - "); Serial.println(readCTHTOpen);

}


//----------------------Chế độ điều khiển bằng tay--------------------------------------------//
// Chế độ open
void resetOpen(){
  digitalWrite(MT_IN1,0);
  digitalWrite(MT_IN2,1);
  TG_senRain = 1;
  while (digitalRead(CTHT_open) == 1) {
    // Chờ cho đến khi công tắc hành trình mở được kích hoạt
    // Hoặc có thể thêm một hạn chế thời gian ở đây để tránh bị mắc kẹt trong vòng lặp vô hạn
    char vcc = Serial.read();
    if(vcc == 'c') break;
  }
    digitalWrite(MT_IN1,0);
    digitalWrite(MT_IN2,0);
    TG_resetOpen = 0;
    TG_khoatay = 1;
}

// Chế độ close
void resetClose(){
  digitalWrite(MT_IN1,1);
  digitalWrite(MT_IN2,0);
  TG_senRain = 0;
  while (digitalRead(CTHT_close) == 1) {
    // Chờ cho đến khi công tắc hành trình mở được kích hoạt
    // Hoặc có thể thêm một hạn chế thời gian ở đây để tránh bị mắc kẹt trong vòng lặp vô hạn
    char vcc = Serial.read();
    if(vcc == 'c') break;
  }
    digitalWrite(MT_IN1,0);
    digitalWrite(MT_IN2,0);
    TG_resetClose = 0;
    TG_khoatay = 1;

  
}
