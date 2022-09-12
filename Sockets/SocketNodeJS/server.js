const { exit } = require('node:process')
let net = require('node:net')
require('dotenv').config()

const { askQuestion, createUniqueId } = require('./utilties')

let HOST = '127.0.0.1'
let PORT = process.env.PORT || 3000

let clientMap = new Map()

net.createServer(onConnect).listen(PORT, HOST)

console.log(`Server listening on http://${HOST}:${PORT}`)

async function start() {
  let message
  while (true) {
    message = await askQuestion('')

    if (message === '!len') {
      console.log(`Client array length : ${clientMap.size}`)
      continue
    }
    if (message === '!exit') exit(1)

    if (!message) continue

    let clientEntries = Array.from(clientMap.entries())
    for (let i = 0, len = clientMap.size; i < len; i++) {
      let [id, clientSock] = clientEntries[i]
      sendMessage({
        isServer: true,
        message,
        clientTo: clientSock,
      })
    }
  }
}

start()

async function onConnect(sock) {
  console.log('CONNECTED: ' + sock.remoteAddress + ':' + sock.remotePort)

  let clientId = await createUniqueId(Array.from(clientMap.keys()), {})
  clientMap.set(clientId, sock)
  sock.on('data', function (data) {
    onIncomingData({ data, sock })
  })
  sock.on('close', function (data) {
    onClose({ data, sock })
  })
  sock.on('error', function (err) {
    console.log(`Error occured for clientId ${sock?.clientId}`)
  })
  sock.clientId = clientId
  // clientMap.set(clientId, sock)

  // console.log(sock.clientId)
}

function onIncomingData({ data, sock }) {
  try {
    const clientData = JSON.parse(data)

    if (clientData?.getClientList === true) {
      sendMessage(
        {
          isServer: true,
          clientFrom: sock,
          clientTo: sock,
          message: Array.from(clientMap.keys()),
          firstTimeConnect: false,
        },
        [{ getClientList: true }]
      )
      return
    } else if (clientData?.firstTimeConnect === true) {
      sendMessage({
        isServer: true,
        clientFrom: sock,
        clientTo: sock,
        message: sock.clientId,
        firstTimeConnect: true,
      })
    }

    console.log(`${sock.remoteAddress} (${sock.clientId}):  ${clientData?.message}`)
    let clientEntries = Array.from(clientMap.entries())
    for (let i = 0, len = clientMap.size; i < len; i++) {
      let [id, clientSock] = clientEntries[i]
      if (sock.clientId != id) {
        if (clientData?.firstTimeConnect === true) {
          sendMessage({
            message: `${sock?.clientId} connected.`,
            isServer: true,
            clientTo: clientSock,
            clientFrom: sock,
          })
        } else {
          sendMessage({
            isServer: false,
            clientFrom: sock,
            clientTo: clientSock,
            message: clientData.message,
          })
        }
      }
    }
  } catch (error) {
    console.log(error)
  }
}

function onClose({ data, sock }) {
  console.log(data)
  let clientEntries = Array.from(clientMap.entries())
  for (let i = 0, len = clientMap.size; i < len; i++) {
    let [id, clientSock] = clientEntries[i]
    if (id != sock.clientId)
      sendMessage({
        message: `${sock.clientId} disconnected.`,
        isServer: true,
        clientTo: clientSock,
      })
  }
  console.log(`${sock.clientId} disconnected.`)
  console.log('CLOSED:  ' + sock.remotePort)
  clientMap.delete(sock.clientId)
}

function sendMessage(
  { isServer = false, message = '', firstTimeConnect = false, clientFrom, clientTo },
  extra = []
) {
  let extras = {}
  for (let index = 0; index < extra.length; index++) {
    const e = extra[index]
    extras = { ...extras, ...e }
  }

  clientTo.write(
    JSON.stringify({
      fromClientDetails: {
        clientId: clientFrom?.clientId,
        clientName: clientFrom?.name,
      },
      toClientDetails: {
        clientId: clientTo?.clientId,
        clientName: clientTo?.name,
      },
      message,
      isServer,
      firstTimeConnect,
      ...extras,
    })
  )
}
