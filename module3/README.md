## Module 3 - Gain real time insights


### Introduction
This lab is focused on configuring an Azure Stream Analytics to aggregate realtime data coming from IoT Hub.  We will calculate the number of votes received, number of unique devices, vote score, average temperature & humidity. 

#### Step 1 - Create a Stream Analytics Job

In this section, you will create a new Stream Analytics Job and validate events are flowing properly.

1. Using a web browser navigate to portal.azure.com   
2. Create a new Stream Analytics Job from the portal navigation using + New -> Internet of Things -> Stream Analytics Job
![Add Stream Analytics](/images/m3AddASA.png) 

3. You’ll be presented with the create pane for Azure Stream Analytics.  For the Job Name field, enter a name for your job that you can remember.  For “Resource Group”, choose “use existing”.  In the drop down list box, you should see a resource group named the same thing as your chosen solution name from lab 1.  Choose that.  Make sure that the “location” is the same as chosen in Lab 1 (e.g. “East US”, most likely).  Click on the “Create” button
![Job Name](/images/m3JobName.png)

4. You will be presented with a progress indicator while the job is creating 
5. Upon completion you’ll be presented the main blade for your stream analytics job
![Completion](/images/m3Completion.png)
 
#### Step 2 - Defining the Input

In this section we’ll define the input to the Azure Stream Analytics job.  This configuration binds to the IoT Hub that you created in module 1
1.	Under “Job Topology” click on “Inputs”

![Define Inputs](/images/m3Input.png) 

2. You’ll be presented a blank list of inputs.  Click the Add button
3.	On the “New input” screen complete the details based on your specific solution names.  A few notes:
    -	For input alias, enter 'devices' (we will use this later in the query, so if you name it something different, you’ll need to change the query later)
    -	For Source Type, choose Data stream
    -	For Source, choose IoT Hub
    -	Since we have only one IoTHub in our subscription at this point, it should auto-fill the rest of the fields.    
    ![Configuration](/images/m3Config.png) 

4.	Click the  button.

#### Step 3 - Creating Azure Funtion to proccess the output



#### Step 4 - Defining the Stream Analytics Output
In this section, we will go back to our Azure Stream Analytics (ASA) job and ‘wire up’ the Function created in Step 3 as the output of our job

1.	In the Azure Portal, on the left hand nav, click on “Stream Analytics Jobs” and then open the job you created above
2.	On the blade for your ASA job, click “Outputs” and then click “+ Add” to add an output
3.	On the “New Output” blade, name it **azfunction**. NEED TO ADD FUNCTION DETAILS


4.	Accept the rest of the defaults and hit ‘Create’.  Wait until the output is created to move to the next step.
5.	Now that we have wired up an IotHub as an input, and an Azure Function as an Output, we are now ready to specify our query. 

#### Step 5 - Writing the Streaming Query
Stream Analytics will read the events as they stream in from the device and execute this query.  Any time an event enters or leaves the windows, a message will be sent to the Azure Function

1. Click on the “Query” button from the “Job Topology” screen.
![Stream Analytics Output](/images/m3ASAOut.png) 

2. You’ll now be presented a basic starting point for a query.
![Stream Analytics Query](/images/m3ASAQuery.png)

3. For our query, we will calculate the number of votes received, number of unique devices, vote score, average temperature & humidity
    
    `
    SELECT Avg(temperature) as temperature, Avg(humidity) as humidity, Sum(vote),  Count(*) as [count], COUNT(DISTINCT device) as Devices
    INTO azfunction
    FROM devices TIMESTAMP BY EventEnqueuedUtcTime
    GROUP BY SlidingWindow(minute,1)

    `
                        
4. Click on the button to store the query.
5. We are done with the Stream Analytics job, but we will not start it running until we have our Azure Function in place to process the events.
