#include <iostream>
#include <fstream>

std::ofstream file("plot.svg");

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
    PID(double min, double max, double Kp, double Ki, double Kd, double dt) : dt(dt), max(max), min(min), Kp(Kp), Ki(Ki), Kd(Kd), integral(0), prev_error(0){};

    double calculate(double setpoint, double process_variable)
    {
        double error = setpoint - process_variable; // Error számítás

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

void inline make_svg()
{
    if (file.is_open())
    {
        file << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"10000\" height=\"100\">\n\n";
        file << "<line x1=\"20\" y1=\"50\" x2=\"10000\" y2=\"50\" style=\"stroke:black;stroke-width:2\" />\n";
        file << "<line x1=\"20\" y1=\"0\" x2=\"20\" y2=\"100\" style=\"stroke:black;stroke-width:2\" />\n\n";
        file << "<line x1=\"20\" y1=\"30\" x2=\"10000\" y2=\"30\" style=\"stroke:black;stroke-width:0.5\" />\n\n";
    }
    else
        throw(-1);
}

void inline finish_svg()
{
    file << "\n</svg>";
    file.close();
}

void inline plot(double y, int x)
{

    file << "<circle cx=\"" << x + 25 << "\" cy=\"" << (50 - y)  << "\" r=\"1\" fill=\"red\" />\n";
}

int main()
{

    double min = -2;
    double max = 2;
    double Kp = .1;
    double Ki = .14;
    double Kd = .6;
    double dt = 1;
    

    double setpoint = 20.677134;
    double process_variable = 0.121241;

    PID pid(min, max, Kp, Ki, Kd, dt);

    bool not_close_enough = true;
    double EPS = 0.000001;

    int x = 0;

    try
    {
        make_svg();

        while (not_close_enough)
        {

            process_variable += pid.calculate(setpoint, process_variable);

            plot(process_variable, x);
            x++;

            if ((process_variable < (setpoint + EPS) && process_variable > (setpoint - EPS)) || x > 30000)
                not_close_enough = false;

            if(x % 40 == 0)
                x++, x--;
        }

        finish_svg();
    }
    catch (int fault)
    {
        if (fault == -1)
            std::cout << "Buta a kodod is te butus" << std::endl;
    }

    return 0;
}