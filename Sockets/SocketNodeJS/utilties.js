const readline = require('node:readline')

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

function createUniqueId(arrList, { min = 1, max = 1000 }) {
  let randomId, flag
  let len = arrList.length
  do {
    randomId = Math.floor(Math.random() * (max - min + 1)) + min
    flag = 0
    for (let i = 0; i < len; i++) {
      const e = arrList[i]
      if (e === randomId) flag = 1
    }
  } while (flag !== 0)
  return new Promise((resolve) => {
    resolve(randomId)
  })
}

// console.log(createUniqueId([1], {}))
module.exports = { askQuestion, createUniqueId }
