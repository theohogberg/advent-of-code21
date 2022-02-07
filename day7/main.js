let fs = require("fs")
let range = require("./range.js")

fs.readFile("input", "utf8" , (err, data) => {
  if (err) {
    console.error(err)
    return
  }
  data = data.split('\n')
  data = data.map(o => o.split("|").map(s => s.trim().split(','))) // lol c++ ...

})