# DSA
Learning material and examples for course AR207 at FE Tuzla
# Software requirements
To succesfully compile the firmware for the ESP8266 SOC we are going to use:
1. Ubuntu 18.04 OS
2. Makefile approach

In one of the below sections we will explain how to setup the toolchain on the Ubuntu 18.04 OS. You could use Win OS but it will require a little bit reading on your side. 
# Hardware requirements
For this course we will need following components:
- Node MCU Board (https://www.ebay.com/itm/313601387191?hash=item4904196ab7:g:KVoAAOSwBYpduobE) or any other ESP8266 based board.
- USB 2.0 to TTL UART Serial Converter CP2102 (https://www.ebay.com/itm/1PCS-6Pin-USB-2-0-to-TTL-UART-Serial-Converter-CP2102-STC-Replace-Ft232/284022352349?hash=item42210d29dd:g:1y4AAOSwLTZfbBhs)
- Wire jumpers [MM,FF,MF] (https://www.ebay.com/itm/40PCS-20cm-2-54MM-FF-FM-MM-Dupont-wire-jumper-cables-male-to-female-For-Arduino/312724733910?hash=item48cfd8bfd6:g:05sAAOSwlbZdSZ6E)

# Setting up the toolchain
1. Create folder DSA
```
mkdir DSA
```
2. Move to the created folder
```
cd DSA
```
3. Download ESP8266 RTOS SDK from the official espressif github page
```
git clone --recursive https://github.com/espressif/ESP8266_RTOS_SDK.git
```
4. Clone this repository
```
git clone https://github.com/semir-t/esp8266-dsa.git
```
5. Add following lines to your ~/.bashrc
```
export PATH=$PATH:~/DSA/xtensa-lx106-elf/bin
export IDF_PATH=~/DSA/ESP8266_RTOS_SDK
```
6. Run the following command
```
python -m pip install --user -r $IDF_PATH/requirements.txt
```
7. Open hello-world example
```
cd ~/DSA/ESP8266_RTOS_SDK/examples/get-started/hello_world
```
8. Configure PORT which will be used for flashin. At this point you should connect your ESP8266 board. After connecting run following command.
```
make menuconfig
```
9. In the menu, navigate to ```Serial flasher config``` > ```Default serial port``` to configure the serial port, where project will be loaded to. Confirm selection by pressing enter, save configuration by selecting < Save > and then exit application by selecting < Exit >.

>Note: 
  On Windows, serial ports have names like COM1. On MacOS, they start with /dev/cu.. On Linux, they start with /dev/tty.
10. Compile and flash hello-world example
```
make all
make flash
```
11. To see if “hello_world” application is indeed running, type ```make monitor```. Several lines below, after start up and diagnostic log, you should see “SDK version: xxxxxxx” printed out by the application.
