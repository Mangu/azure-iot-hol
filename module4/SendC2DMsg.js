var Client = require('azure-iothub').Client;
var Message = require('azure-iot-common').Message;

var connectionString = '{iot hub connection string}';
var targetDevice = '{device id}';

var serviceClient = Client.fromConnectionString(connectionString);

serviceClient.open(function (err) {
  if (err) {
    context.log('Could not connect: ' + err.message);
  } else {
    context.log('Service client connected');      
    var message = new Message(c2d_message);     
    message.messageId = "onmsg";
    context.log('Sending message: ' + message.getData());
    serviceClient.send(targetDevice, message, context.log('Message Sent' ));
  }
});
