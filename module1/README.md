# Azure IoT Edge Hands On Labs - Module 1

Created and maintained by the Microsoft Azure IoT Global Black Belts

## Create an IoT Hub


You can create an IoT hub using the following methods:

* The + New option opens the blade shown in the following screen shot. The steps for creating the IoT hub through this method and through the marketplace are identical.

* In the Marketplace, choose Create to open the blade shown in the following screen shot.

* Provide a name and a resource group. You can use a free tier but only one free tier is available per subscription.

![Create IoT Hub](/images/create-iothub.png)

While you are in the Azure portal, let's go ahead and grab a couple of important connection parameters.

In the IoT Hub blade of the Azure portal for your created IoT Hub, do the following:
* Copy the "Hostname" and paste it into notepad
* In the left-hand nav bar, click on "Shared Access Policies" and then click on "iothubowner", copy the "Connection String - Primary Key" string and paste it into Notepad.  We'll need it later.  This is your "IoTHub Owner Connection string" (keep that in mind, or make a note next to it in Notepad, we will use it in subsequent labs).  
* Close the "Shared Access Policy" blade

## Add a device

* In the left-hand nav bar, click on "IoT Devices"
* click "Add"
* Give your IoT Device a name and click "Save"
* Once created, you will shown as list of devices. Find your device and click on it. On the device details screen find connection string (primary key) and copy/paste this into Notepad.  This is the "IoT Device" connection string


## Connect a device using an MQTT client

One of the ways to connect a device to IoT Hub is using a MQTT client. We are going to use the same sketch we used earlier and only change the MQTT server connection information.

In the sketch, hange the following variables:   

* For the **ClientId** field, use the **deviceId**.

* For **Server** use your `{iothubhostname}`

* For the **Username** field, use `{iothubhostname}/{device_id}/api-version=2016-11-14`, where `{iothubhostname}` is the full CName of the IoT hub.

    For example, if the name of your IoT hub is **contoso.azure-devices.net** and if the name of your device is **MyDevice01**, the full **Username** field should contain:

    `contoso.azure-devices.net/MyDevice01/api-version=2016-11-14`

* For the **Password** field, use a SAS token. The format of the SAS token is the same as for both the HTTPS and AMQP protocols:

  `SharedAccessSignature sig={signature-string}&se={expiry}&sr={URL-encoded-resourceURI}`

* To generate a sas token, we are going to use the IoT Hub extensions of the CLI
  1. Click on the Cloud Shell icon located on the top bar of the portal  ">_"
  2. Install the IoT Hub CLI extension `az extension add --name azure-cli-iot-ext`
  3. Run `az iot hub generate-sas-token -d {deviceid} -n {hubname} -du 63072000 `
    * Make sure to replace {deviceid} and {hubname} with your own values.
    * -du is the duration time of the token. 63072000 represents a year.
  4. Upload the sketch

* To monitor the messages sent to IoT Hub, from the Cloud Shell type `az iot hub monitor-events  -n {hubname}` where {hubname} is th the name of your IoT Hub

