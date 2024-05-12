#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // Chiều rộng màn hình OLED, tính bằng điểm ảnh
#define SCREEN_HEIGHT 64 // Chiều cao màn hình OLED, tính bằng điểm ảnh

#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

unsigned long lastUpdateTime = 0; // Thời điểm cập nhật cuối cùng
bool eyes_open = true; // Trạng thái của đôi mắt: mở hoặc đóng
int transitionDuration = 2000; // Thời gian mở hoặc đóng mắt (milliseconds)

void setup() {
  // Khởi tạo màn hình OLED với địa chỉ mặc định 0x3C
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Màn hình OLED không được kết nối. Kiểm tra kết nối!"));
    while (1);
  }
}

void open_eyes() {
  // Vẽ đôi mắt mở
  display.clearDisplay(); // Xóa màn hình trước khi vẽ
  
  // Tô màu nửa trên của mắt trái
  for (int x = 30; x <= 60; x++) {
    for (int y = 20; y <= 50; y++) {
      if ((x - 45)*(x - 45) + (y - 35)*(y - 35) <= 225 && y <= 35) { // Phương trình hình tròn: (x-45)^2 + (y-35)^2 = 225
        display.drawPixel(x, y, WHITE);
      }
    }
  }
  
  // Tô màu nửa trên của mắt phải
  for (int x = 70; x <= 100; x++) {
    for (int y = 20; y <= 50; y++) {
      if ((x - 85)*(x - 85) + (y - 35)*(y - 35) <= 225 && y <= 35) { // Phương trình hình tròn: (x-85)^2 + (y-35)^2 = 225
        display.drawPixel(x, y, WHITE);
      }
    }
  }

  // Vẽ miệng cười nằm ở giữa
  int mouthCenterX = SCREEN_WIDTH / 2;
  int mouthWidth = 10; // Chiều rộng của miệng cười
  int mouthHeight = 5; // Chiều cao của miệng cười
  int mouthLeft = mouthCenterX - mouthWidth / 2;
  int mouthRight = mouthCenterX + mouthWidth / 2;
  int mouthTop = 40; // Vị trí phía trên của miệng cười
  
  // Vẽ miệng cười dưới dạng hình chữ V nhỏ
  display.drawLine(mouthLeft, mouthTop, mouthCenterX, mouthTop + mouthHeight, WHITE);
  display.drawLine(mouthCenterX, mouthTop + mouthHeight, mouthRight, mouthTop, WHITE);
  
  display.display(); // Hiển thị đôi mắt lên màn hình
}




void close_eyes() {
  // Vẽ đôi mắt đóng
  display.clearDisplay(); // Xóa màn hình trước khi vẽ
  
  // Vẽ mắt trái đóng
  display.fillCircle(45, 35, 15, WHITE); // Vẽ hình tròn trắng để đóng mắt trái
  
  // Vẽ mắt phải đóng
  display.fillCircle(85, 35, 15, WHITE); // Vẽ hình tròn trắng để đóng mắt phải
  
  display.display(); // Hiển thị đôi mắt lên màn hình
}

void loop() {
  unsigned long currentTime = millis(); // Lấy thời gian hiện tại
  
  // Nếu đã đến thời điểm cập nhật tiếp theo
  if (currentTime - lastUpdateTime >= transitionDuration) {
    lastUpdateTime = currentTime; // Cập nhật thời điểm cuối cùng
    
    if (eyes_open) {
      close_eyes(); // Đóng mắt
      eyes_open = false; // Cập nhật trạng thái
    } else {
      open_eyes(); // Mở mắt
      eyes_open = true; // Cập nhật trạng thái
    }
  }
}


