#include <Arduino.h>
#include <Serial.h>
#include <Wire.h>

#define SLAVE_ADDR 8

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);
    while (!Serial)
        ; // wait for serial
    Serial.print("Initializing OBC InfraMock... ");
    Wire.begin();
    Serial.println("DONE");
}

void loop()
{
    // put your main code here, to run repeatedly:
    Serial.println("Waiting on input from operator... ");
    while (!Serial.available())
        ;
    int state = Serial.read();
    Serial.print("Input provided: ");
    Serial.println(state);

    Wire.beginTransmission(SLAVE_ADDR); // begin exchange with slave
    Wire.write(state );                // write to i2c buffer
    Wire.endTransmission();             // flush i2c buffer

    int n = 2;
    Serial.print("requesting data from relay...");

    Wire.requestFrom(SLAVE_ADDR, n); // request 6 bytes from slave
    char buf[n];
    Serial.println("DONE");
    for (int i = 0; i < n; i++)
    {

        buf[i] = Wire.read();
    }
    for (int i = 0; i < n; i++)
    {
        Serial.print(buf[i]);
    }
    Serial.println();


}
