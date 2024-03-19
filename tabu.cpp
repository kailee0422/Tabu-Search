#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define NUM_BITS 50
#define MAX_TABU_LENGTH 10 //Desired maximum tabu list length
#define NUM_ITERATIONS 1000
#define NUM_TWEAK 2 //number of tweaks desired to sample the gradient

// Function to generate initial solution
void generate_initial_solution(int solution[], int num_bits) {
	for (int i = 0; i < num_bits; i++) {
		solution[i] = rand() % 2; // Generate random bit(0/1)
	}
}

// Function to tweak the solution (flip one random bit)
void tweak_one_bit(int solution[], int num_bits) {
	int index = rand() % num_bits; // Choose a random index to flip
	solution[index] = 1 - solution[index]; // Flip the bit
}

// Function to tweak the solution (flip all bits from index to LSB)
void tweak_index_to_LSB(int solution[], int num_bits) {
	int index = rand() % num_bits; // Choose a random index
	for (int i = index; i < num_bits; i++) {
		solution[i] = 1 - solution[i];
	}
}

// Function to tweak the solution (flip all bits from MSB to index)
void tweak_MSB_to_index(int solution[], int num_bits) {
	int index = rand() % num_bits; // Choose a random index
	for (int i = 0; i < index; i++) {
		solution[i] = 1 - solution[i];
	}
}

// Function to tweak the solution (add 1 to the binary number)
void tweak_add_one(int solution[], int num_bits) {
	int carry = 1; // Start with a carry of 1
	for (int i = num_bits - 1; i >= 0; i--) {
		if (solution[i] == 0 && carry == 1) {
			solution[i] = 1; // Flip 0 to 1 if carry is 1
			carry = 0;
		}
		else if (solution[i] == 1 && carry == 1) {
			solution[i] = 0; // Flip 1 to 0 if carry is 1
			// carry remains 1
		}
	}
}

// Function to tweak the solution (flip even bits)
void tweak_even_bit(int solution[], int num_bits) {
	for (int i = 0; i < num_bits; i+=2) {
		solution[i] = 1 - solution[i];
	}
}

// Function to tweak the solution (flip odd bits)
void tweak_odd_bit(int solution[], int num_bits) {
	for (int i = 1; i < num_bits; i+=2) {
		solution[i] = 1 - solution[i];
	}
}

// Function to compute the quality of the solution(Deception Problem's formula)
int quality(int solution[], int num_bits) {
	int a = 0;
	// Convert binary to decimal
	int weight = 1;
	for (int i = num_bits - 1; i >= 0; i--) {
		if (solution[i] == 1) {
			a += weight;
		}
		weight *= 2; // Double the weight for the next bit
	}
	int b = (int)pow(2, num_bits - 2);
	return abs(a - b);
}


// Function to check if a solution is in the tabu list
bool is_in_tabu_list(int solution[], int tabu_list[][NUM_BITS], int tabu_list_size, int num_bits) {
	for (int i = 0; i < tabu_list_size; i++) {
		bool equal = true;
		for (int j = 0; j < num_bits; j++) {
			if (solution[j] != tabu_list[i][j]) {
				equal = false;
				break;
			}
		}
		if (equal) {
			return true;
		}
	}
	return false;
}

// Tabu Search function
int tabu_search(int num_iterations, int num_bits, int max_tabu_length, void (*tweak)(int[], int)) {
	int S[NUM_BITS];
	int Best[NUM_BITS];
	int L[MAX_TABU_LENGTH][NUM_BITS];//tabu table
	int L_size = 0;//record num of tabu table's list

	generate_initial_solution(S, num_bits);// S <-some initial candidate solution

	for (int i = 0; i < num_bits; i++) {
		Best[i] = S[i];//Best<-S
	}

	for (int j = 0; j < num_bits; j++) {
		L[L_size][j] = S[j];// Enqueue S into L
	}

	L_size++;
	//Here I don't use Algorithm way(until Best is the ideal solution or we have run out of time)
	for (int i = 0; i < num_iterations; i++) {
		if (L_size > max_tabu_length) {
			//Remove oldest element from L (L[0] is oldest)
			for (int j = 0; j < max_tabu_length - 1; j++) {
				for (int k = 0; k < num_bits; k++) {
					L[j][k] = L[j + 1][k];
				}
			}
			L_size--;
		}
		int R[NUM_BITS];
		for (int j = 0; j < num_bits; j++) {
			R[j] = S[j];//Copy of S
		}
		tweak(R, num_bits);//R<-Tweak(Copy(S))
		for (int j = 0; j < NUM_TWEAK - 1; j++) {
			int W[NUM_BITS];
			for (int k = 0; k < num_bits; k++) {
				W[k] = R[k];
			}
			tweak(W, num_bits); // W <- Tweak(Copy(S))

			if (!is_in_tabu_list(W, L, L_size, num_bits) && (quality(W, num_bits) > quality(R, num_bits) || is_in_tabu_list(R, L, L_size, num_bits))) {
				for (int k = 0; k < num_bits; k++) {
					R[k] = W[k];
				}
			}
		}

		if (!is_in_tabu_list(R, L, L_size, num_bits)) {
			for (int j = 0; j < num_bits; j++) {
				S[j] = R[j];//S<-R
			}
			if (L_size < MAX_TABU_LENGTH) {
				// Enqueue R into L
				for (int j = 0; j < num_bits; j++) {
					L[L_size][j] = R[j];
				}
				L_size++;
			}
			else {
				// Remove oldest element from L (L[0] is oldest)
				for (int i = 0; i < MAX_TABU_LENGTH - 1; i++) {
					for (int j = 0; j < num_bits; j++) {
						L[i][j] = L[i + 1][j];
					}
				}
				// Enqueue R into L
				for (int j = 0; j < num_bits; j++) {
					L[MAX_TABU_LENGTH - 1][j] = R[j];
				}
			}
		}

		if (quality(S, num_bits) > quality(Best, num_bits)) {
			for (int j = 0; j < num_bits; j++) {
				Best[j] = S[j];
			}
		}

	}

	printf("Best solution found: ");
	for (int i = 0; i < num_bits; i++) {
		printf("%d", Best[i]);
	}
	printf("\nQuality of the best solution: %d\n", quality(Best, num_bits));
	return quality(Best, num_bits);
}

int main() {
	srand(time(NULL));

	printf("tweak_one_bit (Flip one random bit):\n");
	int quality1 = tabu_search(NUM_ITERATIONS, NUM_BITS, MAX_TABU_LENGTH, tweak_one_bit);

	printf("\ntweak_index_to_LSB (Flip all bits from a random index to LSB):\n");
	int quality2 = tabu_search(NUM_ITERATIONS, NUM_BITS, MAX_TABU_LENGTH, tweak_index_to_LSB);

	printf("\ntweak_MSB_to_index (Flip all bits from MSB to a random index):\n");
	int quality3 = tabu_search(NUM_ITERATIONS, NUM_BITS, MAX_TABU_LENGTH, tweak_MSB_to_index);

	printf("\ntweak_add_one (Add 1 to the binary number):\n");
	int quality4 = tabu_search(NUM_ITERATIONS, NUM_BITS, MAX_TABU_LENGTH, tweak_add_one);

	printf("\ntweak_even_bit (flip even bits):\n");
	int quality5 = tabu_search(NUM_ITERATIONS, NUM_BITS, MAX_TABU_LENGTH, tweak_even_bit);

	printf("\ntweak_odd_bit (flip odd bits):\n");
	int quality6 = tabu_search(NUM_ITERATIONS, NUM_BITS, MAX_TABU_LENGTH, tweak_odd_bit);

	// Find the best tweak method
	int best_quality = quality1;
	int best_tweak = 1;
	if (quality2 > best_quality) {
		best_quality = quality2;
		best_tweak = 2;
	}
	if (quality3 > best_quality) {
		best_quality = quality3;
		best_tweak = 3;
	}
	if (quality4 > best_quality) {
		best_quality = quality4;
		best_tweak = 4;
	}
	if (quality5 > best_quality) {
		best_quality = quality5;
		best_tweak = 5;
	}
	if (quality6 > best_quality) {
		best_quality = quality6;
		best_tweak = 6;
	}

	printf("\nThe best tweak method is Tweak %d with a quality of %d\n", best_tweak, best_quality);
	system("PAUSE");
	return 0;
}
