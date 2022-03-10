'use strict';
const mysql = require('mysql');
const db = require('../db');

module.exports = {
    get: (req, res) => {
        let sql = 'SELECT * FROM `dht11`';
        db.query(sql, (err, result) => {
            if (err) throw err;
            res.json(result);
        });
    },
    
    detail: (req, res) => {
        let sql = 'SELECT * FROM `dht11`';
        db.query(sql, [req.params.id], (err, result) => {
            if (err) throw err;
            res.json(result);
        });
    },
    
    store: (req, res) => {
        let data = req.body;
        let sql = 'INSERT INTO dht11 SET ?';
        db.query(sql, data, (err, result) => {
            if (err) throw err;
            res.json({message: 'Insert success!'});
        });
    }
}