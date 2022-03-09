const findRemove = require('find-remove');

setInterval(() => {
    var res = findRemove('./video', { age: { seconds: 30 }, extensions: '.ts' });
    console.log(res);
}, 5000);