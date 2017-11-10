# SBC-C-SDK-V2_0_1_5
**Paasmer IoT SDK** for Single Board Computers Running Linux and cc3200

## Overview

The **Paasmer SDK** for **Single Board Computers (SBC)** like Raspberry-PI, Banana-PI, Orange-PI, Odroidxu4, BeagleBone and also for **CC3200 LaunchPad XL** is a collection of source files that enables you to connect to the Paasmer IoT Platform. It includes the transport client for **MQTT** with **TLS** support.  It is distributed in source form and intended to be built into customer firmware along with application code, other libraries and RTOS.This SDK is equipped with the Zigbee, WiFi and Bluetooth (BLE) protocol support along with Board GPIO's for SBC's.

## Features

The **SBC-C-SDK-V2_0_1_5** simplifies access to the Pub/Sub functionality of the **Paasmer IoT** broker via **MQTT**. The SDK has been tested to work on the **Raspberrp Pi 3, Banana-PI, Orange-PI, Odroidxu4 and BeagleBone** running Raspbian Jessie and on the **CC3200 LaunchPad XL** running TI-RTOS. Support for Other SBC's running any flavors of Linux would be available shortly.

## MQTT Connection

The **SBC-C-SDK-V2_0_1_5** provides functionality to create and maintain a mutually authenticated TLS connection over which it runs **MQTT**. This connection is used for any further publish operations and allow for subscribing to **MQTT** topics which will call a configurable callback function when these topics are received.

##Protocols Supported

The **SBC-C-SDK-V2_0_1_5** is equipped with the Zigbee, WiFi and Bluetooth (BLE) protocol support along with Board GPIO's for **Single Board Computers (SBC)** only.

## Pre Requisites

Registration on the portal http://developers.paasmer.co, is necessary to connect the devices to the **Paasmer IoT Platfrom** .

## Installation
* For SBC, refer SBC-Readme.md
* For CC3200, refer CC3200-Readme.md
