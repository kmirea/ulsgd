#Chaz Louviere
#Why not play a rousing game of Minesweeper?

grid = []
	
def mapCreate(grid):
	xSize = 9
	ySize = 9
	columns = []
	rows = []
	grid = []
		
	for i in range(0,xSize):
		columns.append(chr(i+65)) #Converts x values to alpahabet starting with A
		#print(columns)

	for i in range(0,ySize):
		aRow = str(i+1)
		rows.append(aRow) #Starts row count at 1 rather than 0
		#print(rows)

	for i in columns:
		for q in rows:
			cell = ((ord(i)*10) + ord(q))-699
			grid.append(cell)
	print(grid)
	return grid
def setup():
	print("Welcome to Minesweeper.")
	bTotal = eval(input("How many bombs would you like? "))
	print(bTotal,"bombs?  Let's hope you can handle that many.\nGenerating death field...")
setup()

grid = mapCreate(grid)

bCheckInput = input("Choose a cell to check for mines: ")
bCheckInput = bCheckInput.capitalize()
bCheckInput = list(bCheckInput)
bCheckInput = 1

print(bCheckInput)

#Match input to the grid 

iSpace = -1

for i in range(0,len(grid)):
	if grid[i] != bCheckInput:
		iSpace = -1
	else:
		iSpace = i
		break

if iSpace == -1:
	print("Please try again")
print(iSpace)
