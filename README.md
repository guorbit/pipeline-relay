# Pipeline Relay

Firmware for the Raspberry Pi Pico acting as an I2C-UART bridge between the OBC and the Jetson Nano.

## Sequence Diagram

```
    OBC         BRIDGE          JETSON
---------------------------------------
    |
    |
    |-------------->| Wire.write(data)
    |               |
    |               | (buffer data)
    |               |
    |-------------->| Wire.request(data)
    |               |-------------->| Serial.write(data)
    |               |               |
    |               |               | (change mode fr)
    |               |               |
    |               |<--------------| Serial.write(response)
    |               |               |
```
