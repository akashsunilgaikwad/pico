/*
This is for program to display 0-9 digits every second on single 
four seven segment led display with one 74HC594 shift register on 
Raspberry Pi Pico board.
-Akash
*/

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#define DATA_PIN    13
#define CLOCK_PIN   15
#define LATCH_PIN   14

#define DIGIT_1     1
#define DIGIT_2     2
#define DIGIT_3     3
#define DIGIT_4     4

#define DIGIT_1_EN_PIN  9
#define DIGIT_2_EN_PIN  10
#define DIGIT_3_EN_PIN  11
#define DIGIT_4_EN_PIN  12

// Define the bit Pattern for each digit (0-9)
const uint8_t bits[10] = 
{
    0b00111111, // 0
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111101, // 6
    0b00000111, // 7
    0b01111111, // 8
    0b01101111  // 9
};

const uint8_t digit_pin_mapping[4] =
{
    DIGIT_1_EN_PIN,    
    DIGIT_2_EN_PIN,
    DIGIT_3_EN_PIN,
    DIGIT_4_EN_PIN
};

void send_bit(int value) 
{
    gpio_put(DATA_PIN, value);
    gpio_put(CLOCK_PIN, 1);
    gpio_put(CLOCK_PIN, 0);
}

void send_byte(int value) 
{
    for (int i = 0; i < 8; i++) 
    {
        send_bit(!!(value & (1 << (7 - i))));
    }
}

void latch_data() 
{
    gpio_put(LATCH_PIN, 1);
    gpio_put(LATCH_PIN, 0);
}

void init_gpio_pins()
{
    // GPIO init for Raspberry Pi Pico
    gpio_init(DATA_PIN);
    gpio_init(CLOCK_PIN);
    gpio_init(LATCH_PIN);
    gpio_init(DIGIT_1_EN_PIN);
    gpio_init(DIGIT_2_EN_PIN);
    gpio_init(DIGIT_3_EN_PIN);
    gpio_init(DIGIT_4_EN_PIN);

    // Set Direction to the GPIO pin 
    gpio_set_dir(DATA_PIN, GPIO_OUT);
    gpio_set_dir(CLOCK_PIN, GPIO_OUT);
    gpio_set_dir(LATCH_PIN, GPIO_OUT);

    gpio_set_dir(DIGIT_1_EN_PIN, GPIO_OUT);
    gpio_set_dir(DIGIT_2_EN_PIN, GPIO_OUT);
    gpio_set_dir(DIGIT_3_EN_PIN, GPIO_OUT);
    gpio_set_dir(DIGIT_4_EN_PIN, GPIO_OUT);
}

int main() 
{
    stdio_init_all();
    init_gpio_pins();

    while (true) 
    {
        for (int i = 0; i < 4; i++) 
        {
            // enable digits
            gpio_put(digit_pin_mapping[i], 1);
            // Check the logic of seven seg led before this step
            // GPIO pins are sending low signal and this is common anode system
            send_byte(~bits[i]);
            latch_data();
            sleep_ms(10);
            gpio_put(digit_pin_mapping[i], 0); // disable digit
            // printf("Akash Gaikwad!\n");
        }
    }

    return 0;
}
