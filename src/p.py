#board class has dimensions n by m, an integer bigM wich will be calculated later, and a list of lists of integers c, wich contains the number of elements per row
# the function returns a list [n,m,bigM,c]
class board:
    def __init__(self, n, m, c):
        self.n = n
        self.m = m
        self.c = c
        self.bigM = 0
    
def createBoard():
    n = int(input())
    m = int(input())
    for i in range(n):
        c.append(int(input()))
    return board(n,m,c)

def isEmtpy(b: board):
    for i in range(b.n):
        if b.c[i] > 0:
            return False
    return True

def getBigM(b: board):
    maxM = b.c[0]
    for i in range(b.n):
        if (maxM <= b.c[i]):
            maxM = b.c[i]
            b.bigM = i
    return b.bigM

def getMaxSquareSide(b: board):
    maxSide = 1
    bigM = getBigM(b)
    for i in range(bigM, 0, -1):
        if (maxSide == b.c[bigM]):
            break
        if (b.c[i] == 0):
            return 0
            break
        if (b.c[i] - b.c[i-1] == 0):
            maxSide += 1
        else:
            break
    return maxSide

def deleteSquare(b: board, side):
    for i in range(b.bigM, b.bigM - side + 1, -1):
        b.c[i] -= side
    b.bigM = getBigM(b)
    return b

def copyBoard(b: board):
    copy = board(b.n, b.m, b.c)
    return copy

def getCombinations(b: board):
        # combinations is a hash map with key = list of integers and value = int
    combinations = {}
    if (isEmtpy(b)):
        return 1
    max = getMaxSquareSide(b)
    #loop from i = 1 to i <= max and increment i by 1 each time
    for i in range(1, max + 1):
        copy = copyBoard(b)
        copy.bigM = getBigM(copy)
        deleteSquare(copy, i)
        # if the combination is already in the hash map then combinations[b.c] += combinations[copy.c]
        # else combinations[b.c] = getCombinations(copy)
        if (copy.c in combinations):
            combinations[b.c] += combinations[copy.c]
        else:
            combinations[b.c] = getCombinations(copy)

    # write a loop that prints the combinations hash map by key
    for key in combinations:
        print(key, combinations[key])
    return combinations[b.c]

def main():
    b = createBoard()
    print(getCombinations(b))

