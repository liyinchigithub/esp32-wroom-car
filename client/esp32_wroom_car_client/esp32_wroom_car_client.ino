#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "遥控小车";
const char* password = "12345678";

const int buttonForward = 12; // 前进按钮连接的GPIO引脚
const int buttonBackward = 14; // 后退按钮连接的GPIO引脚
const int buttonLeft = 27; // 左转按钮连接的GPIO引脚
const int buttonRight = 26; // 右转按钮连接的GPIO引脚

const char* serverUrl = "http://192.168.4.1"; // 服务器端ESP32的IP地址

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");

  pinMode(buttonForward, INPUT_PULLUP);
  pinMode(buttonBackward, INPUT_PULLUP);
  pinMode(buttonLeft, INPUT_PULLUP);
  pinMode(buttonRight, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(buttonForward) == LOW) {
    sendCommand(3); // 发送前进命令
  } else if (digitalRead(buttonBackward) == LOW) {
    sendCommand(5); // 发送后退命令
  } else if (digitalRead(buttonLeft) == LOW) {
    sendCommand(1); // 发送左转命令
  } else if (digitalRead(buttonRight) == LOW) {
    sendCommand(2); // 发送右转命令
  }
}

void sendCommand(int action) {
  HTTPClient http;
  http.begin(serverUrl + String("/start"));
  http.addHeader("Content-Type", "application/json");
  String requestBody = "{\"action\":" + String(action) + "}";
  int httpResponseCode = http.POST(requestBody);
  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println(response);
  } else {
    Serial.print("Error on sending POST: ");
    Serial.println(httpResponseCode);
  }
  http.end();
}