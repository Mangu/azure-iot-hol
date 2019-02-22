# Lab 1b: Feedbox Device Simulator

This lab replaces lab 1 and lab 2. After completing this lab, you can move on to lab 3.

## 1. Download the Device Simulator
The Feedbox device simulator allows you to complete the hands on labs without requiring a physical device. To run the simulator, download and upzip [Simulator.zip](/Simulator.zip).

## 2. Create an IoT Hub

You can create an IoT hub using the following methods:

1. The + New option opens the blade shown in the following screen shot. The steps for creating the IoT hub through this method and through the marketplace are identical.
2. In the Marketplace, choose Create to open the blade shown in the following screen shot.
3. Provide a name and a resource group. You can use a free tier but only one free tier is available per subscription.

![Create IoT Hub](/images/create-iothub.png)

While you are in the Azure portal, let's go ahead and grab a couple of important connection parameters.

4. In the IoT Hub blade of the Azure portal for your created IoT Hub, do the following:

1. Copy the "Hostname" and paste it into notepad
2. In the left-hand nav bar, click on "Shared Access Policies" and then click on "iothubowner", copy the "Connection String - Primary Key" string and paste it into Notepad.  We'll need it later.  This is your "IoTHub Owner Connection string" (keep that in mind, or make a note next to it in Notepad, we will use it in subsequent labs).  
3. Close the "Shared Access Policy" blade

## 3. Add a device

1. In the left-hand nav bar, click on "IoT Devices"
2. click "Add"
3. Give your IoT Device a name and click "Save"
4. Once created, you will shown as list of devices. Find your device and click on it. On the device details screen find connection string (primary key) and copy/paste this into Notepad.  This is the "IoT Device" connection string
5. Paste the connection string into the device simulator and press the connect button
6. Once connected, you can change the temperature and humidity slide and press one of the sentiment button to cast a vote

## 4. Monitor device events

1. Click on the Cloud Shell icon located on the top bar of the portal  ">_"
2. Install the IoT Hub CLI extension `az extension add --name azure-cli-iot-ext`
3. To monitor the messages sent to IoT Hub, from the Cloud Shell type `az iot hub monitor-events  -n {hubname}` where {hubname} is th the name of your IoT Hub

>Note: you can now move to lab 3.