const readline = require('readline');
const { exit } = require('node:process');
let net = require('node:net');
require('dotenv').config()

let HOST = '127.0.0.1';
let PORT = process.env.PORT || 3000;


// Create a server instance, and chain the listen function to it
// The function passed to net.createServer() becomes the event handler for the 'connection' event
// The sock object the callback function receives UNIQUE for each connection
let clients = []

net.createServer(function (sock) {
  clients.push(sock)
  // We have a connection - a socket object is assigned to the connection automatically
  console.log('CONNECTED: ' + sock.remoteAddress + ':' + sock.remotePort);
  // Add a 'data' event handler to this instance of socket
  sock.on('data', function (data) {
    try {
      let clientData = JSON.parse(data)

      sock.name = clientData?.name
      console.log(`${sock.remoteAddress} - ${clientData?.name}  :  ${clientData?.message}`);

      // Write the data back to the socket, the client will receive it as data from the server
      // sock.write('You said "' + data + '"');
      for (let i = 0, len = clients.length; i < len; i++) {
        let item = clients[i]
        if (sock != item) {
          if (clientData?.firstTimeConnect === true)
            item.write(JSON.stringify({
              name: `${clientData?.name}`,
              message: `${clientData?.name} connected.`,
              isServer: true
            }))
          else
            item.write(data)

        }
      }
    } catch (error) {
      console.log(error)
    }
  });
  // Add a 'close' event handler to this instance of socket
  sock.on('close', function (data) {
    let index
    for (let i = 0, len = clients.length; i < len; i++) {
      let item = clients[i]
      if (sock != item)
        item.write(JSON.stringify({
          name: `${sock.name}`,
          message: `${sock.name} disconnected.`,
          isServer: true
        }))
      else {
        index = i
        console.log(`${item.name} disconnected.`);
      }
    }
    console.log('CLOSED:  ' + sock.remotePort);
    clients.splice(index, 1);
  });
  sock.on('error', function (err) {
    console.log('Error')
  })

}).listen(PORT, HOST);

console.log(`Server listening on http://${HOST}:${PORT}`);


function askQuestion(query) {
  const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout,
  });

  return new Promise(resolve => rl.question(query, ans => {
    rl.close();
    resolve(ans);
  }))
}

async function start() {
  let message
  while (true) {
    message = await askQuestion('')

    if (message === '!len') {
      console.log(`Client array length : ${clients.length}`)
      continue
    }
    if (message === '!exit') {
      exit(1)
      continue
    }

    if (!message)
      continue
    for (let i = 0, len = clients.length; i < len; i++) {
      let item = clients[i]
      item.write(JSON.stringify({
        name: `SERVER`,
        message
      }))
    }
  }
}

start()