// Gregory D. Stula
// 10/18/20
// CS 325 HW 3 Problem 4

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

// Original Recursive code:
// source: geeksforgeeks (https://www.geeksforgeeks.org/0-1-knapsack-problem-dp-10/)

int knapsack(std::vector<int>& prices, std::vector<int>& weights, int capacity, int n)
{

    // base case
    if (n == 0 || capacity == 0) return 0;

    // ignore items which weight is more than the capacity
    // since it cannot be included in the optimal solution
    if (weights[n] > capacity) {
        return knapsack(prices, weights, capacity, n - 1);
    }
    else {
        // recusively go through the array and
        // return the maximum of nth item included, nth item not included
        return std::max(prices[n] + knapsack(prices, weights, capacity - weights[n], n - 1),
            knapsack(prices, weights, capacity, n - 1));
    }
}

/*
source: geeksforgeeks (https://www.geeksforgeeks.org/0-1-knapsack-problem-dp-10/)
In the following recursion tree, K() refers
to knapSack(). The two parameters indicated in the
following recursion tree are n and W.
The recursion tree is for following sample inputs.
wt[] = {1, 1, 1}, W = 2, val[] = {10, 20, 30}
                       K(n, W)
                       K(3, 2)
                   /            \
                 /                \
            K(2, 2)                  K(2, 1)
          /       \                  /    \
        /           \              /        \
       K(1, 2)      K(1, 1)        K(1, 1)     K(1, 0)
       /  \         /   \          /   \
     /      \     /       \      /       \
K(0, 2)  K(0, 1)  K(0, 1)  K(0, 0)  K(0, 1)   K(0, 0)
Recursion tree for Knapsack capacity 2
units and 3 items of 1 unit weight.

The recursive solution computes the same sub-problems again and again. K(1, 1) is being evaluated twice.
The time complexity of this naive recursive solution is exponential (2^n).

Dynamic Programming Technique:
We can create a table that considers all the possible weights from ‘1’ to ‘M’
as the columns and weights that can be kept as the rows.
This is the approach we will use here.

*/

int main()
{
    int cases; // T -- number of test cases
    int n; // N -- number of items
    int members = 0; // F -- family members
    int max_capacity; // M -- weight each member can carry
    std::vector<int> prices; // P -- prices
    std::vector<int> weights; // W -- weight

    prices.reserve(100);
    weights.reserve(100);
    // output file
    std::ofstream output;
    // input file
    std::ifstream input;
    input.open("shopping.txt");
    output.open("shopping.out");

    // first line of the file is the number of test cases
    input >> cases;

    // process each test case
    for (int i = 0; i < cases; i++) {
        input >> n;

        for (int j = 0; j < n; j++) {
            // insert price into the vector
            input >> prices[j];
            // insert weight into the vector
            input >> weights[j];
        }

        for (int p = 0; p < n; p++) {
            std::cout << prices[p] << " ";
            std::cout << weights[p] << std::endl;
        }

        // get number of family members
        input >> members;
        std::cout << members << std::endl;
        int max_total_price = 0;

        // find the maximum price of items that can be carried for each family member
        // total the maximum price

        for (int j = 0; j < members; j++) {
            input >> max_capacity;
            std::cout << max_capacity << std::endl;
            max_total_price = max_total_price + knapsack(prices, weights, max_capacity, n);
        }

        output << "Test Case " << i + 1 << std::endl;
        output << "Total Price " << max_total_price << std::endl;
    }
    output.close();
    input.close();
}
