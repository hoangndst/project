'use strict';
const mysql = require('mysql');
const db = require('../db');

module.exports = {
    get: (req, res) => {
        res.header("Access-Control-Allow-Origin", "http://127.0.0.1:5500");
        res.header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
        res.header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
        res.header("Access-Control-Allow-Credentials", "true");
        let sql = 'SELECT * FROM `led`';
        db.query(sql, (err, result) => {
            if (err) throw err;
            res.json(result);
        });
    },
    
    detail: (req, res) => {
        let sql = 'SELECT * FROM `led` WHERE `id` = ?';
        db.query(sql, [req.params.id], (err, result) => {
            if (err) throw err;
            res.json(result);
        });
    },

    update: (req, res) => {
        res.header("Access-Control-Allow-Origin", "http://127.0.0.1:5500");
        res.header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
        res.header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
        res.header("Access-Control-Allow-Credentials", "true");
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