# ESP32_CAN库函数使用说明
本库函数使用C++语言中的类简单封装了ESP32CAN的API，封装后的API如下所示
```c++
void ESP_CAN::CAN::CAN_Setup(gpio_num_t TX_PIN, gpio_num_t RX_PIN, CAN_BaudRate baudrate);
```
TX_PIN：对应CAN_TX引脚  
RX_PIN：对应CAN_RX引脚  
baudrate：对应CAN通信的波特率  

其中使用了一个枚举变量来表示所有可用的波特率  
```c++
enum CAN_BaudRate {
    b25K,
    b50K,
    b100k,
    b125k,
    b250k,
    b500k,
    b800k,
    b1000k
};
```
`ESP_CAN::CAN::CAN_Setup()`函数完成了CAN接口的基本设置，但是此时并未启用CAN接口对外通讯，要正常进行通讯，需要执行以下函数：
```c++
esp_err_t ESP_CAN::CAN::CAN_Start();
```
返回值为 ESP_FAIL 时，开启CAN接口失败  
返回值为 ESP_OK 时，成功开启CAN接口，此时可进一步完成CAN的收发功能  
\
为使用上述函数，请先实例化本函数库提供的类：
```c++
ESP_CAN::CAN instance_name;
```
\
TODO:
* 硬件滤波器初始化设置
* CAN收发函数的二次封装