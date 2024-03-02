#include "ownpid.h"

PID::PID(double Kp, double Ki, double Kd) : lasttime(0), max(255), min(0), Kp(Kp), Ki(Ki), Kd(Kd), integral(0), prev_error(0){};

//------------------------------------------------------------------
double millis();

void PID::setKp(double Kp)
{
    this->Kp = Kp;
}

void PID::setKi(double Ki)
{
    this->Ki = Ki;
}

void PID::setKd(double Kd)
{
    this->Kd = Kd;
}

void PID::setMin(double min)
{
    this->min = min;
}

void PID::setMax(double max)
{
    this->max = max;
}

double PID::getKp()
{
    return Kp;
}

double PID::getKi()
{
    return Ki;
}

double PID::getKd()
{
    return Kd;
}

double PID::calculate(double setpoint, double current_state)
{
    double error = setpoint - current_state; // Error számítás

    long double dt = millis() - lasttime; // idő számítása
    lasttime = millis();

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
