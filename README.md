## DISCLAIMER

This document was quickly written to assist the evaluators of this BSQ during my 42 piscine. It contains mistakes and inaccuracies.
Additionally, the code was written by two coding beginners, so errors and a lack of rigor in the code are to be expected while reading it.
Any corrections are welcome.

If you are using a dark theme, the formulas may be hard to read. Click on them!

PDF version is available.
## Step one : Precomputation

This is our precomputing formula:

![formula](https://latex.codecogs.com/png.latex?\\color{Black}%20S[i][j]%20=%20\\sum_{r=1}^{i}%20\\sum_{c=1}^{j}\\text{grid}[r-1][c-1])

This is a \( (r+1, c+1) \) map, 0 is empty and 1 is obstacle, we just add a some 0 in \( r(0) \) and \( c(0) \) :


	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0]
	[0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0]
	[0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
	[0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0]
	[0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]


And this is an empty \( (r+1, c+1) \) map:

    [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]

We start with a \((r+1, c+1)\) matrix where we add \(+1\) because the algorithm considers positions behind the current one. This ensures that indices r<sub>0</sub> and c<sub>0</sub> have the value 0.
![formula](https://latex.codecogs.com/png.latex?\\color{Black}%20∀%20(a,%20b)%20∈%20S(r,%20c),%20(0,%20a)%20=%200%20,%20(0,%20b)%20=%200)
We use the formula: 
![formula](https://latex.codecogs.com/png.latex?\\color{Black}%20S[r][c]%20=%20S[r-1][c]%20+%20S[r][c-1]%20-%20S[r-1][c-1]%20+%20(1%20\\text{%20or%20}%200))

Let's delve into the details:

- \( S[r-1][c] = 6 \)
- \( S[r][c-1] = 7 \)
- \( S[r-1][c-1] = 5 \)

In our map, we have no obstacle at this position, so:

![formula](https://latex.codecogs.com/png.latex?\\color{Black}%20S[r][c]%20=%206%20+%207%20-%205%20+%200%20=%208)

The general concept is to calculate how many obstacles we have already encountered behind our current position. We consider behind us as the leftward and upward directions, similar to a vector from the origin.


	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  ,  0 ,  0, 0]
	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1  ,  2 ,  2, 2]
	[0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2  ,  3 ,  3, 3]
	[0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3  ,  4 ,  4, 4]
	[0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 3, 4, 4, 4, [5], [6],  6, 6]
	[0, 0, 0, 0, 0, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 5, 6, 6, 6, [7], {8},  0, 0]
	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  ,  0 ,  0, 0]
	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  ,  0 ,  0, 0]
	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  ,  0 ,  0, 0]
	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  ,  0 ,  0, 0]

	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0  , 0, 0]
	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, S, 0, 0, 0, 0  , C  , 0, 0]
	[0, 0, 0, 0, 0, S, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0  , 0, 0]
	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, S, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0  , 0, 0]
	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, S, 0, 0,[X] ,[0] , 0, 0]
	[0, 0, 0, 0, 0, R, 0, 0, 0, R, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,[0] ,{0} , 0, 0]
	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0  , 0  , 0, 0]
	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0  , 0, 0]
	[0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0  , 0  , 0, 0]
	[0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0  , 0, 0]


So now we have our filled tab, and on each postion we can know how many obsactles we have behind us include ourself

	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 ]
	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 , 1 , 1 , 1 , 2 , 2 , 2 ]
	[0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2 , 2 , 2 , 2 , 3 , 3 , 3 ]
	[0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 3, 3 , 3 , 3 , 3 , 4 , 4 , 4 ]
	[0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 3, 4 , 4 , 4 , 5 , 6 , 6 , 6 ]
	[0, 0, 0, 0, 0, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 5, 6 , 6 , 6 , 7 , 8 , 8 , 8 ]
	[0, 0, 0, 0, 0, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 5, 5, 5, 5, 6, 7 , 7 , 7 , 8 , 9 , 9 , 9 ]
	[0, 0, 0, 0, 0, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 5, 5, 5, 5, 6, 7 , 7 , 7 , 8 , 9 , 9 , 9 ]
	[0, 0, 0, 0, 0, 2, 2, 3, 3, 4, 4, 4, 4, 5, 5, 5, 6, 6, 6, 6, 7, 8 , 9 , 9 , 10, 11, 11, 11]
	[0, 0, 0, 1, 1, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 7, 8, 8, 8, 8, 9, 10, 11, 11, 12, 13, 13, 13]

	
## Step Two : Computation

Now let's take a look at the main algorithm. Initially, we consider that there is at least one 0x0 solution, so we start looking for a 1x1 solution.

We loop through rows and columns and examine the values in our table at positions \(c + k\) and \(r + k\). Let's see how it works:

Now we will use the formula:
![formula](https://latex.codecogs.com/png.latex?\\color{Black}%20S[r+k][c+k]%20-%20S[r+k][c]%20-%20S[r][c+k]%20+%20S[r][c])

Here, \( S[r][c] \) is our first case. We can easily compute:
![formula](https://latex.codecogs.com/png.latex?\\color{Black}%200%20-%200%20-%200%20+%200%20=%200)

Now we know that our first position in {0} is a 1x1 solution. The rule is to print only the topmost and leftmost solution. Therefore, if there is no 2x2 solution, the 1x1 solution at (0,0) is our final solution, and we stop.

So now we will look for the 2x2 square.


	[ {0}, [0], 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 ]
	[ [0], [0], 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 , 1 , 1 , 1 , 2 , 2 , 2 ]
	[  0 , 0,  0,  0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2 , 2 , 2 , 2 , 3 , 3 , 3 ]
	[  0 , 0,  0,  0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 3, 3 , 3 , 3 , 3 , 4 , 4 , 4 ]
	[  0 , 0,  0,  0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 3, 4 , 4 , 4 , 5 , 6 , 6 , 6 ]
	[  0 , 0,  0,  0, 0, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 5, 6 , 6 , 6 , 7 , 8 , 8 , 8 ]
	[  0 , 0,  0,  0, 0, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 5, 5, 5, 5, 6, 7 , 7 , 7 , 8 , 9 , 9 , 9 ]
	[  0 , 0,  0,  0, 0, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 5, 5, 5, 5, 6, 7 , 7 , 7 , 8 , 9 , 9 , 9 ]
	[  0 , 0,  0,  0, 0, 2, 2, 3, 3, 4, 4, 4, 4, 5, 5, 5, 6, 6, 6, 6, 7, 8 , 9 , 9 , 10, 11, 11, 11]
	[  0 , 0,  0,  1, 1, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 7, 8, 8, 8, 8, 9, 10, 11, 11, 12, 13, 13, 13]


This is the BSQ assuming the is not more than a 4*4 solution
	
	.....HHHH..........o....o..
	.....HHHH..................
	.....HHHH...o...o..........
	.....HHHH...........o..o...
	....o...o..................
	...............o...........
	...........................
	......o..............o.....
	..o.......o................

## More than one?

Again, \( k \) is the size of the square we are looking for. \( k \) is 1 plus our best solution.

To continue, let's take the step of looking for a 5x5 square. Suppose we assume we are at \( k = 5 \), but our best solution so far is a 4x4 square.

Now, we start again from the beginning, knowing that we are looking for a 5*5 square. We will use the formula:
![formula](https://latex.codecogs.com/png.latex?\\color{Black}%20S[r+k][c+k]%20-%20S[r+k][c]%20-%20S[r][c+k]%20+%20S[r][c])

Now we have:
![formula](https://latex.codecogs.com/png.latex?\\color{Black}%20S[5][5]%20-%20S[5][0]%20-%20S[0][5]%20+%20S[0][0])
![formula](https://latex.codecogs.com/png.latex?\\color{Black}%202%20-%200%20-%200%20+%200%20=%202%20\\neq%200)

This is not a solution.

 
	[ {0}, 0, 0, 0, 0, [0], 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 ]
	[  0 , 0, 0, 0, 0,  0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 , 1 , 1 , 1 , 2 , 2 , 2 ]
	[  0 , 0, 0, 0, 0,  1 , 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2 , 2 , 2 , 2 , 3 , 3 , 3 ]
	[  0 , 0, 0, 0, 0,  1 , 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 3, 3 , 3 , 3 , 3 , 4 , 4 , 4 ]
	[  0 , 0, 0, 0, 0,  1 , 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 3, 4 , 4 , 4 , 5 , 6 , 6 , 6 ]
	[ [0], 0, 0, 0, 0, [2], 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 5, 6 , 6 , 6 , 7 , 8 , 8 , 8 ]
	[  0 , 0, 0, 0, 0,  2 , 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 5, 5, 5, 5, 6, 7 , 7 , 7 , 8 , 9 , 9 , 9 ]
	[  0 , 0, 0, 0, 0,  2 , 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 5, 5, 5, 5, 6, 7 , 7 , 7 , 8 , 9 , 9 , 9 ]
	[  0 , 0, 0, 0, 0,  2 , 2, 3, 3, 4, 4, 4, 4, 5, 5, 5, 6, 6, 6, 6, 7, 8 , 9 , 9 , 10, 11, 11, 11]
	[  0 , 0, 0, 1, 1,  3 , 3, 4, 4, 5, 5, 6, 6, 7, 7, 7, 8, 8, 8, 8, 9, 10, 11, 11, 12, 13, 13, 13]

# Searching for a 5x5 Solution

Again, we try one step to the right, starting from the (0,1) position. If (0,0) is not a solution, we increment \( r \) by 1. If \( r(0) \) is not a solution, we move to \( c(1) \) and start from (0,1).

In this case, we found a solution at (0,13).

Let's calculate the function:
![formula](https://latex.codecogs.com/png.latex?\\color{Black}%20S[0+5][13+5]%20-%20S[0+5][13]%20-%20S[0][13+5]%20+%20S[0][13])
![formula](https://latex.codecogs.com/png.latex?\\color{Black}%204%20-%204%20-%200%20+%200%20=%200)

We found a solution for the 5x5 square.


	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,{0}, 0, 0, 0, 0,[0], 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 ]
	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 , 0, 0, 0, 0, 0 , 0, 1, 1 , 1 , 1 , 1 , 2 , 2 , 2 ]
	[0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1 , 1, 1, 1, 1, 1 , 1, 2, 2 , 2 , 2 , 2 , 3 , 3 , 3 ]
	[0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 2 , 2, 2, 2, 2, 2 , 2, 3, 3 , 3 , 3 , 3 , 4 , 4 , 4 ]
	[0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 2 , 2, 2, 2, 2, 2 , 2, 3, 4 , 4 , 4 , 5 , 6 , 6 , 6 ]
	[0, 0, 0, 0, 0, 2, 2, 2, 2, 3, 3, 3, 3,[4], 4, 4, 4, 4,[4], 4, 5, 6 , 6 , 6 , 7 , 8 , 8 , 8 ]
	[0, 0, 0, 0, 0, 2, 2, 2, 2, 3, 3, 3, 3, 4 , 4, 4, 5, 5, 5 , 5, 6, 7 , 7 , 7 , 8 , 9 , 9 , 9 ]
	[0, 0, 0, 0, 0, 2, 2, 2, 2, 3, 3, 3, 3, 4 , 4, 4, 5, 5, 5 , 5, 6, 7 , 7 , 7 , 8 , 9 , 9 , 9 ]
	[0, 0, 0, 0, 0, 2, 2, 3, 3, 4, 4, 4, 4, 5 , 5, 5, 6, 6, 6 , 6, 7, 8 , 9 , 9 , 10, 11, 11, 11]
	[0, 0, 0, 1, 1, 3, 3, 4, 4, 5, 5, 6, 6, 7 , 7, 7, 8, 8, 8 , 8, 9, 10, 11, 11, 12, 13, 13, 13]

## Searching for a 6x6 Solution

When we reach \((r + 6, c + 6) = (r_{\text{max}}, c_{\text{max}})\) without finding any solution, we know there is no square larger than 5x5. This is because any larger square than 6x6 would contain a 6x6 square.

With this method, we can find the first square in the top-left corner by trying to find it row by row, starting from the left.

**Note:** This algorithm provides an \(O(x, y)\) solution on the S<sub>tab</sub>, but the S<sub>tab</sub> is \((r, c)\) sized, so we have:

![formula](https://latex.codecogs.com/png.latex?\\color{Black}%20\\text{Stab%20size}%20=%20(y+1,%20x+1))


	[S, X, X, X, X, X]
	[X, H, H, H, H, H]
	[X, H, H, H, H, H]
	[X, H, H, H, H, H]
	[X, H, H, H, H, H]
	[X, H, H, H, H, H]

here S ithe coordonate in S<sub>tab</sub>, but we have a \((-1, -1)\) vector translate to operate to come back in the map. 
So the S<sub>\(x, y)</sub> postion is the right position of the topside/leftside BSQ in the map.

# CQFD

## Bonus

## Generalized N-Dimensional Cumulative Sum Matrix

For an N-dimensional grid, the cumulative sum matrix \(S\) is defined as:

![formula](https://latex.codecogs.com/png.latex?\\color{Black}%20S[i_1][i_2][\\ldots][i_N]%20=%20\\sum_{a_1=1}^{i_1}%20\\sum_{a_2=1}^{i_2}%20\\ldots%20\\sum_{a_N=1}^{i_N}%20\\text{grid}[a_1-1][a_2-1][\\ldots][a_N-1])

Where:
- \( S[i_1][i_2][\ldots][i_N] \) represents the cumulative sum of elements in the sub-grid from \((1,1,\ldots,1)\) to \((i_1, i_2, \ldots, i_N)\).
- \(\text{grid}[a_1-1][a_2-1][\ldots][a_N-1]\) is the value of the cell at position \((a_1-1, a_2-1, \ldots, a_N-1)\) in the original grid.

The recursive formula for calculating \(S\) is:

![formula](https://latex.codecogs.com/png.latex?\\color{Black}%20S[i_1][i_2][\\ldots][i_N]%20=%20\\text{grid}[i_1-1][i_2-1][\\ldots][i_N-1]%20+%20\\sum_{j=1}^{N}%20S[\\ldots,%20i_j-1,%20\\ldots]%20-%20\\sum_{1%20\\leq%20j%20<%20k%20\\leq%20N}%20S[\\ldots,%20i_j-1,%20\\ldots,%20i_k-1,%20\\ldots]%20+%20\\ldots%20+%20(-1)^{N-1}%20S[i_1-1][i_2-1][\\ldots][i_N-1])

## Obstacle Count in a Sub-Hypercube

For a sub-hypercube defined by its top-left corner \((i_1, i_2, \ldots, i_N)\) and side length \(d\), the number of obstacles is:

![formula](https://latex.codecogs.com/png.latex?\\color{Black}%20\\text{obstacle\\_count}%20=%20S[i_1+d][i_2+d][\\ldots][i_N+d]%20-%20\\sum_{j=1}^{N}%20S[\\ldots,%20i_j,%20\\ldots,%20i_j+d,%20\\ldots]%20+%20\\sum_{1%20\\leq%20j%20<%20k%20\\leq%20N}%20S[\\ldots,%20i_j,%20\\ldots,%20i_k,%20\\ldots,%20i_j+d,%20i_k+d,%20\\ldots]%20-%20\\ldots%20+%20(-1)^{N}%20S[i_1][i_2][\\ldots][i_N])

Where:
- \( S[i_1+d][i_2+d][\ldots][i_N+d] \) is the cumulative sum up to the far corner of the sub-hypercube.
- The alternating sums and subtractions adjust for over-counted regions at the intersections of the sub-hypercube boundaries.
	
Bastian you rock
