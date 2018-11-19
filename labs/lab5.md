## Module 4 - Communicating with the device

Another common pattern in IoT is to execute commands remotely on a device. Since our devices are connected via IoT Hub, we will let IoT Hub handle the communication to the device.

In the overview session, we talked about the three different ways to communicate with a device; desired properties, direct methods and C2D messages. In this module, we are going to use a direct method to send a command to the device. 

For this lab, we are going to send an alert to the device if the satisfaction score fall bellow 70%. The device will react by turning on the LED.

The code to handle the command on the device is already there. Look at the sketch and see if you can find it. We will discuss it in the lab wrap up.

## Add a query to Azure Stream Analytics 

We are going to add and additional query to the ASA job we created in the last lab. Here, we are basically looking for scores that fall bellow 70% for a given device.

1. Go a modify the job query by adding the following code.

    `
    SELECT Avg(temperature) as temperature, Avg(humidity) as humidity, (Sum(vote) /  Count(*)) as score, COUNT(DISTINCT device) as Devices, device
    INTO azfunctionc2d
    FROM devices TIMESTAMP BY EventEnqueuedUtcTime
    GROUP BY SlidingWindow(minute,60), device
    HAVING score < .7

2. Create another Azure Function output. Name it **azfunctionc2d** and point it to the **cloud2device** function.
3. Start the job and test the feature by pressing the "bad" button several times. The LED should turn on
    `