#!/bin/bash

sleep 3

while ! sudo /home/abir/pi-car/move; do 
    sudo bluetoothctl select F4:4E:FC:60:50:23
    sudo bluetoothctl connect E0:F6:B5:24:D1:6C
    echo "command failed"
    sleep 3
done 

echo "command succeeded"