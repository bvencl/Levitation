#include <iostream>
#include <fstream>

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

PID(double min, double max, double Kp, double Ki, double Kd, double dt) :
    dt(dt), max(max), Kp(Kp), Ki(Ki), Kd(Kd), integral(0), prev_error(0) {};

double calculate(double setpoint, double process_variable)
{

}


};