const path = require('path')
const express = require('express')
const http = require('http')
const socketio = require('socket.io')
const formatMessage = require('./utils/messages')
const { userJoin, getCurrentUser, userLeave, getRoomUsers } = require('./utils/users')

const app = express()
const server = http.createServer(app)
const io = socketio(server)

require('dotenv').config()

// Set static folder
app.use(express.static(path.join(__dirname, 'public')))


const botName = 'Chat bot'

// Run when client connects
io.on('connection', socket => {
    // 
    socket.on('joinRoom', ({ username, room }) => {
        console.log('New WS Connection')
        const user = userJoin(socket.id, username, room)

        socket.join(user.room)
        socket.emit('message', formatMessage(botName, 'Welcome to Chat room'))

        // Broadcast when user connects
        socket.broadcast.to(user.room).emit('message', formatMessage(botName, `${user.username} has joined the chat`))

        // Send user and room info
        io.to(user.room).emit('roomUsers', {
            room: user.room,
            users: getRoomUsers(user.room)
        })
    })

    // Listen for chat message
    socket.on('chatMessage', (msg) => {
        const user = getCurrentUser(socket.id)
        io.to(user.room).emit('message', formatMessage(user.username, msg))
    })

    // Runs when user disconnects
    socket.on('disconnect', () => {
        const user = userLeave(socket.id)
        // console.log(user)
        if (user) {
            io.to(user.room).emit('message', formatMessage(botName, `${user.username} has left the chat`))

            // Send user and room info
            io.to(user.room).emit('roomUsers', {
                room: user.room,
                users: getRoomUsers(user.room)
            })
        }
        // io.emit('message', formatMessage(botName, 'A user has left the chat'))
    })
})


const PORT = process.env.PORT || 3000
const start = () => {
    server.listen(PORT, () => console.log(`Server running on http://localhost:${PORT}`))
}

start()