const net = require('node:net');
const { exit } = require('node:process');
const readline = require('readline');
require('dotenv').config()



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



let HOST = '127.0.0.1';
let PORT = process.env.PORT || 3000;
let client = new net.Socket();


// Add a 'data' event handler for the client socket
// data is what the server sent to this socket
client.on('data', function (data) {
  let serverData = JSON.parse(data)
  if (serverData?.isServer === true)
    console.log(`SERVER : ${serverData?.message}`);
  else
    console.log(`${serverData?.name} : ${serverData?.message}`);
});

// Add a 'close' event handler for the client socket
client.on('close', function () {
  console.log('Connection closed');
});

client.on('error', function () {
  console.log('Connection closed unexpectedly');
  client.destroy();
  exit(1)
});


async function start() {
  let name = null

  while (!name) {
    name = await askQuestion('Enter your name : ');
  }

  await new Promise(resolve => {
    client.connect(PORT, HOST, function () {
      console.log(`CONNECTED TO: http://${HOST}:${PORT}`);
      // Write a message to the socket as soon as the client is connected, the server will receive it as message from the client
      client.write(JSON.stringify({
        name,
        message: `${name} connected.`,
        firstTimeConnect: true
      }));
      resolve()
    });
  })
  let message = 'Test'
  while (message != '!exit') {
    // message = await askQuestion("Enter messsage : ");
    message = await askQuestion('');
    if (message && message != '!exit')
      client.write(JSON.stringify({
        name,
        message
      }));
  }
  client.destroy();
}


start();