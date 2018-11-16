## Module 2 - Create a real time dashboard

A typical scenario in IoT solutions is to deliver real-time notifications to subscribing parties. In Azure, there are various ways to achieve real-time delivery of notifications. The following is a walkthrough of using Azure Functions to process messages from IoT device and Azure SignalR Service to deliver the notifications via Websockets. Lastly, we will use simple HTML client to display the notifications

>Since SignalR supports Websockets, any client that supports Websockets could be used.

## 1. Creating the service

1. Create an instance of SignalR Service, follow [these steps](  https://docs.microsoft.com/en-us/azure/azure-signalr/scripts/signalr-cli-create-service).

2. Copy the connection string that is outputted by the script. You will need it the later.

## 2. Creating the function app

Our function is triggered by messages sent to IoT Hub. Since IoT Hub exposes an EventHub compatible endpoint, we need to install the EventHub function bindings. We will also use the SignalR Service bindings to send the messages to SignalR. 

To develop Azure Functions locally, you need to install the  [Azure Functions Core Tools](https://github.com/Azure/azure-functions-core-tools) (V2)

### 2.1 Setup

1. Create a new folder to hold your Azure Function app. Then from a command line run `func init`
2. Install the SignalR Service bindings `func extensions install -p Microsoft.Azure.WebJobs.Extensions.SignalRService -v 1.0.0-preview1-10002`
3. Install the EventHub bindings `func extensions install --package Microsoft.Azure.WebJobs.Extensions.EventHubs --version 3.0.0-beta5`
   >Install the Azure Storage emulator available [here](https://docs.microsoft.com/en-us/azure/storage/common/storage-use-emulator). Make sure to start it once it is install. The EventHub trigger will not work without it.

4. Open local.settings.json. Add a new setting and call it AzureSignalRConnectionString. Paste the connection string from step 1.2 for the setting value.


### 2.2 Negotiator

We need to provide a mechanism for the client to obtain the proper credentials to connect to SignalR Service. For this walkthrough, I am leaving the function with anonymous access. In a production scenario, we can secure it  OAuth or something else. 

1. Run `func new` to create a new function and name it "negotiate". When prompted for a language, select Node / JavaScript. When prompted for a template select HTTPTrigger
   
2. We will use the `SignalRConnectionInfo` input binding to obtain the connection. Open function.json and replace the content with:

```javascript
{
  "disabled": false,
  "bindings": [
    {
      "authLevel": "anonymous",
      "type": "httpTrigger",
      "direction": "in",
      "name": "req"
    },
    {
      "type": "http",
      "direction": "out",
      "name": "res"
    },
    {
      "type": "signalRConnectionInfo",
      "name": "connectionInfo",
      "hubName": "notify",
      "direction": "in"
    }
  ]
}
```  

> The client needs to call this function to obtain the endpoint URL and access token before it can access SignalR Service. 

3. Open index.js and replace the content with:

```javascript
module.exports = function (context, req, connectionInfo) {
    //Return the connection credentials
    context.res = { body: connectionInfo };

    //We need this for CORS
    context.res.headers = { 'Access-Control-Allow-Credentials' : 'true', 
                        'Access-Control-Allow-Origin' : '*', 
                        'Access-Control-Allow-Headers' : 'Origin',
                        'Content-Type': 'application/json' };
                        
    context.done();
  };````

### 2.3 Dispacher

Next, we need to create the function that will dispatch notifications to SignalR Service. One of the many advantages of using SignalR Service in a serverless faction is that we don't need to create a Hub. Instead, the Azure Function will use the SignalR Service output binding to push new messages.

1. Run `func new` to create a new function and name it "notify". When prompted for a language, select JavaScript.

2. Open function.json and replace the content with(replace <EVENTHUBNAME> with your own value):

```javascript
{
  "disabled": false,
  "bindings": [
    {
      "type": "eventHubTrigger",
      "name": "eventHubMessage",
      "direction": "in",
      "eventHubName": "<EVENTHUBNAME>",
      "connection": "myEventHubReadConnectionAppSetting"
    },
    {
      "type": "signalR",
      "name": "signalRMessages",
      "hubName": "notify",
      "direction": "out"
    }
  ]
}
```

3. Open index.js and replace the content with: 

```javascript
module.exports = function (context, eventHubMessage) {
    var msg = eventHubMessage;
    context.bindings.signalRMessages = [{
      "target": "newMessage",
      "arguments": [ msg ]
    }];
    context.done();
};
```

4. To run the app type ``` func host start ```


## 3. Creating the client
To test our function, use the client provided in the "client" folder of this repo. We will walkthrough the client code in the module wrap up.
```