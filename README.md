#  基于ESP32 开发板（MCU）遥控小车

嵌入式单片机ESP32Arduino 遥控小车（蓝牙版）

<img src="" width="300" height="300">


## 材料

ESP32主板1个、步进器1个（电机驱动）、3.7V电池1个（18000mAh）、车身架1个、2个轮胎和2个小马达、跳线若干。

### 小车主板

<img width="449" alt="image" src="https://github.com/liyinchigithub/esp8266_car_webServer/assets/19643260/2fcd5151-e3a0-4d4b-9fbe-824e7a37c865">


### 一、ESP32 NodeMCU 单片机

<img src="" width="300" height="400">

拓展板

<img src="" width="300" height="400">

备注：ESP32引脚数量有限，使用拓展板来引出更多引脚

#### 引脚图

<img src="" width="400" height="300">

#### Arduino IDE 安装ESP32Audio库

1. 打开Arduino IDE。

3. 在菜单栏中，选择Sketch -> Include Library -> Manage Libraries...。

5. 在弹出的库管理器窗口中，输入ESP32库到搜索框中。

7. 在搜索结果中找到ESP32，点击Install按钮进行安装。


#### 选择开发板

1. 打开Arduino IDE。

2. 在菜单栏中，选择工具 -> 开发板 -> 选择ESP32 Dev Module 或者 ESP32-WROOM-DA Modulle

<img width="143" alt="image" src="https://github.com/liyinchigithub/esp32-wroom-car/assets/19643260/9cdddaaa-69ad-4fd2-8f1b-37a29594c37f">


<img width="914" alt="image" src="https://github.com/liyinchigithub/esp32-wroom-car/assets/19643260/1850680e-9e3c-4848-b45d-abac407317e7">

#### 选择端口


<img src="" width="200" height="150">

#### 驱动安装

<img width="200" height="150" alt="image" src="">



### 二、（可变速）L287N直流电机（步进器电机驱动板）

<img src="https://github.com/liyinchigithub/esp8266_car_webServer/assets/19643260/4be41a85-daaa-47ba-a8ee-69594b922bd1" width="200" height="550">

L298N电机驱动板通常需要四个控制引脚来驱动一个双电机：

- 两个用于控制电机A的方向，另外两个用于控制电机B的方向。
- 还有两个使能引脚（一个用于电机A，一个用于电机B），可以用来控制电机的速度，通常通过PWM信号实现。

1. OUT1和OUT2 电池1、OUT3和OUT4 电池2

<img src="https://github.com/liyinchigithub/esp8266_car_webServer/assets/19643260/cc0a4d85-65d7-4f76-acab-0b359a90d4be" width="300" height="200">


2. 12V电源正极（暂不用）、GND电源负极接到esp32电源负极 、+5V接到esp32电源正极极

<img src="https://github.com/liyinchigithub/esp8266_car_webServer/assets/19643260/c999d437-46b0-43eb-8c7f-5f245023c422" width="300" height="200">


3. ENA：电机1PWM调速引脚

<img src="https://github.com/liyinchigithub/esp8266_car_webServer/assets/19643260/4fabed0e-b6d7-4cd6-9a88-b94c54a44d8c" width="300" height="200">

**注意**：不使用调速引脚，那两个塑料不要拔起来，拔起来后需要用“母对母”跳线连接

5. ENB：电机2PWM调速引脚

<img src="https://github.com/liyinchigithub/esp8266_car_webServer/assets/19643260/e572ce93-db48-47b2-bff0-e6e7f846b1cb" width="300" height="200">


6. IN1和IN2：电机1 正反转/停止控制
   
<img src="https://github.com/liyinchigithub/esp8266_car_webServer/assets/19643260/73b05a29-3d88-49ee-ac6e-4be1033e2765" width="300" height="200">

7. IN3和IN4：电机2 正反转/停止控制

* <img src="https://github.com/liyinchigithub/esp8266_car_webServer/assets/19643260/b9c65e78-46da-4abe-b596-874bfc079843" width="300" height="200">


* <img width="800"  height="400" alt="image" src="https://github.com/liyinchigithub/esp8266_car_webServer/assets/19643260/72d39314-f720-45dd-b862-290088d42a8e">

* <img width="739" alt="image" src="https://github.com/liyinchigithub/esp8266_car_webServer/assets/19643260/96386172-4779-4443-9e55-ea090757837c">


8.左右电机控制

<img src="https://github.com/liyinchigithub/esp8266_car_webServer/assets/19643260/f0de3c2f-4cdc-4fba-9f51-eb6617a97c96" width="300" height="200">



9.引脚对接

（1）esp32

| L298N引脚 | ESP32引脚 |
|-----------|-----------|
| IN1 | 23 |
| IN2 | 22 |
| IN3 | 19 |
| IN4 | 18 |
| ENA | 21 |
| ENB | 5 |

（2）esp8266

<img src="https://github.com/liyinchigithub/esp8266_car_webServer/assets/19643260/d2b2ce52-44fb-4903-a1cd-41f9e2f1b2eb" width="200" height="200">

<img src="https://github.com/liyinchigithub/esp8266_car_webServer/assets/19643260/0c27b5c8-5c60-4ea2-aef6-1f0f54a0f2ec" width="200" height="200">



[B站视频1](https://www.bilibili.com/video/BV1TW4y1y7PT/?spm_id_from=333.337.search-card.all.click&vd_source=73d9ae1d519db8c687b2d2e7b02c99ed)
[B站视频2](https://www.bilibili.com/video/BV1Xt411372X/?spm_id_from=autoNext&vd_source=73d9ae1d519db8c687b2d2e7b02c99ed)





### 三、（不可变速）L9110S直流电机（步进器电机驱动板）

- <img src="https://github.com/liyinchigithub/esp8266_car_webServer/assets/19643260/4b6524c5-65e4-40f3-8112-f5a8f1a63fd4" width="300" height="300">


- <img src="https://github.com/liyinchigithub/esp8266_car_webServer/assets/19643260/427a38aa-8058-4608-b2c3-3a224a8be586" width="300" height="300">


- <img src="https://github.com/liyinchigithub/esp8266_car_webServer/assets/19643260/63b7af22-43ba-44dd-9fcb-7d5651c6fffd" width="300" height="300">

## 遥控按钮

### 虚拟网页按键

1.程序烧入ESP32主板后，生成wifi热点：“遥控小车”；
2.使用手机或平板连接热点密码：12345678
3.浏览器地址：http://192.168.4.1

<img width="300" height="600" alt="image" src="https://github.com/liyinchigithub/esp8266_car_webServer/assets/19643260/7ca61931-389f-4d21-8b0d-e1590c4028b9">


### 实体键

要实现一个ESP32作为遥控器端（esp32_wroom_car_client.ino），需要连接4个按钮到ESP32的GPIO引脚，并且当按钮被按下时，发送HTTP POST请求到另一个作为服务器端的ESP32（esp32_wroom_car_server.ino）。


1. 连接每个按钮的一个引脚到ESP32的GPIO引脚，另一个引脚连接到GND。
2. 在客户端代码中配置WiFi连接，以便它可以连接到服务器端ESP32创建的热点。
3. 为每个按钮设置GPIO引脚模式为输入，并启用内部上拉电阻。
4. 在主循环中检测按钮是否被按下，并发送相应的HTTP POST请求到服务器端。












## 常见问题

如果你已经将引脚设置为高电平，但是马达没有运动，可能有以下几个原因：

1. 电流不足：ESP32的GPIO引脚只能提供很小的电流（大约12mA），这可能不足以驱动马达。可能需要一个马达驱动器或者一个适当的晶体管来放大电流。

2. 连接问题：检查你的马达是否正确连接到ESP32和电源。

3. 马达问题：你的马达可能有问题。试着用另一个马达，或者直接用电源给马达供电，看看马达是否能运动。使用专门的马达控制板（如L293D或者L298N）来驱动你的马达。

4. 代码问题：检查你的代码是否正确设置了GPIO引脚为输出模式，并且设置了高电平。





