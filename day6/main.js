let fs = require("fs")

let gen = 0;

function nextGen(fish) {
  const fishNum = fish.length
  for(let i = fishNum-1; i > -1; i--) {
    const n = fish[i]
    if (n === 0) {
      fish[i] = 6
      fish.push(8)
    }
    else {
      fish[i]--
    }
  }
  gen++
  return fish
}

fs.readFile("input", "utf8" , (err, data) => {
  if (err) {
    console.error(err)
    return
  }
  data = data.split(',').map(o => Number(o))
  data = nextGen(data)
  fs.writeFileSync("data", new Uint32Array(data))
  // for(let i = 0; i <= 5; i++) {
  let savedData = fs.readSync("./data", { encoding:"binary", flag:'r' })
  console.log(savedData)
  //   data = nextGen(data)
  //   console.log(i, data.length)
  //   fs.writeFileSync("data.dat", data)
  // }
})