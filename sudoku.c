/*
 * Sudoku Solver (brute-force).
 * This contains some "weird math" and bitwise operations
 * with the purpose of beeing fast as hell. It's pretty fast.
 * 2012 Anton Fagerberg [anton at antonfagerberg dot com]
 */
#include <stdio.h>
#include <stdint.h>

/* "Near worst case" Sudoku
 * http://en.wikipedia.org/wiki/Sudoku_algorithms#Brute-force_algorithm
 */
/*uint16_t puzzle[81] = {
	0,0,0,		0,0,0,			0,0,0,
	0,0,0,		0,0,1 << 3,		0,1 << 8,1 << 5,
	0,0,1 << 1,	0,1 << 2,0,		0,0,0,

	0,0,0,		1 << 5,0,1 << 7,	0,0,0,
	0,0,1 << 4,	0,0,0,			1 << 1,	0,0,
	0,1 << 9,0,	0,0,0,			0,0,0,

	1 << 5,	0,0,	0,0,0,			0,1 << 7,1 << 3,
	0,0,1 << 2,	0,1 << 1,0,		0,0,0,
	0,0,0,		0,1 << 4,0,		0,0,1 << 9
};*/

uint16_t puzzle[81] = {
	0, 0, 0,	0, 0, 0,	0, 0, 0,
	0, 0, 0,	0, 0, 0,	0, 0, 0,
	0, 0, 0,	0, 0, 0,	0, 0, 0,

	0, 0, 0,	0, 0, 0,	0, 0, 0,
	0, 0, 0,	0, 0, 0,	0, 0, 0,
	0, 0, 0,	0, 0, 0,	0, 0, 0,

	0, 0, 0,	0, 0, 0,	0, 0, 0,
	0, 0, 0,	0, 0, 0,	0, 0, 0,
	0, 0, 0,	0, 0, 0,	0, 0, 0
};

uint8_t solve(uint8_t i) {
	// Solved it!
	if (i == 81)
		return 1;

	// Skip the positions which are defined from the start.
	if (puzzle[i]) 
		return solve(i + 1);

	uint16_t valid_numbers = 0xFFFF;
	uint8_t n, m;

	for (n = 0; n < 9; n += 1) {
		// Check rows
		valid_numbers = valid_numbers & ~puzzle[ i % 9 + n * 9 ];

		// Check columns
		valid_numbers = valid_numbers & ~puzzle[ i / 9 * 9 + n ];
	}
	
	// Check "squares"
	for (n = 0; n < 3; n += 1)
		for (m = 0; m < 3; m += 1)
			valid_numbers = valid_numbers & ~puzzle[ 27 * (i / 9 / 3) + 3 * (i / 3 % 3) + n + (m * 9) ];

	uint16_t bit;
	for (m = 1; m < 10; m += 1) {
		bit = 1 << m;
		if (valid_numbers & bit) {
			puzzle[i] = bit;
			if (solve(i + 1))
				return 1;
			puzzle[i] = 0;
		}
	}

	return 0;
}

void print_puzzle() {
	uint8_t i;
	for (i = 0; i < 81; i += 1) {
		if (!(i % 27))
			printf("\n+-------+-------+-------+");
		if (!(i % 9))
			printf("\n");
		if (!(i % 3))
			printf("| ");
		int count = -1;
		while (puzzle[i]) {
			puzzle[i] = puzzle[i] >> 1;
			count++;
		}
		printf("%i ", count);
		if (i % 9 == 8)
			printf("|");
	}
	printf("\n+-------+-------+-------+\n");
}

int main() {
	solve(0);
	if (solve(0))
		print_puzzle();
	else
		printf("Did not solve puzzle. Check input...");
	return 0;
}