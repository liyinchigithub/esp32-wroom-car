#include <WiFi.h>       // 引入WiFi库
#include <HTTPClient.h> // 引入HTTP客户端库

const char *ssid = "遥控小车";     // WiFi名称
const char *password = "12345678"; // WiFi密码

// 摇杆
const int joystickXPin = 34; // VRX
const int joystickYPin = 35; // VRY
const int joystickButtonPin = 32; // SW
// 定义按钮连接的GPIO引脚
const int buttonForward = 12;  // 前进按钮
const int buttonBackward = 14; // 后退按钮
const int buttonLeft = 27;     // 左转按钮
const int buttonRight = 26;    // 右转按钮

const char *serverUrl = "http://192.168.4.1"; // 服务器端ESP32的IP地址



void setup()
{
  Serial.begin(115200);       // 开始串行通信
  WiFi.begin(ssid, password); // 开始WiFi连接
  while (WiFi.status() != WL_CONNECTED)
  { // 等待WiFi连接
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected"); // WiFi连接成功

  // 设置按钮引脚为输入模式，并启用内部上拉电阻
  pinMode(buttonForward, INPUT_PULLUP);
  pinMode(buttonBackward, INPUT_PULLUP);
  pinMode(buttonLeft, INPUT_PULLUP);
  pinMode(buttonRight, INPUT_PULLUP);
  // 摇杆
  pinMode(joystickButtonPin, INPUT_PULLUP); // 设置摇杆按钮为输入并启用内部上拉电阻
}

void loop()
{
  // 定义按钮是否被按下的状态变量
  static bool isForwardPressed = false;
  static bool isBackPressed = false;
  static bool isLeftPressed = false;
  static bool isRightPressed = false;

  // 检查每个按钮并相应地发送命令
  checkButton(buttonForward, 3, isForwardPressed);
  checkButton(buttonBackward, 5, isBackPressed);
  checkButton(buttonLeft, 1, isLeftPressed);
  checkButton(buttonRight, 2, isRightPressed);
  // 读取摇杆值并控制小车
  controlCarWithJoystick();
  delay(50); // 简单的消抖延时
}

// 检查按钮状态并发送命令的函数
void checkButton(int buttonPin, int action, bool &isPressed)
{
  int buttonState = digitalRead(buttonPin); // 读取按钮当前状态
  static int lastButtonState = HIGH;        // 上一次的按钮状态，默认为未按下

  // 检查按钮状态是否改变
  if (buttonState != lastButtonState)
  {
    if (buttonState == LOW)
    {
      // 按钮被按下
      if (!isPressed)
      {
        sendCommand(action); // 发送对应的动作命令
        isPressed = true;
      }
    }
    else
    {
      // 按钮被释放
      if (isPressed)
      {
        sendStopCommand(); // 发送停止命令
        isPressed = false;
      }
    }
    lastButtonState = buttonState; // 更新上一次的按钮状态
  }
}

// 发送动作命令的函数
void sendCommand(int action)
{
  HTTPClient http;                                            // 创建HTTP客户端对象
  http.begin(serverUrl + String("/start"));                   // 开始连接到服务器
  http.addHeader("Content-Type", "application/json");         // 添加HTTP头
  String requestBody = "{\"action\":" + String(action) + "}"; // 创建JSON请求体
  int httpResponseCode = http.POST(requestBody);              // 发送POST请求
  if (httpResponseCode > 0)
  {
    String response = http.getString(); // 获取响应
    Serial.println(response);           // 打印响应
  }
  else
  {
    Serial.print("Error on sending POST: "); // 打印错误信息
    Serial.println(httpResponseCode);
  }
  http.end(); // 结束HTTP连接
}

// 发送停止命令的函数
void sendStopCommand()
{
  HTTPClient http;                                    // 创建HTTP客户端对象
  http.begin(serverUrl + String("/stop"));            // 开始连接到服务器
  http.addHeader("Content-Type", "application/json"); // 添加HTTP头
  int httpResponseCode = http.POST("{}");             // 发送空的JSON对象作为停止命令
  if (httpResponseCode > 0)
  {
    String response = http.getString(); // 获取响应
    Serial.println(response);           // 打印响应
  }
  else
  {
    Serial.print("Error on sending POST: "); // 打印错误信息
    Serial.println(httpResponseCode);
  }
  http.end(); // 结束HTTP连接
}

void controlCarWithJoystick() {
  int xValue = analogRead(joystickXPin); // 读取X轴值
  int yValue = analogRead(joystickYPin); // 读取Y轴值
  bool buttonPressed = digitalRead(joystickButtonPin) == LOW; // 读取按钮状态

  // 根据摇杆位置决定动作
  if (yValue < 1700) { // 前进
    Serial.println("前进");
    sendCommand(3);
  } else if (yValue > 2400) { // 后退
    Serial.println("后退");
    sendCommand(5);
  } else if (xValue < 1700) { // 左转
  Serial.println("左");
    sendCommand(1);
  } else if (xValue > 2400) { // 右转
  Serial.println("右");
    sendCommand(2);
  }
   else if (buttonPressed) { // 按钮被按下
    sendStopCommand();
  } 
  else {
    sendStopCommand(); // 摇杆在中间位置时停止
  }
}