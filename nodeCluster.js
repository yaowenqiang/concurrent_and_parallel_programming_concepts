var cluster = require("cluster");
var http = require("http");
var processors =  require('os').cpus().length;
var port = 8888;
if (cluster.isMaster) {
    console.log("Listening on port %d", port);
    console.log("processor count %d", processors);
    for (var i = 0; i < processors; i++) {
        cluster.fork();
    }

    cluster.on("exit", function(worker, node, signal) {
         cluster.fork();
    });
} else {
    http.createServer(function(req, res) {
        res.writeHead(200);
        res.end("Echoing request URI: " + req.url + "\n");
    }).listen(port);
}
