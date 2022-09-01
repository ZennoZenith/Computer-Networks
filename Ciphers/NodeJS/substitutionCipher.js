const readline = require('readline')
function askQuestion(query) {
  const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout,
  })

  return new Promise((resolve) =>
    rl.question(query, (ans) => {
      rl.close()
      resolve(ans)
    })
  )
}

class Message {
  static SMALL = 'abcdefghijklmnopqrstuvwxyz'
  static CAPITAL = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
  constructor() {
    this.plainText = 'HelloWorld'
    this.encryptedText = 'KhoorZruog'
    this.ignoreChar = ''
    this.key = 3
  }
  getPlainText() {
    return this.plainText
  }
  getEncryptedText() {
    return this.encryptedText
  }
  setPlainText(plainText) {
    this.plainText = plainText
    return this.sanitiseText(this.plainText, { plainText: true })
  }
  setEncryptedText(encryptedText) {
    this.encryptedText = encryptedText
    this.sanitiseText(this.encryptedText, { encryptedText: true })
  }
  setKey(key) {
    this.key = Number(key)
  }
  setIgnoreChar(text) {
    this.ignoreChar = text
  }
  sanitiseText(text, { plainText = true, encryptedText = false }) {
    let tempText = new String()
    let i = 0,
      flag = 0
    let textLen = text.length

    for (i = 0; i < textLen; i++) {
      const element = text[i]
      if (this.ignoreChar.includes(element)) {
        tempText += text[i]
        continue
      }
      if (Message.SMALL.includes(element)) {
        tempText += text[i]
        continue
      } else if (Message.CAPITAL.includes(element)) {
        tempText += text[i]
        continue
      }
      flag = 1
    }
    if (plainText) this.plainText = tempText
    else if (encryptedText) this.encryptedText = tempText
    return flag
  }
  encrypt() {
    let len = Message.SMALL.length
    let plainTextLen = this.plainText.length

    this.encryptedText = ''
    for (let i = 0; i < plainTextLen; i++) {
      if (this.ignoreChar.includes(this.plainText[i])) {
        this.encryptedText += this.plainText[i]
        continue
      }
      let index = Message.SMALL.indexOf(this.plainText[i])
      if (index !== -1) {
        index += this.key
        while (index >= len) index -= len
        while (index < 0) index += len
        this.encryptedText += Message.SMALL[index]
      } else {
        index = Message.CAPITAL.indexOf(this.plainText[i])
        index += this.key
        while (index >= len) index -= len
        while (index < 0) index += len
        this.encryptedText += Message.CAPITAL[index]
      }
    }

    return this.encryptedText
  }
  decrypt() {
    let len = Message.SMALL.length
    let encryptedTextLen = this.encryptedText.length

    this.plainText = ''
    for (let i = 0; i < encryptedTextLen; i++) {
      if (this.ignoreChar.includes(this.encryptedText[i])) {
        this.plainText += this.encryptedText[i]
        continue
      }
      let index = Message.SMALL.indexOf(this.encryptedText[i])
      if (index !== -1) {
        index -= this.key
        while (index >= len) index -= len
        while (index < 0) index += len
        this.plainText += Message.SMALL[index]
      } else {
        index = Message.CAPITAL.indexOf(this.encryptedText[i])
        index -= this.key
        while (index >= len) index -= len
        while (index < 0) index += len
        this.plainText += Message.CAPITAL[index]
      }
    }

    return this.plainText
  }
}

async function main() {
  let m = new Message()

  let choice, key, flag, text
  do {
    console.log('1. Encrypt.')
    console.log('2. Decrypt.')
    console.log('3. Set ignore character list.')
    console.log('4. Exit.')
    choice = await askQuestion('Enter your choice : ')
    switch (choice) {
      case '1':
        text = await askQuestion('Enter plain text : ')
        flag = m.setPlainText(text)
        if (flag == 1) console.log('String contains special character(s).')
        key = await askQuestion('Enter key : ')
        m.setKey(key)
        console.log('Encrypted text : ' + m.encrypt())
        flag = await askQuestion('Do you want to decrypt (y/n) : ')
        if (flag == 'y' || flag == 'Y') console.log('Plain text : ' + m.decrypt())
        break
      case '2':
        text = await askQuestion('Enter encrypted text : ')
        flag = m.setEncryptedText(text)
        if (flag == 1) console.log('String contains special character(s).')
        key = await askQuestion('Enter key : ')
        m.setKey(key)
        console.log('Plain text : ' + m.decrypt())
        break
      case '3':
        text = await askQuestion('Enter ignore character list : ')
        m.setIgnoreChar(text)
        break
      case '4':
        console.log('Exiting...')
        break
      default:
        console.log('Wrong choice try again..')
        break
    }
  } while (choice != '4')
}

main()
