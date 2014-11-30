#!/bin/bash
echo "START driver load/unload testing"
echo "Loading driver..."
sudo insmod first_driver.ko 
dmesg | tail
echo "Unloading driver..."
sudo rmmod first_driver.ko 
dmesg | tail
echo "FINISH"
