### Introduction
The purpose of this lab is to get an IoT device connected to and talking to Azure IoTHub and the RM-PCS.  While this is demo device in a demo situation, it is very representative of the process of connecting any device to Azure.  We will leverage the Raspberry PI 3 (mac or pc are also options) but will simulate the sensor data.  The connection to Azure will leverage a Python script running on Linux, which is a very common IoT development environment.  However, it is certainly not the only option.  The Azure IoT Device SDKs leveraged for this lab are also available in the following languages:

* C
* Java
* C#
* Python
* Node.js

>NOTE: Other modules throught out the lab have references to an LED as evidance of an action. Since we are simulating the sensors and LED, you will need to confirm the action via the console logs

It has also been tested and used on these platforms:

* Linux
* Windows (universal – desktop and mobile)
* Various Real-Time OS’s (RTOS), including FreeRTOS, Arduino, and many others
* IOS
* Android
 

In this series of labs, you will:

1. Create and navigate the Azure IoT Remote Monitoring Pre-Configured Solution (RM-PCS)
2. Create a device to read a temperature and humidity sensor and send that data to the RM-PCS for display
3. Create a Stream Analytics job that looks for ‘high temperature’ alerts and outputs that alert to a queue for further processing
4. Create an Azure Function that takes that alert, and sends a command to the device to turn on or off an LED (which will be simulated on the console) depending on the alert condition.
    
At the end of this lab you will have a physical IoT device connected to Wifi, sending telemetry data to Azure IoT, and listening to and responding to commands from Azure.

#### Step 1 - Connected to and powering your RPI
>NOTE:  this lab was written assuming your network policy do not allow them to use SSH on their network.  The RPI connect to the network using wireless, and use the console cable to connect from their laptop to their RPI.  If you are on a network where you can SSH into the RPI directly, you can skip this section.

At this point, we are almost ready to power up our RPI.  Before we do, let’s connect our console cable so we can watch the PI boot.

While our RPI will connect over Wifi to the Internet (and Azure), and our laptops will also connect over Wifi to the Internet on the same network, corporate policy will not allow you to SSH from your laptop to the RPI directly.  So, we must connect over serial console with the USB/TTL cable.

To use the cable, we \*may\* need to install a driver (Windows boxes may auto-download), and do some configuration (and install a terminal client, in the case of Windows).

To set up the connection, follow the instructions (with the caveats below) at https://learn.adafruit.com/adafruits-raspberry-pi-lesson-5-using-a-console-cable?view=all
Caveats:

* The serial console has already been enabled on your RPIs, so you can skip down to the     software installation section about mid-way down the page
* Make sure you get the right drivers for your machine (PC vs. Mac)
* For the actual connection of the console cable to your RPI, follow the picture in the previous section, not the instructions on the site
* **DO NOT** connect the red cable from the USB/TTL cable.   We will be powering our RPI externally.

Once the PI is up and going.  Log in with username ‘pi’ and password ‘raspberry’.  To check network connectivity, try ‘sudo ping 8.8.8.8’ (CTRL-C to stop).

Congrats!  You and up and running and ready to talk to Azure!
 
#### Step 2 - Gathering IDs, Keys, and Connection Strings

Before we can connect the device to the Azure RM-PCS, we need to let the solution know about the device (so we can authenticate).  

1.	Navigate to your RM-PCS solution   (https://\[solutionname\].azurewebsites.net)
2.	On the bottom left corner, click the “Add a device” button
 
3.	Click Add New under “Custom Device”
4.	On the next screen, change the radio buttons to “let me define my own Device ID”, and pick a deviceID for your device
 ![Custom Device](/images/m2AddDevice.png) 
5.	Click Create
6.	Your device is now added to the RM-PCS.  Copy the three parameters displayed on this page, Device ID, IoTHub Hostname, and Device Key.  Paste them into notepad, as we will need them in the next step
7.	Click Done.  On the Devices screen, see that your device has been added to the list of devices in the solution.

#### Step 3 - Posting Telemetry data to Azure 
The code to read from your DHT22 sensor and post to Azure has been provided as part of this lab.  Now that we have our keys, strings, etc, we’ll need to download it, modify it for your specific RM-PCS solution details, run it, and test it.  Follow the steps below to get started

1.	On the RPI, we need to download the code.  We’ve provided the python script, and also pre-compiled the python SDK for your use.  If you are interested in the steps to compile the python module yourself if you need to start from scratch, see the details in Appendix B
2.	To download the code, enter these commands on the RPI

        cd ~
        git clone –recursive https://github.com/AzureIoTGBB/AzureIoTHandsOnLabs
        cd AzureIoTHandsOnLabs/Module2c
        
3.	The code is downloaded, now we need to put the details for your specific device, RM-PCS, and (just for fun), location
4.	edit the lab2c.py script with your favorite linux editor.  If you don’t have one, use nano

        nano lab2c.py
    
5. Read through the code, which is well commented, and make sure you understand what it is doing.

6. Scroll down to line 17  (you can see what line you are on by typing “CTRL-C”).  Line 17 is where you enter the connection details you got from the “add device” process in the previous step.  Copy/paste your host name, device id, and device key you copied into the placeholders (make sure to delete the < and > signs).  Full screening ‘putty’ allows you to see more of the line at once.

    Values to change: 

        deviceID = "<yourdeviceID>"
        deviceKey = "<yourdevickey>"
        iotHubHostName = "<youriothubname>.azure-devices.net"
        #ex: myiothub.azure-devices.net

7. go to http://www.bing.com/maps and search for your home, your home town, or some other location that interests you.  On the map you can see the latitude and longitude.  Substitute those values into the line above (you’ll need to arrow out to the right to get to it). 

    Put the lat and long of your fav place here otherwise we default to the center of the football universe
        
            latitude = 33.208350
            longitude = -87.550320

8. Save the file.  If you are using nano as the editor, hit CTRL-O, <enter>
9. Close the file (CTRL-X in nano)
10. Execute the script   (‘python lab2c.py’ from the command prompt)
11. You should see the DeviceInfo string echo’ed to the screen and sent to the IoTHub, the default "reported properties" sent, and then every 5 seconds, you should see the temperature and humidity (in a JSON string) sent to the IoTHub.  The LED should also briefly flash to indicate we are sending data (which will be simulated on the console)
12. Congratulations, you’ve connected a physical IoT device to the Azure IoT RM-PCS.  Next we can look at the telemetry, as well as test manually sending a command to the device from the portal, which we will do in the next step

#### Step 4 -  Posting Telemetry data to Azure 

Now we can take a look at the RM-PCS portal and make sure everything is working before we move on to the next lab.

1. Navigate to the RM-PCS portal for your solution (https://\[solutionname\].azurewebsites.net)
2. Look on the map and you should see your device.  You can either click on that device, or from the “Devices to View” drop down, you can select your device.  You should see the temperature and humidity displayed there, and it should match the data you see flowing from the RPI via your putty console

3. Feel free to hold your fingers over the DHT22 sensor, or breath on it, to vary the temperature and humidity and watch the values change on the portal

4. After looking at the telemetry data, click on the “Devices” tab on the left hand nav

5. Choose your device from the list by clicking on it.  Once the Device Details pops out from the right hand side, choose “Commands” to go to the commands page.

6. From the Select A Command box, you should see the two commands that we told the RM-PCS we support via the DeviceInfo message we sent from the device, “ON”, and “OFF”.
-
7. Choose “ON” from the drop down and choose “Send Command”.  The LED (which will be simulated on the console) on the device should light, and you should see this message appear in your RPI console
![Console](/images/m2Console.png)  
8. Now select the “OFF” command from the drop down and send the command.  Observe the LED (which will be simulated on the console) turn back off and the corresponding message in the RPI console

We used cloud to device messages (C2D) in steps 7 & 8. C2D are great for one way notifications to the device. 
With C2D, messages will stay in a queue until proccessesed by the device. The time to live of the message is configurable from 1-7 days.

9. Stop lab2c.py (Ctrl + X).  Choose “ON” from the drop down and choose “Send Command”.  Notice that the LED (which will be simulated on the console) on the device does not turn on like it did step 7. This is expected.
10. Execute the script   (‘python lab2c.py’ from the command prompt). The LED (which will be simulated on the console) on the device should light up without having to resend the command. 
       
Congratulations!  You now have a physical IoT device talking to the RM-PCS.  In the next couple of labs, we’ll do some processing of the telemetry data looking for high temperature “alarms” and responding to them.

#### Appendix A – Configuring your Raspberry PI 

1.	Setup Wireless (don’t need to do this if your PI is already connected to the internet)
 
    * Open the wpa-supplicant configuration file in nanob     
            sudo nano /etc/wpa_supplicant/wpa_supplicant.conf 
     
    * Go to the bottom of the file and add the following
    
            Network={
            	 ssid="The_ESSID_from_earlier"
            	 psk="Your_wifi_password"
              }
        
    * You might need to reboot to have the changes take effect. To reboot:

          sudo reboot
  
2.	Install Python
    
        sudo apt-get update
        
        sudo apt-get install build-essential python-dev
    
 
3.	Install drivers for the temperature sensor (DHT)
 
        cd ~
         
        git clone –recursive https://github.com/adafruit/Adafruit_Python_DHT.git
         
        cd Adafruit_Python_DHT 
         
        sudo python setup.py install
 
4.	Install Azure IoT Hub device SDK for Python

        from the command line make sure you CD to module2c's directory and then run:
         
        pip install azure-iothub-device-client 
