'use strict';
const mysql = require('mysql');

const db = mysql.createConnection({
  host: "localhost",
  port: 3307,
  user: "root",
  password: "password",
  database: process.env.DB_NAME || "esp32_api"
});

module.exports = db
