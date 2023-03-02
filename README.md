# Autonomous Robotic Car

## Project goals

Project to create an autonomous, wheeled robotics platform capable of navigation.

## Restrictions

There is a robotics competition we might aim to join with this platform; the Firefighting Contest (rules available on Google Drive and ARC Discord channel). The competition rules imposes some restrictions:

* The robot should roughly fit within 30x30x30cm.
* The robot should be able to navigate a noisy environment (a miniature apartment with optional furniture and colored walls with posters).
* The robot should be able to put out a candle (several options available, not related to the moving platform itself).

## Technology areas

### Movement

The robot should be able to move around and navigate a maze. It's proposed to use differential drive with two stepper motors mounted on opposite sides of the robot in east-west direction, and to use two free-moving ball-joints mounted in the north-south direction. This would allow full movement speed back and forward, and allow turning on the spot.

What motors to use?
    - We have some micro motors RH158.12.75.

Test controlling the motors using a motor driver:
    - DC motor control shield with BTN8982 Infineon
    - Controlled by arduino
* TODO: Test Encoders in Wheel mockup
    - Using reflective sensors Pololu IRS01A with pattern on wheel inside

* TODO: The platform movement solution must be able to move the platform properly:
    - What is the target speed?
    - What weight will the platform including payload have?
    - What inclination/rough terrain should we aim for?
* TODO: Should we use suspension to give the robot some ability to navigate uneven terrain?

### Power solution

The robot must be able to move autonomously without a connected power cable. The battery/batteries must be able to power the motors, any computational modules, sensors etc.

* TODO: What power planes must we have?
    - Probably 24V?
    - Maybe 12V?
    - 5V/3.3V for peripheral boards?
* TODO: Fuses etc.
* TODO: Power control (power on/off, panic button, start button etc.)

It's possible that some modules can power others (smaller boards powered by USB for example), but the motors should be directly driven from DC power supply.

Physical wiring must also be considered (what modules connect to where, how are cables drawn, is there any EMC issues from having certain cables close to each other etc.)

### Sensors

At first an idea was to use a XBox One Kinect for vision, but there are some downsides to this approach. There is a minimum distance of ~50cm until the Kinect is able to use depth information. The Kinect also has a rather bulky power supply.

A combination of many different sensors would make for a robust perception system.

* XBox 360 Kinect:
    - TODO: Worth investigating? We have a lot of them.
    - TODO: ~70cm until depth works?
    - TODO: Power consumption?
* XBox Kinect:
    - ~50cm until depth works. Verified.
    - TODO: Power consumption?
* Conventional cameras:
    - TODO: What resolution? How many? Lenses?
* IR cameras?
* IR distance sensors?
* Ping distance sensors?
* LIDAR?
* Tactile sensors (bumpers)?

### Computation

* NUC-style computer?
* Odroid/RaspberryPi?
* Arduino-style for low level peripherals?

### Software

* TODO: What base platform(s) to use? Closely related to the computation device.
* Linux-based system?
    - Can use ROS/ROS2?
    - Vision frameworks etc.?
* RTOS-based system?
* Bare-metal code (Arduino etc.)?

Revisit when computational platform has been decided on.

What language(s) to use?

* C/C++?
* Python?
* Other?


