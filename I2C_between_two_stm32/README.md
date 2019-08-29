I2C between two uC.

Note: Use 2K to 10K resistor to pull up SDA and SCL line.

How it work:

- When start, Master wait for 1 sec and send data to Slave.

- When sending is complete , Master turn led on and wait for 1 sec before read data from Slave.

- After read data from Slave conplete, both Master and Slave blink their led.
