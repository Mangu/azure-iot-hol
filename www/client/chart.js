var ctx = document.getElementById("chart").getContext("2d");

var data = {
    labels: [],
    datasets: [
        {
          label: 'Temperature (F)',
          borderColor: "rgba(255, 0, 0, 1)",
          backgroundColor: "rgba(255, 0, 0, 1)",
          fill: false,
          data: []
        },
        {
            label: "Humidity (%)",
            borderColor: "rgba(0, 255, 0, 1)",
            backgroundColor: "rgba(0, 255, 0, 1)",
            fill: false,
            data: []      
        },
        {
            label: "Vote",
            borderColor: "rgba(0, 0, 255, 1)",
            backgroundColor: "rgba(0, 0, 255, 1)",
            fill: false,
            data: []
        }
    ]
};

// TODO suggested min and max
let options = {
    responsive: true,
    hoverMode: 'index',
    stacked: false,
    title: {
        display: false,
        text: ''
    },

    scales: {
      xAxes: [{
        display: true,
        scaleLabel: {
          display: true,
          labelString: 'Time'
        }
      }],
      yAxes: [{
        display: true,
        scaleLabel: {
          display: true,
          labelString: 'Value'
        }
      }]
    },

};

var chart = new Chart.Line(ctx, { data: data, options: options });