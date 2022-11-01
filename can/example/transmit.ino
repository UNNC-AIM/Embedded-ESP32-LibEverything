#include <Arduino.h>
#include <can.h>

void setup() {
    // Setup instance
    Serial.begin(115200);

    ESP_CAN::CAN can;

    can.CAN_Setup(GPIO_NUM_33, GPIO_NUM_35, b1000k);
    can.CAN_Start();

    // Initialize CAN port
}

void loop() {
    // Create variables to store the tx data and rx data
    can_frame_data tx_data;
    int16_t cmdCurrent = 5000;

    // Specify Tx data
    tx_data.identifier = 0x1ff;
    tx_data.flags = TWAI_MSG_FLAG_NONE;
    tx_data.data_length_code = 2;

    tx_data.data[0] = (uint8_t)(cmdCurrent >> 8);
    tx_data.data[1] = (uint8_t)(cmdCurrent);

    // Transmit
    Serial.println(ESP_CAN::CAN_Transmit(tx_data, 1));
    vTaskDelay(2);
}