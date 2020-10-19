// Gregory D. Stula
// 10/18/20
// CS 325 HW 3 Problem 4

#include <algorithm>
#include <cstdlib>
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

// we are also including a parameter to know which item was selected
int knapsack_dp(std::vector<int>& prices, std::vector<int>& weights, std::vector<int>& selected, int m, int n)
{
    // create table
    std::vector<std::vector<int>> table(n + 1, std::vector<int>(m + 1));

    // build the table
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= m; w++) {
            if (i == 0 || w == 0) {
                table[i][w] = 0;
            }
            else if (weights[i - 1] <= w) {
                // source of formula: https://www.youtube.com/watch?v=nLmhmB6NzcM
                table[i][w] = std::max(prices[i - 1] + table[i - 1][w - weights[i - 1]], table[i - 1][w]);
            }
            else {
                table[i][w] = table[i - 1][w];
            }
        }
    }

    // find each item in the knapsack
    // source: https://www.geeksforgeeks.org/printing-items-01-knapsack/
    int res = table[n][m];
    // capacity used
    int cap = m;

    for (int i = n; i > 0 && res > 0; i--) {
        // either the result comes from the top
        // (table[i-1][m2]) or from (prices[i-1] + table[i-1]
        // [w-wt[i-1]]) as in Knapsack table. If
        // it comes from the latter one/ it means
        // the item is included.
        if (res == table[i - 1][cap]) {
            continue;
        }
        else {
            // this item was included
            selected.push_back(weights[i - 1]);
            // deduct the included weight
            res = res - prices[i - 1];
            cap = cap - weights[i - 1];
        }
    }

    // will be the maximum price
    return table[n][m];
}

int main()
{
    int cases; // T -- number of test cases
    int n; // N -- number of items
    int members = 0; // F -- family members
    int max_capacity; // M -- weight each member can carry
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
        std::vector<int> prices; // P -- prices
        std::vector<int> weights; // W -- weight

        input >> n;

        for (int j = 0; j < n; j++) {
            // insert price into the vector
            int tmp;
            input >> tmp;
            prices.push_back(tmp);
            // insert weight into the vector
            input >> tmp;
            weights.push_back(tmp);
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

        std::vector<std::vector<int>> selected(members, std::vector<int>());
        for (int j = 0; j < members; j++) {
            input >> max_capacity;
            std::cout << max_capacity << std::endl;
            max_total_price = max_total_price + knapsack_dp(prices, weights, selected[j], max_capacity, n);
        }

        // get index of selected items

        output << "Test Case " << i + 1 << std::endl;
        output << "Total Price " << max_total_price << std::endl;

        // output the selected items indices
        for (int j = 0; j < members; j++) {
            output << j + 1 << ": ";
            // get current family members selections
            auto curr = selected[j];

            // sort
            std::sort(curr.begin(), curr.end());

            for (auto&& k : curr) {
                // find the index of the weight
                // using C++ iterators
                auto itr = std::find(weights.begin(),weights.end(), k);
                // output index
                output << distance(weights.begin(), itr) + 1 << " ";

            }
            output << std::endl;
        }
    }
    output.close();
    input.close();
}
