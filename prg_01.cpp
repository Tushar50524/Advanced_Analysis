#include <iostream>
#include <vector>
#include <cstdlib> // for rand()
#include <ctime>   // for time()

using namespace std;

// Function to perform randomized quick sort
pair<vector<int>, int> randomized_quick_sort(const vector<int>& arr) {
    if (arr.size() <= 1) {
        return {arr, 0}; // Base case: return the array and 0 comparisons
    }

    // Randomly select a pivot
    int pivot_index = rand() % arr.size();
    int pivot = arr[pivot_index];

    vector<int> less_than_pivot;
    vector<int> equal_to_pivot;
    vector<int> greater_than_pivot;
    
    int comparisons = 0;

    for (const int& element : arr) {
        comparisons++; // Count comparison
        if (element < pivot) {
            less_than_pivot.push_back(element);
        } else if (element > pivot) {
            greater_than_pivot.push_back(element);
        } else {
            equal_to_pivot.push_back(element);
        }
    }

    // Recursively sort the sub-arrays
    pair<vector<int>, int> sorted_less = randomized_quick_sort(less_than_pivot);
    pair<vector<int>, int> sorted_greater = randomized_quick_sort(greater_than_pivot);

    // Combine the sorted sub-arrays and the pivot
    vector<int> sorted_array = sorted_less.first;
    sorted_array.insert(sorted_array.end(), equal_to_pivot.begin(), equal_to_pivot.end());
    sorted_array.insert(sorted_array.end(), sorted_greater.first.begin(), sorted_greater.first.end());

    // Calculate the total number of comparisons
    int total_comparisons = comparisons + sorted_less.second + sorted_greater.second;

    return {sorted_array, total_comparisons};
}

int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed for random number generation

    vector<int> array = {34, 7, 23, 32, 5, 62};
    pair<vector<int>, int> result = randomized_quick_sort(array);
    
    cout << "Sorted Array: ";
    for (const int& num : result.first) {
        cout << num << " ";
    }
    cout << endl;
    cout << "Number of Comparisons: " << result.second << endl;

    return 0;
}