/*
This is for program to display 0-9 digits every second on single 
seven segment led display with one 74HC594 shift register on 
Raspberry Pi Pico board.
-Akash
*/

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#define DATA_PIN    13
#define CLOCK_PIN   15
#define LATCH_PIN   14

// Define the bit Pattern for each digit (0-9)
const uint8_t bits[10] = {
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

void send_bit(int value) {
    gpio_put(DATA_PIN, value);
    gpio_put(CLOCK_PIN, 1);
    gpio_put(CLOCK_PIN, 0);
}

void send_byte(int value) {
    for (int i = 0; i < 8; i++) {
        send_bit(!!(value & (1 << (7 - i))));
    }
}

void latch_data() {
    gpio_put(LATCH_PIN, 1);
    gpio_put(LATCH_PIN, 0);
}

int main() {
    stdio_init_all();
    gpio_init(DATA_PIN);
    gpio_init(CLOCK_PIN);
    gpio_init(LATCH_PIN);
    gpio_set_dir(DATA_PIN, GPIO_OUT);
    gpio_set_dir(CLOCK_PIN, GPIO_OUT);
    gpio_set_dir(LATCH_PIN, GPIO_OUT);

    while (true) {
        for (int i = 0; i < 10; i++) {
            send_byte(bits[i]);
            latch_data();
            sleep_ms(1000);
            printf("Akash Gaikwad!\n");
        }
    }

    return 0;
}