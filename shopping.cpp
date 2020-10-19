// Gregory D. Stula
// 10/18/20
// CS 325 HW 3 Problem 4

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <vector>

/*
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

        // get number of family members
        input >> members;
        int max_total_price = 0;

        // find the maximum price of items that can be carried for each family member
        // total the maximum price

        std::vector<std::vector<int>> selected(members, std::vector<int>());
        for (int j = 0; j < members; j++) {
            input >> max_capacity;
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

            // reverse iterate so output ascending
            for (int k = curr.size() - 1; k >= 0; k--) {
                // find the index of the weight
                // using C++ iterators
                auto itr = std::find(weights.begin(), weights.end(), curr[k]);
                // output index
                output << distance(weights.begin(), itr) + 1 << " ";

            }
            output << std::endl;
        }
    }
    output.close();
    input.close();
}
