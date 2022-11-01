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
完成CAN接口的初始化以后便可使用CAN收发函数：  
```c++
inline esp_err_t CAN_Transmit(const can_frame_data frame, TickType_t ticks_to_wait);
inline esp_err_t CAN_Receive(const can_frame_data frame, TickType_t ticks_to_wait);
```
由于Espressif官方提供的API已经十分详尽，这里直接使用内联函数替换官方API。  
\
收发函数中`can_frame_data`是官方API中`twai_message_t`的别名，其内容如下：
```c++
typedef struct {
    union {
        struct {
            //The order of these bits must match deprecated message flags for compatibility reasons
            uint32_t extd: 1;           /**< Extended Frame Format (29bit ID) */
            uint32_t rtr: 1;            /**< Message is a Remote Frame */
            uint32_t ss: 1;             /**< Transmit as a Single Shot Transmission. Unused for received. */
            uint32_t self: 1;           /**< Transmit as a Self Reception Request. Unused for received. */
            uint32_t dlc_non_comp: 1;   /**< Message's Data length code is larger than 8. This will break compliance with ISO 11898-1 */
            uint32_t reserved: 27;      /**< Reserved bits */
        };
        //Todo: Deprecate flags
        uint32_t flags;                 /**< Deprecated: Alternate way to set bits using message flags */
    };
    uint32_t identifier;                /**< 11 or 29 bit identifier */
    uint8_t data_length_code;           /**< Data length code */
    uint8_t data[TWAI_FRAME_MAX_DLC];    /**< Data bytes (not relevant in RTR frame) */
} twai_message_t;
```
而`TickType_t`是官方API中的延时时长，单位时间取决于系统时间长度，默认情况下单位为/ms  

TODO:
* 硬件滤波器初始化设置