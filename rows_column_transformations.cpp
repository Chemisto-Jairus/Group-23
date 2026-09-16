/** 
C++ Matrix Transformation Utility

A lightweight C++ data manipulation library for performing row-wise and column-wise mathematical transformations on 2D matrices (`std::vector<std::vector<double>>`).

## Features

* **Row Difference (`row_difference`)**: Computes consecutive element differences across each row.
* **Column Difference (`column_difference`)**: Computes consecutive row differences within each column.
* **Row Percentage (`row_percentage`)**: Calculates each element's percentage contribution relative to its row sum.
* **Column Percentage (`column_percentage`)**: Calculates each element's percentage contribution relative to its column sum.
* **Row Normalization (`row_normalize`)**: Scales each row's values to a `[0.0, 1.0]` range using Min-Max scaling.
* **Matrix Printer (`printDataFrame`)**: Formats and prints 2D numerical matrices to stdout with uniform column alignment.

## Prerequisites

* **Compiler**: Any C++11 compatible compiler (`g++`, `clang++`, or MSVC).
* **Build System**: Terminal/Command Line or an IDE such as VS Code or CLion.

Compilation and Running

 Using `g++` (Terminal)

1. Open your terminal in the directory containing `main.cpp`.
//2. Compile the source file:
   ```bash
   g++ -std=c++11 main.cpp -o matrix_transform
   */
#include <iostream>
#include <vector>
#include <iomanip>
#include <numeric>
#include <algorithm>
#include <cmath>

using namespace std;

// Helper function to print a matrix/dataframe cleanly
void printDataFrame(const string& title, const vector<vector<double>>& df) {
    cout << "\n--- " << title << " ---\n";
    for (const auto& row : df) {
        for (double val : row) {
            cout << setw(10) << fixed << setprecision(2) << val << " ";
        }
        cout << "\n";
    }
}

// 1. row_difference(): Computes difference between consecutive elements within each row
vector<vector<double>> row_difference(const vector<vector<double>>& df) {
    vector<vector<double>> result = df;
    for (size_t i = 0; i < df.size(); ++i) {
        for (size_t j = df[i].size() - 1; j > 0; --j) {
            result[i][j] = df[i][j] - df[i][j - 1];
        }
        if (!df[i].empty()) {
            result[i][0] = 0.0; // First element has no previous element to subtract from
        }
    }
    return result;
}

// 2. column_difference(): Computes difference between consecutive rows within each column
vector<vector<double>> column_difference(const vector<vector<double>>& df) {
    vector<vector<double>> result = df;
    if (df.empty()) return result;

    for (size_t i = df.size() - 1; i > 0; --i) {
        for (size_t j = 0; j < df[i].size(); ++j) {
            result[i][j] = df[i][j] - df[i - 1][j];
        }
    }
    // Set the first row elements to 0 since they don't have a previous row
    for (size_t j = 0; j < result[0].size(); ++j) {
        result[0][j] = 0.0;
    }
    return result;
}

// 3. row_percentage(): Computes each element's percentage contribution to its row total
vector<vector<double>> row_percentage(const vector<vector<double>>& df) {
    vector<vector<double>> result = df;
    for (size_t i = 0; i < df.size(); ++i) {
        double row_sum = 0;
        for (double val : df[i]) row_sum += val;

        for (size_t j = 0; j < df[i].size(); ++j) {
            if (row_sum != 0) {
                result[i][j] = (df[i][j] / row_sum) * 100.0;
            } else {
                result[i][j] = 0.0;
            }
        }
    }
    return result;
}

// 4. column_percentage(): Computes each element's percentage contribution to its column total
vector<vector<double>> column_percentage(const vector<vector<double>>& df) {
    vector<vector<double>> result = df;
    if (df.empty()) return result;

    size_t num_rows = df.size();
    size_t num_cols = df[0].size();
    vector<double> col_sums(num_cols, 0.0);

    // Calculate column sums
    for (size_t j = 0; j < num_cols; ++j) {
        for (size_t i = 0; i < num_rows; ++i) {
            col_sums[j] += df[i][j];
        }
    }

    // Compute percentages
    for (size_t i = 0; i < num_rows; ++i) {
        for (size_t j = 0; j < num_cols; ++j) {
            if (col_sums[j] != 0) {
                result[i][j] = (df[i][j] / col_sums[j]) * 100.0;
            } else {
                result[i][j] = 0.0;
            }
        }
    }
    return result;
}

// 5. row_normalize(): Scales each row's values to a 0.0 - 1.0 range (Min-Max Scaling)
vector<vector<double>> row_normalize(const vector<vector<double>>& df) {
    vector<vector<double>> result = df;
    for (size_t i = 0; i < df.size(); ++i) {
        if (df[i].empty()) continue;

        double min_val = *min_element(df[i].begin(), df[i].end());
        double max_val = *max_element(df[i].begin(), df[i].end());
        double range = max_val - min_val;

        for (size_t j = 0; j < df[i].size(); ++j) {
            if (range != 0) {
                result[i][j] = (df[i][j] - min_val) / range;
            } else {
                result[i][j] = 0.0; // Handles rows where all elements are identical
            }
        }
    }
    return result;
}

int main() {
    // Initial sample dataframe/matrix (3 rows, 4 columns)
    vector<vector<double>> dataframe = {
        {10.0, 20.0, 30.0, 40.0},
        {15.0, 25.0, 35.0, 45.0},
        {20.0, 40.0, 60.0, 80.0}
    };

    printDataFrame("Original Dataframe", dataframe);

    // Execute transformations
    vector<vector<double>> row_diff = row_difference(dataframe);
    printDataFrame("Row Difference", row_diff);

    vector<vector<double>> col_diff = column_difference(dataframe);
    printDataFrame("Column Difference", col_diff);

    vector<vector<double>> row_pct = row_percentage(dataframe);
    printDataFrame("Row Percentage (%)", row_pct);

    vector<vector<double>> col_pct = column_percentage(dataframe);
    printDataFrame("Column Percentage (%)", col_pct);

    vector<vector<double>> row_norm = row_normalize(dataframe);
    printDataFrame("Row Normalized (0.0 - 1.0)", row_norm);

    return 0;
}
/**
 * INPUT/OUTPUT EXAMPLE (main.cpp)
#include <iostream>
#include <vector>
#include "dataframe.h" // Replace with main.cpp if single-file setup

int main() {
    std::vector<std::vector<double>> dataframe = {
        {10.0, 20.0, 30.0, 40.0},
        {15.0, 25.0, 35.0, 45.0},
        {20.0, 40.0, 60.0, 80.0}
    };

    // Calculate row percentages
    auto row_pct = row_percentage(dataframe);
    printDataFrame("Row Percentage (%)", row_pct);

    return 0;
} 
    
OUTPUT:
--- Original Dataframe ---
     10.00      20.00      30.00      40.00 
     15.00      25.00      35.00      45.00 
     20.00      40.00      60.00      80.00 

--- Row Normalized (0.0 - 1.0) ---
      0.00       0.33       0.67       1.00 
      0.00       0.33       0.67       1.00 
      0.00       0.33       0.67       1.00
*/
