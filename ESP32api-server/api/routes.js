'use strict';
module.exports = function(app) {
    let ledController = require('./controllers/ledController');
    let dht11Controller = require('./controllers/dht11Controller');
    app.route('/led')
        .get(ledController.get)
        .post(ledController.store);
    app.route('/led/:id')
        .get(ledController.detail)
        .put(ledController.update);
    app.route('/dht11')
        .get(dht11Controller.detail)
        .post(dht11Controller.store);
};