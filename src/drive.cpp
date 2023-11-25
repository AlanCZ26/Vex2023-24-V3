#include "main.h"
int PTOvar = 0;
void drivetrain(int l, int r){
    if (l == r == 0) {
        lMotor1.brake();
        lMotor2.brake();
        ltMotor.brake();
        rMotor1.brake();
        if (PTOvar == 0) {
            rMotor2.brake();
            rtMotor.brake();
        }
    } elif 

}