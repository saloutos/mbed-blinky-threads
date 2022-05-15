/*
 * Copyright (c) 2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"

Thread thread;
Thread thread2;
DigitalOut led1(LED1);

volatile bool running = true;
volatile int cc = 0;

// Blink function toggles the led in a long running loop
void blink(DigitalOut *led)
{
    while (running) {
        *led = !*led;
        ThisThread::sleep_for(1000);
    }
}

void counting()
{
    while (running) {
        cc += 1;
        ThisThread::sleep_for(500);
    }
}

// Spawns a thread to run blink for 5 seconds
int main()
{   
    printf("Initital count: %d\n\r", cc); 
    thread.start(callback(blink, &led1));
    thread2.start(counting);
    ThisThread::sleep_for(5000);
    running = false;
    printf("Final count: %d\n\r", cc); 
    thread.join();
    thread2.join();
}