let fs = require("fs")

fs.readFile("input", "ascii" , (err, data) => {
  if (err) {
    console.error(err)
    return
  }
	
  data = data.split('\n').slice(0, -1)
		.map(l => l.split('')
			.map(s => +s))

	// save low points
	let lows = []
	let total = 0
	const rows = data.length
	const columns = data.at(0).length

	for (let y=0; y<rows; y++)
	{
		for (let x=0; x<columns; x++)
		{
			let tar = 	data.at(y).at(x) // target

			// omg javascript.
			let down = 		data[y+1]?.at(x) 
			if (down === 	undefined) down = Infinity
			let up = 			data[y-1]?.at(x)
			if (up === 		undefined) up = Infinity
			let right = 	data[y][x+1]
			if (right === undefined) right = Infinity
			let left = 		data[y][x-1]
			if (left === 	undefined) left = Infinity
			
			if (tar<down && tar<up && tar<right && tar<left)
			{ // low point found! save and add 1
				lows.push(tar)
				total += (tar+1)
			}
		}
	}
	// answer
	console.log(lows)
	console.log(total)
})

