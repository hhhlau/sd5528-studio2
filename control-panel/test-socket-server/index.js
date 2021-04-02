const WebSocket = require('ws');
const carSocket = new WebSocket.Server({ port: 81 });

const browserSocket = new WebSocket.Server({ port: 82 });

let connectedClients = {}

function delay(method, ms) {
    return new Promise(function (resolve, reject) {
        setTimeout(function () {
            method
            resolve();
        }, ms);
    });
}

carSocket.on('connection', function connection(ws, req) {
    // var userID = parseInt(ws.upgradeReq.url.substr(1), 10)
    // console.log(userID)
    // connectedClients[userID] = ws

    // console.log(`[${userID}] Car connected with IP: ${req.socket.remoteAddress} (${req.headers['user-agent']})`)
    ws.on('message', function incoming(message) {
        console.log('received: %s', message);
    });


    // setInterval(() => {
    //     console.log('H')
    //     ws.send('Hello');
    // }, 1000)
});

browserSocket.on('connection', function connection(ws, req) {
    console.log(req.headers['user-agent'])
    if (Object.keys(req.headers).includes('user-agent')) {
        if (req.headers['user-agent'].includes('arduino-WebSocket-Client')) {
            console.log("Found you! Car")
            connectedClients["car"] = ws
        } else {
            connectedClients[req.socket.remoteAddress] = ws
        }
    } else {
        connectedClients[req.socket.remoteAddress] = ws
    }

    console.log(`[] Broswer connected with IP: ${req.socket.remoteAddress} (${req.headers['user-agent']})`)


    // console.log(connectedClients)
    console.log(Object.keys(connectedClients))
    ws.on('message', async function incoming(message) {
        console.log('received: %s', message);
        if (['UP', 'BACK', 'LEFT', 'RIGHT', 'STOP', 'SLOW'].includes(message)) {
            switch (message) {
                case 'UP':
                    console.log("Switch: UP")
                    connectedClients['car'].send('1')
                    break
                case 'BACK':
                    console.log("Switch: BACK")
                    connectedClients['car'].send('2')
                    break
                case 'RIGHT':
                    console.log("Switch: RIGHT")
                    connectedClients['car'].send('3')
                    break
                case 'LEFT':
                    console.log("Switch: LEFT")
                    connectedClients['car'].send('4')
                    break
                case 'STOP':
                    console.log("Switch: STOP")
                    connectedClients['car'].send('0')
                    break
                case 'SLOW':
                    console.log("Go slow")
                    connectedClients['car'].send('0')
                    for (var i = 0; i < 4; i++) {
                        await delay(connectedClients['car'].send('0'), 150)
                        await delay(connectedClients['car'].send('1'), 250)
                    }
                    connectedClients['car'].send('0')
            }
        }
    });
});