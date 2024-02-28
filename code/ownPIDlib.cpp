#include  <iostream>
// #include "Arduino.h"

double sample_time;

class PID
{
private:
    double min;
    double max;
    double prev_error;
    double integral;
    double Kp;
    double Ki;
    double Kd;
    double dt;

public:
    PID(double Kp, double Ki, double Kd) : dt(sample_time), max(255), min(0), Kp(Kp), Ki(Ki), Kd(Kd), integral(0), prev_error(0){};

    double calculate(double setpoint, double current_state)
    {
        double error = setpoint - current_state; // Error számítás

        double Op = Kp * error; // Proportional súlyozása

        integral += error * dt; // Integral rész számítása későbbre

        double Oi = Ki * integral; // Integral rész súlyozása

        double Od = Kd * (error - prev_error) / dt; // Derivative rész számolása és súlyozása

        double output = Od + Oi + Op; // Output a három tagból

        // outout max és min között?
        if (output < min)
            output = min;
        if (output > max)
            output = max;

        prev_error = error;

        return output;
    }
};


int main(){

double KpX = 1;
double KpY = 1;

double KiX = 0;
double KiY = 0;

double KdX = 0;
double KdY = 0;


PID pidX(KpX, KiX, KdX);
PID pidY(KpY, KiY, KdY);



while(true)
{








}




return 0;
}