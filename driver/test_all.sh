#!/bin/bash
echo "Making driver..."
sudo make
echo "Loading driver..."
sudo insmod first_driver.ko 
dmesg | tail
echo "Unloading driver..."
sudo rmmod first_driver.ko 
dmesg | tail
echo "Cleaning..."
sudo make clean
echo "Test is finished"
