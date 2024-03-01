#include <iostream>
#include <fstream>
#include <iomanip>

std::ofstream file("plot.svg");

const int width = 10000;
const long double setpoint = 26.19231;
class PID
{
private:
    long double min;
    long double max;
    long double prev_error;
    long double integral;
    long double Kp;
    long double Ki;
    long double Kd;
    long double dt;

public:
    PID(long double min, long double max, long double Kp, long double Ki, long double Kd, long double dt) : dt(dt), max(max), min(min), Kp(Kp), Ki(Ki), Kd(Kd), integral(0), prev_error(0){};

    long double calculate(long double setpoint, long double current_state)
    {
        long double error = setpoint - current_state; // Error számítás

        long double Op = Kp * error; // Proportional súlyozása

        integral += error * dt; // Integral rész számítása későbbre

        long double Oi = Ki * integral; // Integral rész súlyozása

        long double Od = Kd * (error - prev_error) / dt; // Derivative rész számolása és súlyozása

        long double output = Od + Oi + Op; // Output a három tagból

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
        file << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"" << width << "\" height=\"300\">\n\n";
        file << "<line x1=\"40\" y1=\"0\" x2=\"" << width << "\" y2=\"0\" style=\"stroke:black;stroke-width:2\" />\n";
        file << "<line x1=\"40\" y1=\"0\" x2=\"40\" y2=\"100\" style=\"stroke:black;stroke-width:2\" />\n\n";
        file << "<line x1=\"40\" y1=\"" << std::setprecision(10) << setpoint << "\" x2=\"" << width << "\" y2=\"" << std::setprecision(10) << setpoint << "\" style=\"stroke:black;stroke-width:0.5\" />\n\n";
    }
    else
        throw(-1);
}

void inline finish_svg(long double x, long double y)
{
    file << "<text x=\"5\" y=\"30\" font-size=\"5\" fill=\"white\">" << x << "</text>\n";
    file << "<text x=\"5\" y=\"60\" font-size=\"5\" fill=\"white\">" << std::setprecision(10) << y << "</text>\n";
    file << "<text x=\"5\" y=\"90\" font-size=\"5\" fill=\"white\">" << std::setprecision(10) << setpoint << "</text>\n";
    file << "\n</svg>";
    file.close();
}

void inline plot(long double y, int x)
{

    file << "<circle cx=\"" << ((double)x) / 32 + 40 << "\" cy=\"" << y << "\" r=\"0.25\" fill=\"red\" />\n";
}

int main()
{

    long double min = -5;
    long double max = 5;
    long double Kp = 0.0;
    long double Ki = 0.5;
    long double Kd = 0.5;
    long double dt = 1;

    long double current_state = 0.0;

    PID pid(min, max, Kp, Ki, Kd, dt);

    bool not_close_enough = true;
    long double EPS = 0.00000001;

    int x = 0;

    try
    {
        make_svg();

        while (not_close_enough)
        {

            current_state += pid.calculate(setpoint, current_state);

            plot(current_state, x);
            x++;

            if ((current_state < (setpoint + EPS) && current_state > (setpoint - EPS)) || x > 30000 * 8)
            {
                not_close_enough = false;
            }

            // if (x % 40 == 0)
            // {
            //     current_state += (static_cast<float>(rand() % 3) - 1.5);
            // }
        }

        finish_svg(x, current_state);
    }
    catch (int fault)
    {
        if (fault == -1)
            std::cout << "Buta a kodod is te butus" << std::endl;
    }

    return 0;
}