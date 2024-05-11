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

void draw_circle() {
  display.clearDisplay(); // Xóa màn hình trước khi vẽ
  // Vẽ vòng tròn tại tọa độ (64, 32) (tọa độ trung tâm) với bán kính 30 điểm ảnh
  display.drawCircle(64, 32, 30, WHITE);
  display.display(); // Hiển thị vòng tròn lên màn hình
}

void setup() {
  // Khởi tạo màn hình OLED với địa chỉ mặc định 0x3C
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Màn hình OLED không được kết nối. Kiểm tra kết nối!"));
    while (1);
  }
  // Hiển thị vòng tròn lên màn hình OLED
  draw_circle();
  delay(2000); // Delay 2 giây để vòng tròn hiển thị trong 2 giây
}

void loop() {
  // Không cần thực hiện gì trong hàm loop() vì chúng ta chỉ muốn hiển thị vòng tròn một lần.
}

