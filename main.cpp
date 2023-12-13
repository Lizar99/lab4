#include "InterruptIn.h"
#include "PinNames.h"
#include "mbed.h"

DigitalOut led_red (PA_10);
DigitalOut led_green (PA_8);
DigitalOut led_yelow (PB_5);
static auto sleep_time = 100ms;
static int a = 0;
InterruptIn ibutton1(BUTTON1);

void pressed() {
    a++;
    if (a>2)
    {
        a=0;
    }
}

void steadyMode() {
    led_red = 1;
    led_yelow = 1;
    led_green = 1;
}

void blinkMode() {
    led_red = !led_red;
    led_yelow = !led_yelow;
    led_green = !led_green;
    ThisThread::sleep_for(1s);
}

void runningLightsMode() {
    static int position = 0;
    if (position == 0) {
        led_red = 1; led_yelow = 0; led_green = 0;
    } else if (position == 1) {
        led_red = 0; led_yelow = 1; led_green = 0;
    } else {
        led_red = 0; led_yelow = 0; led_green = 1;
    }
    position = (position + 1) % 3;
    ThisThread::sleep_for(1s);
}

int main() {

    ibutton1.rise(&pressed);
    while (1) {
        switch (a) {
            case 0:
                steadyMode();
                break;
            case 1:
                blinkMode();
                break;
            case 2:
                runningLightsMode();
                break;
        }
    }
}



// int main() {

// int i = 0;
// led = 0;
// printf ("Hello World !\n");
// while(1) {
// ThisThread::sleep_for(1s);
// led = !led;
// printf("This programm runs since %d seconds. \n", i++);
// }

// }


// InterruptIn ibutton1(BUTTON1);
// static auto sleep_time = 1000ms;
// void pressed()
// {
//     // Управление скоростью мерцания светодиода
//     sleep_time += 1000ms;
//     if (sleep_time > 5000ms)
//         sleep_time = 1000ms;

// }
// int main()
// {
//     int i = 0;
//     led = 0;
//     printf("Hello World !\n");
//     ibutton1.rise(&pressed);
//     while (1)
//     {
//         led = !led;
//         ThisThread::sleep_for(sleep_time);
//         printf("This programm runs since %d seconds. \n", i++);
//     }
// }



// Thread thread;
// void print_thread()
// {
// while (true)
// {
// printf("Hello from thread\n");
// ThisThread::sleep_for(500ms);
// }
// }
// int main()
// {
// thread.start(print_thread);
// ThisThread::sleep_for(5s);
// int i = 0;
// led = 0;
// while(1) {
// ThisThread::sleep_for(1s);
// led = !led;
// }
// }


// Thread thread;
// #define PRINT_FLAG 66
// void print_thread()
// {
// while (ThisThread::flags_get() != PRINT_FLAG) {
// printf("Hello from Thread1 :D\n");
// ThisThread::sleep_for(500ms);
// }
// printf("Bye from Thread1\n");
// }
// int main()
// {
// thread.start(print_thread);
// ThisThread::sleep_for(5s);
// thread.flags_set(PRINT_FLAG);


// }

