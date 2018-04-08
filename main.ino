void setup()
{
    pinMode(13, OUTPUT);
}

void loop()
{
    static int potPosition;
    potPosition = analogRead(A0);
    digitalWrite(13, HIGH);
    delay(2000)
    digitalWrite(13, LOW);
    delay(2000)
}