'use strict';
module.exports = function(app) {
    let ledController = require('./controllers/ledController');
    app.route('/led')
        .get(ledController.get)
        .post(ledController.store);
    app.route('/led/:id')
        .get(ledController.detail)
        .put(ledController.update);
};