let fs = require("fs")

fs.readFile("input", "utf8" , (err, data) => {
  if (err) {
    console.error(err)
    return
  }
  data = data.split('\n')
  data = data.map(o => o.split("|").map(s => s.trim().split(','))) // lol c++ ...
  data = data.map(o => o[1][0].split(' '))
	// get 2, 3, 4, 7
	let total = 0
	data.forEach(l => {
		l.forEach(w => {
			const len = w.length
			if (len == 2 || len == 3 || len == 4 || len == 7) {
				total++
			}
		})
	})
	console.log(total)
})