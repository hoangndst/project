'use strict';
module.exports = function(app) {
    let ledController = require('./controllers/ledController');
    // app.use((req, res, next) => {
    //     res.header("Access-Control-Allow-Origin", "*");
    //     res.header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
    //     res.header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
    //     res.header("Access-Control-Allow-Credentials", "true");
    //     next();
    // });
    app.route('/led')
        .get(ledController.get)
        .post(ledController.store);
    app.route('/led/:id')
        .get(ledController.detail)
        .put(ledController.update);
};