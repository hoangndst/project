const http = require('http');
const fs = require('fs');

const PORT = 4000;

http.createServer((req, res) => {

    const headers = {
        'Access-Control-Allow-Origin': '*',
        'Access-Control-Allow-Methods': 'OPTIONS, POST, GET',
        'Access-Control-Max-Age': 2592000, // 30 days
        /** add other headers as per requirement */
    };

    if (req.method === 'OPTIONS') {
        res.writeHead(204, headers);
        res.end();
        return;
    }

    var path = "video" + req.url;

    fs.readFile(path, (err, data) => {
        res.writeHead(200, { 'Access-Control-Allow-Origin': '*' });
        if (err) {
            if (err.code === 'ENOENT') {
                res.writeHead(404);
                res.end();
            } else {
                res.writeHead(500);
                res.end('Server Error ' + err.code);
                res.end();
            }
        } else {
            res.end(data, 'utf-8');
        }
    });
}).listen(PORT);

console.log('Server running at PORT: ' + PORT);