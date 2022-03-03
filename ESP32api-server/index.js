const app = require('express')();
const bodyParser = require('body-parser');
require('dotenv').config();
const PORT = 3000;

app.use(bodyParser.urlencoded({ extended: true }));
app.use(bodyParser.json());


let routes = require('./api/routes');
routes(app);

app.use(function(req, res) {
    res.status(404).send({url: req.originalUrl + ' not found'})
});

app.listen(PORT, () => {
    console.log(`Server listening on port ${PORT}`);
});
