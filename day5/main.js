let fs = require("fs")
let range = require("./range.js")

class Cloud {
	constructor(list) {
		this.pt1 = { x: Number(list[0][0]), y: Number(list[0][1]) }
		this.pt2 = { x: Number(list[1][0]), y: Number(list[1][1]) }
	}
	isHorizontalOrVertical() {
		return this.pt1.x === this.pt2.x || this.pt1.y === this.pt2.y
	}
	drawline() {
		const x = this.pt1.x - this.pt2.x
		const y = this.pt1.y - this.pt2.y
		const xmin = Math.min(this.pt1.x, this.pt2.x)
		const ymin = Math.min(this.pt1.y, this.pt2.y)
		if (x<0) return range(this.pt1.x, this.pt2.x).map(x => new Object({x:x+xmin, y:this.pt1.y}))
		if (x>0) return range(this.pt2.x, this.pt1.x).map(x => new Object({x:x+xmin, y:this.pt1.y}))
		if (y<0) return range(this.pt1.y, this.pt2.y).map(y => new Object({x:this.pt1.x, y:y+ymin}))
		if (y>0) return range(this.pt2.y, this.pt1.y).map(y => new Object({x:this.pt1.x, y:y+ymin}))
	}
}

fs.readFile("input", "utf8" , (err, data) => {
  if (err) {
    console.error(err)
    return
  }
  data = data.split('\n')
  data = data.map(o => o.split("->").map(s => s.trim().split(','))) // lol c++ ...
  data = data.map(o => new Cloud(o))
  data = data.filter(o => o.isHorizontalOrVertical())
  let lines = data.map(o => o.drawline())
  let values = {}
  lines.forEach(l => {
  	l.forEach(q => {
  		if (!values[`${q.x}${q.y}`])
 	 			values[`${q.x}${q.y}`] = 0
 	 		values[`${q.x}${q.y}`]++
  	})
  })
  let total = 0
  for (const k in values) {
  	if (values[k] > 1) {
  		total++
  	}
  }
  console.log(total)
})