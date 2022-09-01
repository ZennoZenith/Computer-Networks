const readline = require('readline')
const ZERO_CHAR = 'a'
const ONE_CHAR = 'b'

String.prototype.isUpperCase = function () {
  return this.toString() === this.toUpperCase()
}

String.prototype.isUpperCase = function () {
  for (let ch of this) {
    if (!/[A-Z\W]/.test(ch)) {
      return false
    } 
  }
  return true
}

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

function ConvertNumberToCharacterList(number) {
  let i
  let tempCh = new Array(5)
  number = Number(number)
  for (i = 4; i > -1; i--) {
    if (number % 2 == 0) tempCh[i] = ZERO_CHAR
    else tempCh[i] = ONE_CHAR
    number = Math.floor(number / 2)
  }
  return tempCh
}
function ConvertCharacterListToNumber(tempCh) {
  let i
  let number = 0
  let temp = 1
  for (i = 4; i > -1; i--) {
    if (tempCh[i] == ONE_CHAR) {
      number += temp
    }
    temp *= 2
  }
  return number
}

class Message {
  static SMALL = 'abcdefghijklmnopqrstuvwxyz'
  static CAPITAL = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
  constructor() {
    this.plainText = 'HelloWorld'
    this.encryptedText = 'grEETinGs frOm THe ReAL uNIVeRsE TodAY Is The dAy I wILl fiNA'
    this.ignoreChar = ' '
    this.key = 3
    this.carrierText =
      'Greetings from the real universe Today is the day I will finally know what brick tastes like'
    this.sanitiseText(this.plainText, { plainText: true })
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
  setCarrierText(carrierText) {
    this.carrierText = carrierText
    this.sanitiseText(this.carrierText, { carrierText: true })
  }
  setKey(key) {
    this.key = Number(key)
  }
  setIgnoreChar(text) {
    this.ignoreChar = text
  }
  sanitiseText(text, { plainText = true, encryptedText = false, carrierText = false }) {
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
    else if (carrierText) this.carrierText = tempText
    return flag
  }
  encrypt() {
    let plainTextLen = this.plainText.length
    let i, j
    let tempCh = new Array(5)
    let intermediateText = ''

    for (i = 0; i < plainTextLen; i++) {
      if (this.ignoreChar.includes(this.plainText[i])) continue
      let index = Message.SMALL.indexOf(this.plainText[i])
      if (index == -1) {
        index = Message.CAPITAL.indexOf(this.plainText[i])
      }
      tempCh = ConvertNumberToCharacterList(index)
      intermediateText += tempCh.join('')
    }
    let intermediateTextLength = intermediateText.length

    /*For debugging

    //* Print intermediate text for debuging
    console.log(intermediateText)
    let tempText = [...intermediateText]
    let temp = ''
    for (let index = 0; index < tempText.length; index++) {
      const element = tempText[index]
      if (index % 5 == 0) temp += ' '
      temp += element
    }
    console.log('Intermediate text  : ' + temp)
    */

    j = 0
    this.encryptedText = ''
    for (i = 0; i < intermediateTextLength; i++) {
      while (this.carrierText[j] == ' ') {
        this.encryptedText += this.carrierText[j]
        j++
      }

      if (intermediateText[i] == ZERO_CHAR) this.encryptedText += this.carrierText[j]?.toLowerCase()
      else this.encryptedText += this.carrierText[j]?.toUpperCase()
      j++
    }
    return this.encryptedText
  }
  decrypt() {
    let encryptedTextLen = this.encryptedText.length
    let i, j

    let tempCh = new Array(5)
    let intermediateText = ''

    for (i = 0, j = 0; i < encryptedTextLen; i++) {
      while (this.encryptedText[i] == ' ') i++
      if (this.encryptedText[i]?.isUpperCase()) intermediateText += ONE_CHAR
      else intermediateText += ZERO_CHAR
      j++
    }
    let intermediateTextLength = intermediateText.length
    j = 0
    this.plainText = ''
    for (i = 0; i < intermediateTextLength; i += 5) {
      tempCh[0] = intermediateText[i]
      tempCh[1] = intermediateText[i + 1]
      tempCh[2] = intermediateText[i + 2]
      tempCh[3] = intermediateText[i + 3]
      tempCh[4] = intermediateText[i + 4]
      let index = ConvertCharacterListToNumber(tempCh)
      this.plainText += Message.SMALL[index]
      j++
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
    console.log('4. Set carrier text.')
    console.log('5. Exit.')
    choice = await askQuestion('Enter your choice : ')
    switch (choice) {
      case '1':
        text = await askQuestion('Enter plain text : ')
        flag = m.setPlainText(text)
        if (flag == 1) console.log('String contains special character(s).')
        console.log('Encrypted text : ' + m.encrypt())
        flag = await askQuestion('Do you want to decrypt (y/n) : ')
        if (flag == 'y' || flag == 'Y') console.log('Plain text : ' + m.decrypt())
        break
      case '2':
        text = await askQuestion('Enter encrypted text : ')
        flag = m.setEncryptedText(text)
        if (flag == 1) console.log('String contains special character(s).')
        console.log('Plain text : ' + m.decrypt())
        break
      case '3':
        text = await askQuestion('Enter ignore character list : ')
        m.setIgnoreChar(text)
        break
      case '4':
        text = await askQuestion('Enter carrier text : ')
        flag = m.setCarrierText(text)
        if (flag == 1) console.log('String contains special character(s).')
        break
      case '5':
        console.log('Exiting...')
        break
      default:
        console.log('Wrong choice try again..')
        break
    }
  } while (choice != '5')
}

main()
