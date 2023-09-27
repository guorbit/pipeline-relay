#include <Arduino.h>
#include <Serial.h>
#include <Wire.h>

#define SLAVE_ADDR 8

UART Serial2(0, 1, NC, NC);

int toJetsonBuf;

void sendUart(int state)
{
    char payload[2];
    payload[0] = state;
    payload[1] = '#';
    Serial.println(payload[0]);
    Serial2.println(payload);
}

String readUart()
{
    Serial.print("Input on UART1: ");
    char uartBuffer[20];
    int count = 0;
    while (count < 20)
    {
        uartBuffer[count] = Serial2.read();
        if (uartBuffer[count] == '#')
        {
            break;
        }
        count++;
    }
    uartBuffer[count] = '\0';
    char i2cBuffer[count];
    for (int i = 0; i < count; i++)
    {
        i2cBuffer[i] = uartBuffer[i];
    } 
    Serial.println(uartBuffer);
    return i2cBuffer;
}

// put functions here:
void i2cCommandHandler(int n)
{
    Serial.println(n);
    if (n == 0)
    {
        return;
    }
    Serial.print("I2C payload received: ");
    int buf = Wire.read(); 
    Serial.println(buf);
    
    toJetsonBuf = buf;
}

void i2cRequestHandler()
{
    Serial.print("Relaying data to Jetson: ");
    Serial.println(toJetsonBuf);
    sendUart(toJetsonBuf);
    sleep_ms(100);
    while (!Serial2.available())
        ;
    
    String payload = readUart();
    // String payload = "it";

    Serial.print("Relaying data to OBC: ");
    Serial.println(payload);

    Wire.write(payload.c_str());
}

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);

    /* while (!Serial)
        ; // wait for serial */
    Serial.print("Initializing IO Relay.");
    Wire.begin(SLAVE_ADDR);
    Serial.print(".");
    Wire.onReceive(i2cCommandHandler);
    Serial.print(".");
    Wire.onRequest(i2cRequestHandler);
    Serial2.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.println("\tDONE");
}

void loop()
{
    // put your main code here, to run repeatedly:
    digitalWrite(LED_BUILTIN, HIGH);
    delay(10);
    digitalWrite(LED_BUILTIN, LOW);
    delay(10);
}
