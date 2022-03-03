'use strict';
const mysql = require('mysql');

const db = mysql.createConnection({
  host: process.env.DB_HOST || "localhost",
  port: 3306,
  user: process.env.DB_USER || "hoangndst",
  password: "Hoang2002*",
  database: process.env.DB_NAME || "esp32_api"
});

module.exports = db
