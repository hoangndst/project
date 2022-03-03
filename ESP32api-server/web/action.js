var led26Status = 0;
var led27Status = 0;
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


function led26() {
    if (led26Status == 0) {
        led26Status = 1;
        httpPUT(server + "/led/26", JSON.stringify({ "status": led26Status }), function (data) {
            console.log(data);
        });
    } else {
        led26Status = 0;
        httpPUT(server + "/led/26", JSON.stringify({ "status": led26Status }), function (data) {
            console.log(data);
        });
    }
}