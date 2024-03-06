#include "ownpid.h"
#include "Arduino.h"

// ENA és ENB sebességszabályozók az L298N-en

// #define makrók a pineknek
//
//
//
//
//
//
//____________

void reactX(int a)
{
    if (a >= 0)
    {
        digitalWrite(IN1, 1); // Az irány beállítása
        digitalWrite(IN2, 0); // Az irány beállítása
        analogWrite(ENA, a);  // Sebesség beállítása
    }
    else
    {
        a = -a;
        digitalWrite(IN1, 0);
        digitalWrite(IN2, 1);
        analogWrite(ENA, a);
    }
}

void reactY(int a)
{
    if (a >= 0)
    {
        digitalWrite(IN3, 0);
        digitalWrite(IN4, 1);
        analogWrite(ENB, a);
    }
    else
    {
        a = -a;
        digitalWrite(IN3, 1);
        digitalWrite(IN4, 0);
        analogWrite(ENB, a);
    }
}
    void setup()
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
    }

    void loop()
    {

        unsigned long now = millis();
        if (now - lastSampleTime >= sampleTime)
        {

            lastSampleTime = now;           // Frissítjük az utolsó mintavétel időpontját
            current_stateX = analog_read(); // pin ami kell
            current_stateY = analog_read(); // pin ami kell

            // Itt hívd meg a PID számítását
            double outputX = pidX.calculate(setpointX, current_stateX);
            double outputY = pidY.calculate(setpointY, current_stateY);

            reactX(outputX);
            reactY(outuputY);
        }
    }
