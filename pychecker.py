import sys

def print_largest_square_grid(r, c, grid):
	S = [[0] * (c + 1) for _ in range(r + 1)]
	
	for i in range(1, r + 1):
		for j in range(1, c + 1):
			S[i][j] = (1 if grid[i-1][j-1] == 'o' else 0) + S[i-1][j] + S[i][j-1] - S[i-1][j-1]

	best_size = 0
	best_position = (0, 0)
	
	for i in range(r):
		for j in range(c):
			while True:
				k = best_size + 1
				if i + k > r or j + k > c:
					break
				obstacle_count = (S[i+k][j+k] - S[i+k][j] - S[i][j+k] + S[i][j])
				if obstacle_count == 0:
					best_size = k
					best_position = (i, j)
				else:
					break

	r_start, c_start = best_position
	result_grid = [list('.' if cell == '0' else 'o' for cell in row) for row in grid]

	for i in range(r_start, r_start + best_size):
		for j in range(c_start, c_start + best_size):
			result_grid[i][j] = 'x'

	print("py size BSQ = {}".format(best_size))
	print("py pos BSQ = ({}, {})".format(c_start, r_start))

	for row in result_grid:
		print("".join(row))
	

if __name__ == "__main__":
	if len(sys.argv) != 4:
		print("python pychecker.py r c map")
		sys.exit(1)

	r = int(sys.argv[1])
	c = int(sys.argv[2])
	flat_grid = sys.argv[3]

	if len(flat_grid) != r * c:
		print("Error len")
		sys.exit(1)

	grid = [flat_grid[i * c:(i + 1) * c] for i in range(r)]

	print_largest_square_grid(r, c, grid)
