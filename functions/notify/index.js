module.exports = function (context, eventHubMessage) {
   
    context.bindings.signalRMessages = [{
      "target": "newMessage", 
      "arguments": [ eventHubMessage ]
    }];

    context.done();
};