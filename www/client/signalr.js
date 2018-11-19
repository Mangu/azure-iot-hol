      const apiBaseUrl = 'http://localhost:7071';
      const hubName = 'notify';
  
      getConnectionInfo().then(info => {  
        let username="user";
        while (!username && username !== null) {
          username = prompt('Enter a username');
        }
        
        if (username === null) return;
        document.body.classList.add('ready');  
        
        const value1 = document.getElementById('value1');
        const value2 = document.getElementById('value2');
        const value3 = document.getElementById('value3');
        const value4 = document.getElementById('value4');
        const value5 = document.getElementById('value5');     

        const eventlog = document.getElementById('eventlog');
        const maxLogs = 20;

        const options = {
          accessTokenFactory: () => info.accessToken
        };
      
        const connection = new signalR.HubConnectionBuilder()
          .withUrl(info.url, options)
          .configureLogging(signalR.LogLevel.Information)
          .build();
  
        connection.on('newMessage', (message) => {
          
          console.log(JSON.stringify(message));
            let msg = message;                                   
            var row = eventlog.insertRow(1);
            var ts = new Date().toLocaleTimeString();
               
            row.insertCell(0).innerText =  ts;
            row.insertCell(1).innerText =  msg.location;
            row.insertCell(2).innerText =  msg.vote;
            row.insertCell(3).innerText =  Math.round(msg.humidity);
            row.insertCell(4).innerText =  Math.round(msg.temperature);
            
             if(eventlog.rows.length > maxLogs)
                eventlog.deleteRow(maxLogs)                
            
            data.labels.push(ts);
            data.datasets[0].data.push(Math.round(msg.temperature));
            data.datasets[1].data.push(Math.round(msg.humidity));
            data.datasets[2].data.push(Math.round(msg.vote*100));

            chart.update();
        });

        connection.on('newCalculation', (message) => {
            let msg = message;

            console.log(JSON.stringify(message));
            
            value1.innerText = msg[0].devices.toString();
            value2.innerText = Math.round(msg[0].count);
            value3.innerText = (Math.round(msg[0].sum) / Math.round(msg[0].count)).toFixed(2);
            value4.innerText = Math.round(msg[0].temperature);
            value5.innerText = Math.round(msg[0].humidity);             
        });        
       
        connection.onclose(() => console.log('disconnected'));
  
        console.log('connecting...');
        connection.start()
          .then(() => console.log('connected!'))
          .catch(console.error);
        
      }).catch(alert);
  
      function getConnectionInfo() {
        return axios.post(`${apiBaseUrl}/api/negotiate`)
          .then(resp => resp.data);
      }     
