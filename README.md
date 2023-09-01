    OBC         BRIDGE          JETSON
---------------------------------------
    |
    |
    --------------->| Wire.write(data)
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