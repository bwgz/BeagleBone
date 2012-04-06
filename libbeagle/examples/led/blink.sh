#!/bin/sh
#
# This script will blink the USER3 and another led connected
# to the specified GPIO pin.
#
# usage: blink.sh [ gpio_number ] [ blinks ]
#
# Defaults to GPIO number 72 (Expansion Header 8, Pin xx)

number=${1:-72}
max=${2:-10}
user3=/sys/class/leds/beaglebone::usr3
gpio=/sys/class/gpio/gpio${number}
delay=1

if [ ! -d ${gpio} ]
then
	echo $number > /sys/class/gpio/export
fi

if [ -d ${gpio} ]
then
	i=0
	while [ $i -lt $max ]
	do
		echo 1 > $user3/brightness
		echo high > ${gpio}/direction
		sleep $delay
		echo 0 > $user3/brightness
		echo low > ${gpio}/direction
		sleep $delay
		i=`expr $i + 1`
	done

	echo $number > /sys/class/gpio/unexport
fi
