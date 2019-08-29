I2C between two uC.

Note:
Speed : 400Khz.
Use 2K to 5K resistors to pull up SDA and SCL line (5V).

How it work:

- When start, Master wait for 1 sec and send data to Slave.

- When sending is complete , Master turn the led on and wait for 1 sec before read data from Slave.

- After read data from Slave conplete, both Master and Slave blink their led.
