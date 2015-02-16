**********************
*Author: mynameistony*
**********************

*********************************************
This software is free to use,              
just please let me know, it's nice to hear 
that other people are using stuff I made :)
*********************************************
This is the sketch for my Arduino Valentines gift.

*************

*Description*

*************

This is the source for a gift I made for my Valentine <3

You push a button, and it will pulse an LED, and print out a nice message

//Still testing
//I've added a WiFi NTP client to update the time every 30 seconds
//It also uses an ultrasonic range finder as a motion sensing backlight toggle

You're on your own in designing and implementing it, but here are some photos of mine to get you started
https://imgur.com/a/8SGDb

There is a class can be created that contains encapsulates everything, you just create an instance with your pin configuration
and call a few key functions,
or you can pick and pull, I don't care.


*******
*Parts*
*******
--1x Arduino

--1x LED

--1x Button

--1x Serial LCD (or other)
	->Mine is a Parallax Serial LCD, I made a nice little class for that is used
	->You could use another but probably have to change some stuff

--1x WiFi Shield (not required)
	->This to get a network time, so it can be a clock too
	->If not using one, you will have to remove all the WiFi code

--1x HC SR04 Range Finder (not required)
	->For motion sensing light up

**************************************************
There is a class in "stuff.h" that will
have to be modified if not using the exact parts
**************************************************

