const { exit } = require('node:process')
let net = require('node:net')
require('dotenv').config()

const { askQuestion, createUniqueId } = require('./utilties')

let HOST = '127.0.0.1'
let PORT = process.env.PORT || 3000

let clientMap = new Map()
let isServerBusy = false
let clientToIdWhenBusy = null
let clientFromIdWhenBusy = null

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
    if (message === '!busy') {
      console.log(`Server busy? : ${isServerBusy}`)
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
  console.log(`CONNECTED (${clientId}): ` + sock.remoteAddress + ':' + sock.remotePort)
  // clientMap.set(clientId, sock)

  // console.log(sock.clientId)
}

function onIncomingData({ data, sock }) {
  try {
    const clientData = JSON.parse(data)
    // console.log(clientData)
    if (clientData?.message == '!busy') {
      sendMessage(
        {
          isServer: true,
          clientFrom: sock,
          clientTo: sock,
          message: `Server busy ? : ${isServerBusy}`,
        },
        [{ isServerBusy }]
      )
      return
    }

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
    }
    if (clientData?.firstTimeConnect === true) {
      sendMessage({
        isServer: true,
        clientFrom: sock,
        clientTo: sock,
        message: sock.clientId,
        firstTimeConnect: true,
      })
      return
    }

    clientData.clientToId = Number(clientData?.clientToId)
    if (isServerBusy === true) {
      if (clientToIdWhenBusy == clientData?.clientToId && clientFromIdWhenBusy == sock.clientId) {
        sendMessage({
          isServer: false,
          clientFrom: sock,
          clientTo: clientMap.get(clientToIdWhenBusy),
          message: clientData.message,
        })
        isServerBusy = false
        clientToIdWhenBusy = null
        clientFromIdWhenBusy = null
      } else {
        sendMessage({
          isServer: true,
          clientFrom: sock,
          clientTo: sock,
          message: `Server is busy. Try again later`,
        })
      }
      return
    } else {
      if (clientMap.get(clientData?.clientToId) != undefined) {
        isServerBusy = true
        clientToIdWhenBusy = sock.clientId
        clientFromIdWhenBusy = clientData?.clientToId
        sendMessage({
          isServer: false,
          clientFrom: sock,
          clientTo: clientMap.get(clientFromIdWhenBusy),
          message: clientData.message,
        })
      } else {
        sendMessage({
          isServer: true,
          clientFrom: sock,
          clientTo: sock,
          message: `Client id does not exits`,
        })
      }
      return
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
  { isServer = false, message = '', firstTimeConnect = false, clientFrom = null, clientTo = null },
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
