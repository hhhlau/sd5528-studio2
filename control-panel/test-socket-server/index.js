const WebSocket = require('ws');
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

browserSocket.on('connection', function connection(ws, req) {
    console.log(req.headers['user-agent'])
    if (Object.keys(req.headers).includes('user-agent')) {
        if (req.headers['user-agent'].includes('arduino-WebSocket-Client')) {
            console.log("Found you! Car")
            connectedClients["car"] = ws
        } else if (req.headers['user-agent'].includes('AppleWebKit')) {
            console.log("Got you browser!")
            connectedClients["browser"] = ws
        } else {
            connectedClients[req.socket.remoteAddress] = ws
        }
    } else {
        connectedClients[req.socket.remoteAddress] = ws
    }



    // console.log(connectedClients)
    console.log(Object.keys(connectedClients))
    ws.on('message', async function incoming(message) {
        // console.log(Object.keys(this))
        // console.log(JSON.parse(message))
        let data = JSON.parse(message)
        // console.table(data)
        // if (['UP', 'BACK', 'LEFT', 'RIGHT', 'STOP', 'SLOW'].includes(message)) 
        if (Object.keys(data).includes("direction")) {
            console.log('from browser')
            switch (data.direction) {
                case 'UP':
                    console.log("Switch: UP")
                    connectedClients['car'].send('1')
                    break
                case 'BACK':
                    console.log("Switch: BACK")
                    connectedClients['car'].send('2')
                    break
                // case 'RIGHT':
                //     console.log("Switch: RIGHT")
                //     connectedClients['car'].send('3')
                //     break
                // case 'LEFT':
                //     console.log("Switch: LEFT")
                //     connectedClients['car'].send('4')
                //     break
                case 'STOP':
                    console.log("Switch: STOP")
                    connectedClients['car'].send('0')
                    break
                case 'SLOW':
                    console.log("Go slow")
                    connectedClients['car'].send('3')
                // for (var i = 0; i < 4; i++) {
                //     await delay(connectedClients['car'].send('0'), 150)
                //     await delay(connectedClients['car'].send('1'), 250)
                // }
                // connectedClients['car'].send('0')
            }
        } else if (Object.keys(data).includes("detections")) {
            console.log("is data")
            if (Object.keys(connectedClients).includes("browser")) {
                connectedClients['browser'].send(JSON.stringify(data))
            }
            // let _detectionData = data["detections"]
            // _detectionData.forEach(function (detection) {
            //     // console.log(detection)
            //     if (Object.keys(connectedClients).includes("browser")) {
            //         connectedClients['browser'].send(JSON.stringify(detection))
            //     }

            // })

        }
    });
});