# Azure IoT Edge Hands On Labs - Module 1

Created and maintained by the Microsoft Azure IoT Global Black Belts

## Create an IoT Hub


You can create an IoT hub using the following methods:

* The + New option opens the blade shown in the following screen shot. The steps for creating the IoT hub through this method and through the marketplace are identical.

* In the Marketplace, choose Create to open the blade shown in the following screen shot.

* Provide a name and a resource group. You can use a free tier but only one free tier is available per subscription.

![Create IoT Hub](/images/create-iothub.png)

While you are in the Azure portal, let's go ahead and grab a couple of important connection parameters and create an IoT Edge Device

In the IoT Hub blade of the Azure portal for your created IoT Hub, do the following:
* In the left-hand nav bar, click on "Shared Access Policies" and then click on "iothubowner", copy the "Connection String - Primary Key" string and paste it into Notepad.  We'll need it later.  This is your "IoTHub Owner Connection string" (keep that in mind, or make a note next to it in Notepad, we will use it in subsequent labs).  
* Close the "Shared Access Policy" blade

## Add a device

* In the left-hand nav bar, click on "IoT Devices"
* click "Add"
* Give your IoT Device a name and click "Save"
* Once created, you will shown as list of devices. Find your device and click on it. On the device details screen find connection string (primary key) and copy/paste this into Notepad.  This is the "IoT Device" connection string


