def main():

	grid = createGrid(9,9)

	maxMines = eval(input("How many mines: "))
	
	print(grid)

def createGrid(xSize,ySize):
	xList = []
	yList = []
	grid = []
	
	for i in range(xSize):
		xCell = chr(65 + i)
		xList.append(xCell)
		
	for i in range(ySize):
		yCell = i
		yList.append(yCell)
		 
	for i in xList:
		grid.append(yList)
		
			
	return (grid)

def fillDeathField(grid,maxMines):
	mineCount = 0
	






main()
