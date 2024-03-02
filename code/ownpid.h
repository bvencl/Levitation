#ifndef OWNPID_H
#define OWNDIP_H


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

    double calculate(double, double);

};


#endif