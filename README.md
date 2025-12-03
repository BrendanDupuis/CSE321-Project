# CSE 321 Project - Record Player RPM Detector

This is a project created by Brendan Dupuis and Enzo Mclauchlin for the UB CSE 321 Semester-long Project. This code when uploaded to an Arduino R3 Uno and configured with components and setup listed below will read the RPM of the currently-playing record, as well as track the amount of time gained or lost on a theoretical perfect-speed record player.

## Hardware Setup:
You will need these components:
- 1x Arduino R3 Uno (or Elegoo Uno R3)
- 1x TCS 3200 Color Sensor
- 1x I2C 20x4 LCD Matrix Display
- 9x Standard Jumper Wires
- 1x Y Cable Splitter Jumper Wire

Once these are obtained, follow these instructions:
1. Hook digital pins 8 to 12 into _____ [FILL IN WITH PROPER PIN INSERT]
2. Hook analog pins A4 and A5 into ___ and ___ on the I2C display respectivley.
3. Hook the seperate ground pins into GND on both the I2C display and the color sensor.
4. Hook the Y-cable into 5V, and the ends into VCC of the I2C display and color sensor.
5. _________ [DESCRIBE BUTTON LAYOUT]
6. Attach the microcontroller to your computer via serial port.

## Installation:
1. Clone the repository (can be done in a number of ways, if no knowledge how to then look up a tutorial).
2. Use an IDE such as Arduino IDE or Platform IO to verify and upload the code to the device over serial.

## Usage:
1. Find a brightly-colored sticker of reasonable size. Detectability may vary; in testing we found that red was most consistently detectible, though green or blue should be suitable. Make sure the sticker you use is not the same color as your record platter.  We reccomend a sticker larger than the length of your thumb, but smaller than a fourth of the total circumference of the record platter.

2. Place the sticker upon the side of the record platter, with the color clearly covering the decribed portion of the side of the record platter. Ensure that the sticker will not brush against any components of the player by slowly rotating the platter by hand in at least one full rotation, for if the sticker brushes other components or halts the platter, this could cause danmage to the player while running.

3. Align your device such that the sensor has a direct line of sight with the sticker / platter. The sticker should be no closer than thumb width and no further than two thumb widths for optimal function.

ALTERNATIVELY FOR STEPS 1 TO 3:

1. Find a brightly-colored piece of card stock of color described previously.

2. Make a hole punch the size of the record platter spindle, and cut the card stock such that it does not exceed the boundary of the label of the record, but extends to the furthest possible point, with a thickness and shape along the circular record label which is comperable to a slice of pie.

3. Extend the device in such a way that the sensor looms over the record player and does not get in the way of the needle, but has clear and close line of sight to the label in a similar way as to is described above.

(This "alternative" method is of far greater consistency, but requires construction of a mechanizm to hold the sensor above the record player, which is somewhat risky. Such an effect could be achieved by driving the jumper wires through a bendy wire holder such as those used in bendy portable reading lights. This method also only works if the top of your record player is accessible (any required close-top record players will not be able to do this) and the label must be a distinctly different color from the cardstock with no decernable color change across it.)

4. Power the device with the serial port to a standard power outlet connection.

5. The device will need to be calibrated upon startup. Line the sticker up with the sensor and press the button which you have wired for calibration, that being the button attached to digital pin ___ [FILL THIS IN].

6. Make sure the sensor gets a clear reading of the color of the sticker for the duration of its calibration, i.e. let the sticker or the sensor move as little as possible.

7. Start your record player right after calibration finishes! This will ensure that the "offset" time calculation is correctly oriented.

8. While in the starting countdown, press the "45RPM" button which you have wired to digital pin ___ [FILL THIS IN] to switch the mode of the device to 45RPM offset time calculation mode. If this is not done for a record which is supposed to spin at 45RPM, then the device will be improperly set for 33.3RPM offset time calculation by default.

9. Kick back and enjoy, or steadily calibrate your record player to the closest possible time.







