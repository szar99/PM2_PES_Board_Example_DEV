#include "mbed.h"
#include "Stepper.h"
 
// initialise PWM
Stepper stepperMotor(PB_14,PC_4); // step, dir
Stepper stepperMotor2(PB_12,PA_15); // config 2

DigitalIn user_button(USER_BUTTON);
 
DigitalOut led(LED1);

DigitalOut enableStepper(PB_1);

int main() {
	// set stepper velocities and rotation directions
    stepperMotor.setSpeed(7000);
    stepperMotor.rotate(stepperMotor.CW);
    stepperMotor.stop();
    stepperMotor.setPositionZero();
    
    stepperMotor2.setSpeed(7000);
    stepperMotor2.rotate(stepperMotor.CW);
    stepperMotor2.stop();
    stepperMotor2.setPositionZero();
    
    bool buttonNow = false;
    bool buttonBefore = false;
    
	// enable must be set to LOW in order to turn on the stepper drivers
    enableStepper = 0;
    
    printf("initialization succesfull\n\r");
    
    while(1) {
        
        buttonNow = !user_button;
        // detect rising edge button
        if(buttonNow && !buttonBefore) {
            led = 1;
            // test stepper motor
            stepperMotor.goesTo(20*2048);
            stepperMotor2.goesTo(20*2048);
            wait(3.0f);
            //stepperMotor.stop();
            //stepperMotor2.stop();
            stepperMotor.setPositionZero();
            stepperMotor2.setPositionZero();
        }
        
        led = !led;
        
        wait(0.2); // 200 ms
    }
}
