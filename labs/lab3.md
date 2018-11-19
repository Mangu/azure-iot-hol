## Module 2 - Create a real time dashboard

A typical scenario in IoT solutions is to deliver real-time notifications to subscribing parties. In Azure, there are various ways to achieve real-time delivery of notifications. The following is a walkthrough of using Azure Functions to process messages from IoT device and Azure SignalR Service to deliver the notifications via Websockets. Lastly, we will use simple HTML client to display the notifications

>Since SignalR supports Websockets, any client that supports Websockets could be used.

## 1. Creating the service

1. Create an instance of SignalR Service, follow [these steps](  https://docs.microsoft.com/en-us/azure/azure-signalr/scripts/signalr-cli-create-service).

2. Copy the connection string that is outputted by the script. You will need it the later.

## 2. Creating the function app

Our function is triggered by messages sent to IoT Hub. Since IoT Hub exposes an EventHub compatible endpoint, we need to install the EventHub function bindings. We will also use the SignalR Service bindings to send the messages to SignalR. 

### 2.1 Setup

1. To develop Azure Functions locally, you need to install the  [Azure Functions Core Tools](https://github.com/Azure/azure-functions-core-tools) (V2)
2. From a command line, navigate to the functions forder and run `func init`
3. We need to install the EventHub and SignalR bindings, to do so run `func extensions install --force`. This will look at the functions.json files and install the needed bindings.
4. Install the Azure Storage emulator available [here](https://docs.microsoft.com/en-us/azure/storage/common/storage-use-emulator. Make sure to start it once it is install. The EventHub trigger will not work without it.
5. Open local.settings.json and replace the content with the content from settings.json. Make sure you change the settings to your own.

### 2.2 Negotiator

We need to provide a mechanism for the client to obtain the proper credentials to connect to SignalR Service. For this walkthrough, I am leaving the function with anonymous access. In a production scenario, we can secure it  OAuth or something else. The code here is very simple. function.json has the configurations for the function and index.js has the actual code.

### 2.3 Dispacher - Notify

Next, we need to create the function that will dispatch notifications to SignalR Service. One of the many advantages of using SignalR Service in a serverless faction is that we don't need to create a Hub. Instead, the Azure Function will use the SignalR Service output binding to push new messages. 

Open the function.json and index.js in the notify folder. Again, nothing fancy here

To run the app type ``` func host start ```

## 3. Creating the client
To test our function, use the client provided in the "client" folder of this repo. We will walkthrough the client code in the module wrap up.