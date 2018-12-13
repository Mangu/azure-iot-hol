'use strict';

module.exports = {
    broker: null,
    configuration: null,

    create: function (broker, configuration) {
        this.broker = broker;
        this.configuration = configuration;

        return true;
    },

    receive: function (message) {
	    console.log('printer.receive.properties:', message.properties);
        console.log(`printer.receive - ${Buffer.from(message.content).toString()} \n`);
    },

    destroy: function () {
        console.log('printer.destroy');
    }
};
