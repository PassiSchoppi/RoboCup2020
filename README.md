# RoboCup2020

## Documentation

### setLED(uint8_t color)

set's the color of the LED's to the color given as argument
include led.h and config.h so that you can use the names of
the colors as argument;  available colors: OFF, WHITE, RED,
GREEN, BLUE, PINK, YELLOW and TURQUOISE;  Serial3 has to be
started with the specific baud rate

### motorSetLeftSpeed(int16_t speed)

set's the speed of the left motor to the speed given as one
argument;  include motor.h to use this function

## motorSetRightSpeed(int16_t speed)

set's the speed of the right motors to the speed given as a
argument;  include motor.h to use this function

### motorBrake()

stops all motors so the robot stays; include motor.h to use
this function in your code

### pid(uint8_t motorSpeed, uint8_t distanceF, uint8_t distanceB, bool leftSide)

it is not really a pid controller, but it changes the given
motor speed so that the robot drives through any track with
two walls right and left; returns a float that represents a
speed that you can apply to the motor; the bool leftSide is
a argument that has to be true if you want to get the speed
for the left side; include pid.h to use it

### readSensor(uint8_t *sensorData)

reads all the sensor data and writs it in to the sensorData
since this is a call by refference you have to call it with
a & before the array that you put as argument;  you have to
include sensor.h to use it

### changeState(uint8_t *state, uint8_t *sensorData)

this function is the whole state maschine; as arguments you
have to put the current state as call by refference and all
the data given by the sensors; include state.h to use it

### isWall(uint8_t where, uint8_t *sensorData)

this function returns true when there is a wall;  you might
include config.h so that you can use FRONT, LEFT, RIGHT and
BACK as the where argument; you have to give it an array as
call by refference so that the function gets everything out
of the array

---

fuck me I hate documentation
