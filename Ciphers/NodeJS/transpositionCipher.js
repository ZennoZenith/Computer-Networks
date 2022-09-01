const readline = require('readline')
const MATRIX_LEN = 100
const RAND_CHAR = 'M'

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
    this.encryptedText = 'HlodeorMlWlM'
    this.ignoreChar = ''
    this.key = 3
    this.plainTextlen = 10
    this.matrix = new Array(MATRIX_LEN)
    for (var i = 0; i < 8; i++) {
      this.matrix[i] = new Array(MATRIX_LEN)
    }
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
  setPlainTextLen(plainTextlen) {
    this.plainTextlen = Number(plainTextlen)
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
  showMatrix(m, n) {
    for (let i = 0; i < m; i++) {
      console.log(this.matrix[i]?.slice(0, n))
    }
  }
  encrypt() {
    let i,
      j,
      k = 0,
      len
    len = this.plainText.length
    this.plainTextlen = len
    this.encryptedText = ''
    let numberOfRows = Math.ceil(len / this.key)

    for (i = 0; i < numberOfRows; i++) {
      for (j = 0; j < this.key; j++) {
        if (k < len) this.matrix[i][j] = this.plainText[k]
        else this.matrix[i][j] = RAND_CHAR
        k++
      }
    }
    this.showMatrix(numberOfRows, this.key)

    k = 0
    for (j = 0; j < this.key; j++) {
      for (i = 0; i < numberOfRows; i++) {
        this.encryptedText += this.matrix[i][j]
        k++
      }
    }
    return this.encryptedText
  }
  decrypt() {
    let i,
      j,
      k = 0
    let len = this.encryptedText.length
    let numberOfRows = Math.ceil(len / this.key)

    for (j = 0; j < this.key; j++) {
      for (i = 0; i < numberOfRows; i++) {
        if (k < len) this.matrix[i][j] = this.encryptedText[k]
        else this.matrix[i][j] = RAND_CHAR
        k++
      }
    }
    this.showMatrix(numberOfRows, this.key)

    this.plainText = ''
    k = 0
    for (i = 0; i < numberOfRows; i++) {
      for (j = 0; j < this.key; j++) {
        this.plainText += this.matrix[i][j]
        k++
        if (k == this.plainTextlen) break
      }
    }

    return this.plainText
  }
}

async function main() {
  let m = new Message()

  let choice, key, flag, text, len
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
        len = await askQuestion('Enter string len : ')
        m.setKey(key)
        m.setPlainTextLen(len)
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
