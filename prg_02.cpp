#include <iostream>
#include <vector>
#include <cstdlib> // for rand()
#include <ctime>   // for time()
using namespace std;
// Function to partition the array around the pivot
int partition(vector<int>& arr, int low, int high, int pivotIndex) {
    int pivotValue = arr[pivotIndex];
    swap(arr[pivotIndex], arr[high]); // Move pivot to end
    int storeIndex = low;

    for (int i = low; i < high; i++) {
        if (arr[i] < pivotValue) {
            swap(arr[storeIndex], arr[i]);
            storeIndex++;
        }
    }
    swap(arr[storeIndex], arr[high]); // Move pivot to its final place
    return storeIndex; // Return the final position of the pivot
}

// Randomized Select function to find the i-th smallest element
int randomized_select(vector<int>& arr, int low, int high, int i) {
    if (low == high) {
        return arr[low]; // If the list contains only one element
    }

    // Select a random pivot index
    int pivotIndex = low + rand() % (high - low + 1);
    pivotIndex = partition(arr, low, high, pivotIndex);

    // The pivot is in its final sorted position
    if (i == pivotIndex) {
        return arr[i]; // Found the i-th smallest element
    } else if (i < pivotIndex) {
        return randomized_select(arr, low, pivotIndex - 1, i); // Search left
    } else {
        return randomized_select(arr, pivotIndex + 1, high, i); // Search right
    }
}
int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed for random number generation

    vector<int> array = {34, 7, 23, 32, 5, 62};
    int i = 3; // For example, find the 3rd smallest element (0-based index)

    if (i < 0 || i >= array.size()) {
        cout << "Index out of bounds." << endl;
        return 1;
    }

    int result = randomized_select(array, 0, array.size() - 1, i);
    cout << "The " << i + 1 << "th smallest element is: " << result << endl;

    return 0;
}

//runs well