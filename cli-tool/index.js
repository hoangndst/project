#!/usr/bin/env node

import chalk from "chalk";
import chalkTable from "chalk-table";
import gradient from "gradient-string";
import chalkAnimation from "chalk-animation";
import { createSpinner } from "nanospinner";
import figlet from "figlet";
import { getData } from './ApiServer.js'

let playerName = "Hoang";

const options = {
  leftPad: 2,
  columns: [
    { field: "id",     name: chalk.bold("ID") },
    { field: "col1",  name: chalk.bold("Name") },
    { field: "col2", name: chalk.green("Account Balance") }
  ]
};

const sleep = (ms = 2000) => new Promise((r) => setTimeout(r, ms));

async function welcome() {
  getData('option=toPay').then(res => {
    let rows = res.rows;
    for (let i = 0; i < rows.length; i++) {
      if (rows[i].col2[0] === '-') {
        rows[i].col2 = chalk.bgRed(rows[i].col2) + '\n';
      } else {
        rows[i].col2 = chalk.bgGreen(rows[i].col2) + '\n';
      }
    }
    let table = chalkTable(options, rows);
    console.log(`
      ${chalk.bgCyan('510Pay - Account Balance')}
    `);
    console.log(`${table}`);
  });
}



welcome();