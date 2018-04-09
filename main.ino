#include "Arduino.h"

void setup()
{
}

void loop()
{
    static int potPosition;
    potPosition = analogRead(A2);
}