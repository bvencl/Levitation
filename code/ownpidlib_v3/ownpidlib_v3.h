#ifndef OWNPIDLIB_V3_H
#define OWNDIPLIB_V3_H

#include "Arduino.h"
#include <cmath>

long unsigned sample_time;

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
    long unsigned lasttime;

public:
    PID(double Kp, double Ki, double Kd);

    void setKp(double);
    void setKi(double);
    void setKd(double);
    void setMin(double);
    void setMax(double);

    double getKp();
    double getKi();
    double getKd();

    long int calculate(double, double);

};


#endif