Project: Arduio based - Animated Jack-o-lantern
Name: Johnny - ThinkSchematics.com
Date: 7 Oct 2022
Last Modified: 10 Oct 2022

Background:
	Last year we made a paper mache jack-o-lanturn.  We put a fake candle into it, though this year we want
	to have some animation to it.  Would like to mount in some eyes inside that light up, move, to tack someone 
	walking in front of the jack-o-lanturn.  The eyes have LEDs in the to make them light up.  We are running
	a random variable to change the brightness of the LEDs.  It would be nice to have LEDs inside to light it up
	a bit.  Last we would like to add some audio that is motion activated, to play some "spooky" audio.

Things to do:  
	--Clean up code (make it run smother) - looking for help 
	--Consider putting LEDs on a 555 timer or some other circuit, so they don't stop flashing due to delays in code
	--Do some comparison between sensors... the servo is jumping back and forth
		--try to make it more natural eye movement
	--Consider using photo resistors or transistors instead of ultrasonic sensors to detect motion.  
	  Down side is the LEDs might cause bad readings.
	--Add SD card and audio out, then have it say "spooky stuff" when it detects something

Code samples/barrow/insperation/background info/recognition from following pages:
	Blinking an LED - https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
	Analog PWM - https://docs.arduino.cc/tutorials/generic/secrets-of-arduino-pwm
	Random number - https://www.arduino.cc/reference/en/language/functions/random-numbers/random/
	Datasheet found at: https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf