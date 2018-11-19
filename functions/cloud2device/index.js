module.exports = async function (context, req) {
    context.log('Cloud2Device function processed a request:' + JSON.stringify(req));

    var Client = require('azure-iothub').Client;
    var Message = require('azure-iot-common').Message;    
    var connectionString = process.env['iotHubConnectionString'];   
    var c2d_message = "ON"
    var targetDevice;        
    var serviceClient = Client.fromConnectionString(connectionString);
    
    serviceClient.open(function (err) {
      if (err) {
        context.log('Could not connect: ' + err.message);
      } else {
            context.log('Service client connected');      
            var message = new Message(c2d_message);     
            context.log('Sending message: ' + message.getData());
            
            for (var i = 0; i < req.body.length; i++) { 
                targetDevice = req.body[i].device;   
                serviceClient.send(targetDevice, message, context.log('Message Sent' ));     
            }          
      }
    });
};