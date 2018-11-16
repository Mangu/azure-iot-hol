## Module 4 - Communicating with the device

Another common pattern in IoT is to execute commands remotely on a device. You saw this in the hardware portion of this workshop by sending a message to the device via a topic. Since our devices are connected via IoT Hub, we will let IoT Hub handle the communication to the device.

In the overview session, we talked about the three different ways to communicate with a device; desired properties, direct methods and C2D messages. In this module, we are going to use a direct method to send a command to the device. 

Instead of giving you the steps by step instructions, since this is the last module, we will provide general guidance and assist as needed.

To complete the loop, we want to alert send an alert when the temperature rises above a given threshold.

>Hint: Since we already process each message in notify function, you could add the temperature alert logic there. 

