module.exports = function (context, req, connectionInfo) {
  context.log('Negotiate function processed a request:' + JSON.stringify(req));

  context.res = {
    body: connectionInfo,
    headers: {
      'Access-Control-Allow-Credentials': 'true',
      'Access-Control-Allow-Origin': req.headers.origin,
      'Access-Control-Allow-Headers': req.headers['access-control-request-headers']
    }
  };  
  context.done();
}