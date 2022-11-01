#include <Arduino.h>
#include <can.h>

struct motor_feedback_data {
    uint16_t ecd;
    int16_t rotor_spd;
    int16_t torque_current;
    uint8_t temperature;
};

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
    static can_frame_data rx_data;
    motor_feedback_data motor_data;
    
    ESP_CAN::CAN_Receive(&rx_data, 1);

    motor_data.ecd = (uint16_t)(rx_data.data[0] << 8) | rx_data.data[1];
    motor_data.rotor_spd = (uint16_t)(rx_data.data[2] << 8) | rx_data.data[3];
    motor_data.torque_current = (uint16_t)(rx_data.data[4] << 8) | rx_data.data[5];
    motor_data.temperature = rx_data.data[6];

    Serial.printf("Encoder: %d\tRotor Speed: %d rpm\tTorque current: %d mA\tTemp: %d Celus\n", 
        motor_data.ecd,
        motor_data.rotor_spd,
        motor_data.torque_current,
        motor_data.temperature
    );
    vTaskDelay(100);
}