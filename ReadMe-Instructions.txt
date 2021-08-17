to launch navigate to folder and type:
cd  /home/pi/Uri/Intel/clone5/RealSenseID/samples/cpp/build

since if inserted code into git it compiles without the window I save the whole file in 7z and update all the changes at once!!!
so just unzip WINDOWS.7z


How to compile code on windows:
----------------------------------------------
you can see https://github.com/IntelRealSense/RealSenseID
*extract RealSenseID-v.21.0.zip
*in cmd  :  cd C:\Elpas\e4ext-intel-realsense\WINDOWS\tools 
*cmake .. -DRSID_PREVIEW=1  
*open project C:\Elpas\e4ext-intel-realsense\try2\RealSenseID-v.21.0\tools\ALL_BUILD.vcxproj
*rsid-viewer set as startup project and run


*cd C:\Elpas\e4ext-intel-realsense\try2\RealSenseID-v.21.0\samples\tools
*cmake .. -DRSID_PREVIEW=1  



./authenticate-cpp-sample "192.168.0.64" 8093 11 "/dev/ttyACM0"

"192.168.1.200"    - ip
8093  - port
11-reader id lf in omni
"/dev/ttyACM0"    - the usb port name


use this command to find out port connected :
--------------------------------------------------------
sudo dmesg | grep 'Intel F450' -A 5 | grep ttyACM
and only probably change the acm0 to acm1 etc...


to tun the command line to declare faces on PI:
-------------------------------------------------------
cd  /home/pi/Uri/Intel/clone5/RealSenseID/build/bin
./rsid-cli  "/dev/ttyACM0"



*when exported to new PI need to copy  librsid.so  


to update firmware:
----------------------------------------
in directory:
pi@raspberrypi:~/Uri/Intel/clone6/RealSenseID-v.21.0/build/bin $ 

./rsid-fw-update --file "/home/pi/Uri/Intel/clone6/RealSenseID-v.21.0/build/bin/F450_3.1.0.29_SKU1_SIGNED.bin" --port COM3 --force-version



./rsid-fw-update --file "/home/pi/Uri/Intel/clone6/RealSenseID-v.21.0/build/bin/F450_4.0.0.37_SKU1_SIGNED.bin" --port  "/dev/ttyACM0"



