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
        let sql = 'SELECT * FROM `dht11` WHERE ORDER BY `id` DESC LIMIT 1';
        db.query(sql, [req.params.id], (err, result) => {
            if (err) throw err;
            res.json(result);
        });
    },

    update: (req, res) => {
        let data = req.body;
        let ledId = req.params.id;
        let sql = 'UPDATE led SET ? WHERE id = ?';
        db.query(sql, [data, ledId], (err, result) => {
            if (err) throw err;
            res.json({message: 'Update success!'});
        });
    },
    
    store: (req, res) => {
        let data = req.body;
        let sql = 'INSERT INTO led SET ?';
        db.query(sql, data, (err, result) => {
            if (err) throw err;
            res.json({message: 'Insert success!'});
        }
        );
    }
}