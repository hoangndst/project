var server = "http://192.168.43.101:3000";
function httpPUT(url, data, callback) {
    var req = new XMLHttpRequest();
    req.open("PUT", url, true);
    req.setRequestHeader("Content-type", "application/json");
    req.onreadystatechange = function () {
        if (req.readyState == 4 && req.status == 200) {
            callback(req.responseText);
        }
    }
    req.send(data);
}

function httpGET(url, callback) {
    var req = new XMLHttpRequest();
    req.open("GET", url, true);
    req.onreadystatechange = function () {
        if (req.readyState == 4 && req.status == 200) {
            callback(req.responseText);
        }
    }
    req.send();
}


function led26() {

    httpGET(server + "/led/26", function (data) {
        var led26 = JSON.parse(data);
        console.log(led26);
        var led26Status = led26[0].status;
        if (led26Status == 0) {
            httpPUT(server + "/led/26", JSON.stringify({ "status": true }), function (data) {
                console.log(data);
            });
        } else {
            httpPUT(server + "/led/26", JSON.stringify({ "status": false }), function (data) {
                console.log(data);
            });
        }
    });

}

function led27() {

    httpGET(server + "/led/27", function (data) {
        var led27 = JSON.parse(data);
        console.log(led27);
        var led27Status = led27[0].status;
        if (led27Status == 0) {
            httpPUT(server + "/led/27", JSON.stringify({ "status": true }), function (data) {
                console.log(data);
            });
        } else {
            httpPUT(server + "/led/27", JSON.stringify({ "status": false }), function (data) {
                console.log(data);
            });
        }
    });
    
}