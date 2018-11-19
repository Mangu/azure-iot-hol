module.exports = async function (context, req) {
    context.log('Calculate function processed a request:' + JSON.stringify(req));
    
    context.bindings.signalRMessages = [{
        "target": "newCalculation",
        "arguments": [ req.body ]
      }];
      context.done();    
};