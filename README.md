Tabu-Search Algorithm
Objective: Utilize the Tabu Search algorithm to find the optimal (or near-optimal) solution for the deception problem.

Parameters:

Number of Bits (NUM_BITS): 50
Desired Maximum Tabu List Length (MAX_TABU_LENGTH)
Number of Iterations (NUM_ITERATIONS): 1000
Number of Tweaks (NUM_TWEAK): Specifies the number of tweaks desired to sample the gradient
Deception Problem
The deception problem is defined as follows:

scss
Copy code
f(x) = |B2D(s) - 2^(n-2)|
Where:

s_i ∈ {0,1} represents binary bits.
n > 2 is the number of bits.
Tweak Methods
In this implementation, four tweak methods are employed:

Flip One Bit Randomly: Changes one bit randomly.
Flip Bits from Random Index to LSB (Least Significant Bit): Changes bits from a random index to the LSB.
Flip Bits from MSB (Most Significant Bit) to Random Index: Changes bits from the MSB to a random index.
Increment Binary Value by One: Adds one to the binary value.
Algorithm Description
The Tabu-Search algorithm iteratively explores the solution space, utilizing various tweak methods to search for the optimal solution while avoiding getting trapped in local optima. The algorithm maintains a tabu list to store recently visited solutions, preventing revisiting them in subsequent iterations. The process continues until the termination condition is met or the maximum number of iterations is reached.
