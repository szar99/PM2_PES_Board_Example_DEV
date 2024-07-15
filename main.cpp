#include "mbed.h"

// pes board pin map
#include "pm2_drivers/PESBoardPinMap.h"

// drivers
#include "pm2_drivers/DebounceIn.h"
#include "pm2_drivers/Stepper.h"
#include <chrono>
//#include "pm2_drivers/Stepper.h"

bool do_execute_main_task = false; // this variable will be toggled via the user button (blue button) and
                                   // decides whether to execute the main task or not
bool do_reset_all_once = false;    // this variable is used to reset certain variables and objects and
                                   // shows how you can run a code segment only once

// objects for user button (blue button) handling on nucleo board
DebounceIn user_button(USER_BUTTON); // create DebounceIn object to evaluate the user button
                                     // falling and rising edge
void toggle_do_execute_main_fcn();   // custom function which is getting executed when user
                                     // button gets pressed, definition below

// main runs as an own thread
int main()
{
    // attach button fall function address to user button object, button has a pull-up resistor
    user_button.fall(&toggle_do_execute_main_fcn);

    // while loop gets executed every main_task_period_ms milliseconds, this is a
    // simple approach to repeatedly execute main
    const int main_task_period_ms = 20;  // define main task period time in ms e.g. 20 ms, there for
                                        // the main task will run 50 times per second
    Timer main_task_timer;              // create Timer object which we use to run the main task
                                        // every main_task_period_ms

    // led on nucleo board
    DigitalOut user_led(USER_LED);

    //Stepper stepper(PB_14, PC_4, 1.0f, 200);
    //Stepper stepper(PB_14, PC_4);

    //Stepper stepper(PB_12, PA_15, 1.0f, 200);
    DigitalOut step(PB_14);
    DigitalOut dir(PC_4);
    DigitalOut enableStepper(PB_1);
    //DigitalOut cs()

    //DigitalOut halfstep(PC_5);

    enableStepper.write(0);
    dir.write(1);

    //halfstep.write(1);

    // start timer
    main_task_timer.start();

    while (true) {
        main_task_timer.reset();

        if (do_execute_main_task) {
            step.write(1);
            thread_sleep_for(1);
            step.write(0);
            thread_sleep_for(1);

            
            // stepper.startRotation();
            //stepper.setAbsolutePosition(600);
        } else {
            // the following code block gets executed only once
            if (do_reset_all_once) {
                do_reset_all_once = false;
                // stepper.stopRotation();
                // //stepper.setAbsoluteZeroPosition();
                // stepper.setSpeed(-1.0f);
                // stepper.startRotation();
            }

        }

        // printf("%f \n", stepper.getPosition());
        // toggling the user led
        user_led = !user_led;
        // read timer and make the main thread sleep for the remaining time span (non blocking)
        // int main_task_elapsed_time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(main_task_timer.elapsed_time()).count();
        // thread_sleep_for(main_task_period_ms - main_task_elapsed_time_ms);
    }
}

void toggle_do_execute_main_fcn()
{
    // toggle do_execute_main_task if the button was pressed
    do_execute_main_task = !do_execute_main_task;
    // set do_reset_all_once to true if do_execute_main_task changed from false to true
    if (do_execute_main_task)
        do_reset_all_once = true;
}

