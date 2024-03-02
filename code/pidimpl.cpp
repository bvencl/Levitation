#include "ownpid.h"
// #include "Arduino.h"

int main()
{

    double KpX = 1.0, KiX = 0.0, KdX = 0.0;

    double KpY = 1.0, KiY = 0.0, KdY = 0.0;

    PID pidX(KpX, KiX, KdX);
    PID pidY(KpY, KiY, KdY);

    double setpointX;
    double setpointY;
    double current_stateX;
    double current_stateY;
    unsigned long lastSampleTime = 0; // Az utolsó mintavétel időpontja
    unsigned long sampleTime = 100;   // Mintavételi idő milliszekundumban

    while (true)
    {
        unsigned long now = millis();
        if (now - lastSampleTime >= sampleTime)
        {
            lastSampleTime = now; // Frissítjük az utolsó mintavétel időpontját

            // Itt hívd meg a PID számítását
            double outputX = pidX.calculate(setpointX, current_stateX);
            double outputY = pidY.calculate(setpointY, current_stateY);

            // További logika, pl. kimenet alkalmazása
        }
    }
}