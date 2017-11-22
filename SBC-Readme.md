# PAASMER-SBC

**Paasmer IoT SDK** for Single Board Computers Running Linux and cc3200

# Optional Requisites
* WiFi devices - Paasmer IoT is supports Belkin Wemo and Philips Hue bridge.
* Bluetooth Light - Paasmer IoT supports Magic Light smart LED bulbs.
* ZigBee modules

**Note- The WiFi devices must be connected to the local network same as that of your SBC.**

### Zigbee Requisites
In order to use the Zigbee the following is required.

* Single Board Computers.

* Arduino UNO Board.

* 2 ZigBee modules.

* XCTU Software installed on your system for ZigBee configuration. [XCTU software](https://www.digi.com/products/xbee-rf-solutions/xctu-software/xctu)

* Lastest version of Arduino IDE to installed on your computer. [Arduino software](https://www.arduino.cc/en/main/software)

# Installation

* Download the SDK or clone it using the command below.

```
$ git clone https://github.com/PaasmerIoT/SBC-C-SDK-V2_0_1_5.git
$ cd SBC-C-SDK-V2_0_1_5
```
* To install dependencies, follow the commands below

```
$ sudo chmod 777 ./*
$ sudo ./install.sh
```
This will take some time to install the required softwares and packages.

## Device Registration
The Device Registration can be done in two ways, either through Web UI or Using command line.

#### Using Command line

* To register the device to the Paasmer IoT Platform, the following command need to be executed.

```
$ sudo ./paasmerDeviceRegistration.sh
```

This will ask for the UserName and DeviceName. Give a unique DeviceName for your device and that must be alphanumeric without giving any spaces[a-z A-Z 0-9].

 
* After completion, Go to the `<Linux>` directory in the `<sample>` folder.
```
cd samples/linux/subscribe_publish_sample
```

* Edit the config.h file to include the feed names , feed types, connnectiontype and feed pin details. 

```c
#include "../../../details.h"

#define timePeriod 6 //change the time delay as you required for sending actuator values to paasmer cloud

char* feedname[]={"feed1","feed5"};  //Do not provide any spaces for the feeds.

char* feedtype[]={"actuator","sensor"}; //modify with the type of feeds i.e., actuator or sensor

int feedpin[]={3,8}; //modify with the pin numbers which you connected devices (actuator or sensor)

char* connectiontype[] = {"GPIO","zigbee"};

#define zigbeePort "/dev/ttyUSB0"  // comment this line if Zigbee is Used

#define wifiDiscover 1

#define bluetoothDiscover 1
```

#### Using Web UI
* Login to http://developers.paasmer.co/, create a device and fill the feed details.
* Click on `save` icon to save changes. 
* After completion, Go to the `SDK` directory and run the command below.

```
sudo ./Update.sh
```
* This will ask for the UserName, DeviceName and Password. Give the DeviceName which is created in the Web UI.
* This will automatically download the necessary credentials and the config file, and place them in the respective directory.

## ZigBee Configuration (Optional)

To establish, the ZigBee protocol the 2 ZigBee modules are to configured as a Coordinator and a Router. The ZigBee at the SBC side is to be configured as a Coordinator and the one at the Arduino side as a Router. Use XCTU software to Configure the ZigBee's as explained in the `ZigBEE_config.pdf` file.

The installation part is to be done in two parts, like

* Arduino  

* SBC 
 
## Arduino 

* Open a new Sketch, Copy and Paste from the `ZigBee.ino` file in `<Arduino Sketch_DIR>/`.

* Connect the Arduino UNO board to your system, open the Arduino IDE and click on the `TOOLS` icon, select the `Board` as **Arduino/Genuino UNO** and select the port in which the board is connected in the `Port` option. 

* Also edit the `config.h` in the Arduino Sketch similar to our `config.h` file in SBC. The code sample is as below,

```
#define devicename "Zigbee" //your device name

#define timePeriod 2 //change the time delay as you required for sending sensor values to paasmer cloud

char feedname[][10]={"Feed1","Feed2","Feed3","feed4","feed5","feed6"};

String feedtype[]={"sensor","sensor","sensor","actuator","actuator","actuator"};

String connectiontype[]= {"GPIO","GPIO","zigbee","GPIO","GPIO","zigbee"};

int feedpin[]={2,4,5,6,32,8};
```
* Save and Run the code in Arduino UNO.

* Connect the ZigBee Router device to the Arduino UNO as give below

| Arduino   | XBee |
| --------- | -----|
| 5V        | 5V   |
| GND       | GND  |
| TX        | RX   |
| RX        | TX   |

* Connect the ZigBee Coordinator device to the RaspberryPi through the USB2.0 cable. (Only if ZigBee is used)

## Execution 
   
* Compile the code and generate output file.
```
$ sudo make
```
* Run the code using the command below.

```
$ sudo ./subscribe_publish_sample
```

* The device would now be connected to the Paasmer IoT Platform and publishing sensor values are specified intervals.

* User can update the feed details for any Device in the WeB UI followed by running the below command *
```
sudo ./Update.sh
```

## Support

The support forum is hosted on the GitHub, issues can be identified by users and the Team from Paasmer would be taking up requests and resolving them. You could also send a mail to support@paasmer.co with the issue details for quick resolution.

## Note:

The Paasmer IoT SBC-C-SDK-V2_0_1_5 utilizes the features provided by AWS-IOT-SDK for C.

