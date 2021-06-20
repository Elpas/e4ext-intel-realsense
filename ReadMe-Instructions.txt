to launch navigate to folder and type:


cd  /home/pi/Uri/Intel/clone5/RealSenseID/samples/cpp/build
./authenticate-cpp-sample "192.168.0.64" 8093 11 "/dev/ttyACM0"

"192.168.1.200"    - ip
8093  - port
11-reader id lf in omni
"/dev/ttyACM0"    - the usb port name


use this command to find out port connected :
sudo dmesg | grep 'Intel F450' -A 5 | grep ttyACM
and only probably change the acm0 to acm1 etc...


to tun the command line to declare faces on PI:
-------------------------------------------------------
cd  /home/pi/Uri/Intel/clone5/RealSenseID/build/bin
./rsid-cli  "/dev/ttyACM0"



*when exported to new PI need to copy  librsid.so  


